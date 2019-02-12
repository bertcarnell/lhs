pkg <- "lhs"
pkg_path <- ".."
dependencies <- c("Depends", "Suggests")
restart <- NA # or NA
extraArgs <- list(laGP = "--no-vignettes")

require(callr)
require(assertthat)
require(withr)
require(devtools)
require(revdepcheck)
require(rcmdcheck)

################################################################################
# functions
check_and_create_dir <- function(newdir)
{
  if (!file.exists(newdir))
  {
    dir.create(newdir, recursive = TRUE)
  }
  return(newdir)
}

print_section <- function(oldtext, newtext, typetext, output_filename)
{
  if (length(oldtext) != length(newtext) || 
      (length(oldtext) > 0 && length(newtext) > 0 && !all(oldtext == newtext)))
  {
    cat(file=output_filename, "#### ", typetext, "\n\n")
    if (length(oldtext) > 0) cat(file=output_filename, "- Old version:\n\n", oldtext, "\n\n")
    if (length(newtext) > 0) cat(file=output_filename, "- New version:\n\n", newtext, "\n\n")
  } else
  {
    cat(file=output_filename, "#### No Change In ", typetext, "\n\n")
    cat(file=output_filename, oldtext, "\n\n")
  }
}

################################################################################
# Create directory structure
revdep_path <- check_and_create_dir(file.path(pkg_path, "revdep"))
revdep_library_path <- check_and_create_dir(file.path(revdep_path, "library", "lhs"))
revdep_library_path_new <- check_and_create_dir(file.path(revdep_library_path, "new"))
revdep_library_path_old <- check_and_create_dir(file.path(revdep_library_path, "old"))
revdep_check_path <- check_and_create_dir(file.path(revdep_path, "checks"))

################################################################################
# install old package and dependencies

if (!file.exists(file.path(revdep_library_path_old, pkg)))
{
  deps <- tools::package_dependencies(pkg)[[pkg]]

  install.packages(pkg, lib = revdep_library_path_old)
  install.packages(deps, lib = revdep_library_path_old)
} else
{
  cat("old lhs package already installed\n")
}

################################################################################
# install new package and dependencies

if (!file.exists(file.path(revdep_library_path_new, pkg)))
{
  out <- callr::rcmd("build", cmdargs = pkg_path)
  assertthat::assert_that(out$status == 0, msg = "R CMD build failed on the new package")
  pkg_tar_ball <- list.files(path = '.', pattern = pkg)
  install.packages(pkg_tar_ball, lib = revdep_library_path_new, repos = NULL)
  install.packages(deps, lib = revdep_library_path_new)
} else
{
  cat("new lhs package already installed\n")
}

################################################################################
# check reverse dependencies
revdeps <- devtools::revdep(pkg = pkg, dependencies = dependencies)
if (!is.na(restart))
{
  ind <- which(revdeps == restart)
  revdeps <- revdeps[-1:-(ind-1)]
}

if (file.exists(file.path("revdep.out.Rdata")))
{
  load(file = file.path("revdep.out.Rdata"))
} else 
{
  rcmd_output_new <- vector("list", length(revdeps))
  rcmd_output_old <- vector("list", length(revdeps))
}

for (i in seq_along(revdeps))
{
  revdep <- revdeps[i]
  revdep_check_path_curr <- check_and_create_dir(file.path(revdep_check_path, revdep))
  revdep_check_path_curr_old <- check_and_create_dir(file.path(revdep_check_path_curr, "old"))
  revdep_check_path_curr_new <- check_and_create_dir(file.path(revdep_check_path_curr, "new"))

  temp <- download.packages(revdep, destdir = revdep_check_path_curr, type = "source")
  tarball <- temp[1,2]

  extraArgs_local <- NULL
  if (exists(pkg, where=extraArgs))
  {
    extraArgs_local <- extraArgs[[pkg]]
  }

  withr::with_envvar(
    revdepcheck:::check_env_vars(check_version = FALSE, force_suggests = TRUE),
    rcmd_output_old[[i]] <- rcmdcheck::rcmdcheck(
      path = tarball,
      libpath = c(revdep_library_path_old, .libPaths()),
      args = c("--as-cran", extraArgs),
      check_dir = revdep_check_path_curr_old
    )
  )

  withr::with_envvar(
    revdepcheck:::check_env_vars(check_version = FALSE, force_suggests = TRUE),
    rcmd_output_new[[i]] <- rcmdcheck::rcmdcheck(
      path = tarball,
      libpath = c(revdep_library_path_new, .libPaths()),
      args = c("--as-cran", extraArgs),
      check_dir = revdep_check_path_curr_new
    )
  )
  # Collect up the results for a markdown report
  save(rcmd_output_new, rcmd_output_old, file = file.path("revdep.out.Rdata"))
}

assertthat::assert_that(length(rcmd_output_new) == length(rcmd_output_old),
                        msg = "Unexpected error:  new check output and old check output mismatch")

output_file <- file(file.path("revdep_README.md"), "wt")
cat(file=output_file, "# Reverse Dependency Checks for package ", pkg, "\n")
cat(file=output_file, as.character(Sys.time()), "\n\n")

for (i in seq_along(rcmd_output_old))
{
  x <- rcmd_output_old[[i]]
  y <- rcmd_output_new[[i]]
  cat(file=output_file, "## ", x$package, " ", x$version, "\n\n")
  
  print_section(x$errors, y$errors, "Errors", output_file)
  print_section(x$warnings, y$warnings, "Warnings", output_file)
  print_section(x$notes, y$notes, "Notes", output_file)
}
close(output_file)

