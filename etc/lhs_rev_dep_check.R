# docker run
# -ti
# --rm
# -v /mnt/c/repositories/lhs:/home/docker/lhs
# -w /home/docker
# -u docker
# --name lhs_revdep_check
# rev_dep_step1
# Rscript /home/docker/lhs/etc/lhs_rev_dep_check2.R`

args = commandArgs(trailingOnly=TRUE)

if (length(args) != 3 & length(args[1]) == 1 & length(args[2]) == 1 & length(args[2]) == 1) {
  stop("Three arguments are required (pkg, cran_version, which_type)")
} else 
{
  if (!(args[3] %in% c("Depends", "Imports", "Suggests")))
  {
	stop("The third argument must be Depends, Imports, or Suggests")
  }
  pkg <- args[1]
  cran_version <- args[2]
  which_type <- args[3]
  # pkg <- "lhs"
  # cran_version <- "1.1.3"
  # which_type <- "Depends"
}

etc_dir <- file.path("/home", "docker", pkg, "etc")
etc_txt <- file.path(etc_dir, paste0("revdep_README_", which_type, ".md"))

old_dir <- file.path("revdep", "old")
new_dir <- file.path("revdep", "new")

require(devtools)

cat("\n\n\tCreating directories\n")
if (!file.exists(file.path("revdep")))
  dir.create(file.path("revdep"))
if (!file.exists(old_dir))
  dir.create(old_dir)
if (!file.exists(new_dir))
  dir.create(new_dir)

cat("\tBuilding\n")
built_pkg <- devtools::build(pkg)

cat(paste0("\tCopying ", built_pkg, "\n"))
file.copy(built_pkg, new_dir)

cat("\tDownloading .tar.gz\n")
download.file(paste0("https://cran.r-project.org/src/contrib/", pkg, "_", cran_version, ".tar.gz"),
              destfile = file.path(old_dir, paste0(pkg, "_", cran_version, ".tar.gz")))

cat("\tChecking New\n")
new_results <- tools::check_packages_in_dir(dir = new_dir,
                                            check_args = c("--no-build-vignettes", "--no-manual"),
											check_env = c("_R_CHECK_FORCE_SUGGESTS_" = ifelse(which_type == "Suggests", TRUE, FALSE)),
                                            reverse = list(which = which_type))

warnings()

cat("\tChecking Old\n")
old_results <- tools::check_packages_in_dir(dir = old_dir,
                                            check_args = c("--no-build-vignettes", "--no-manual"),
											check_env = c("_R_CHECK_FORCE_SUGGESTS_" = ifelse(which_type == "Suggests", TRUE, FALSE)),
                                            reverse = list(which = which_type))

warnings()

cat("\tWriting Results\n")

cat(paste0("# Reverse Dependency Checks for package ", pkg, " ", Sys.time(), "\n"),
    file = etc_txt)

cat("\n## Old Results\n\n", file = etc_txt, append = TRUE)
tryCatch({
  capture.output(summary(old_results), file = etc_txt, append = TRUE)
}, error = function(e) cat(paste("Failed to produce results: ", e$message), file = etc_txt, append = TRUE))

cat("\n## New Results\n\n", file = etc_txt, append = TRUE)
tryCatch({
  capture.output(summary(new_results), file = etc_txt, append = TRUE)
}, error = function(e) cat(paste("Failed to produce results: ", e$message), file = etc_txt, append = TRUE))

cat("\tLooping through Differences\n")

cat("\n## Differences\n", file = etc_txt, append = TRUE)

new_detail <- tools::check_packages_in_dir_details(new_dir)
old_detail <- tools::check_packages_in_dir_details(old_dir)

for (this_pkg in unique(c(old_detail$Package, new_detail$Package)))
{
  if (this_pkg == pkg)
    next
  old_rows <- which(old_detail$Package == this_pkg)
  new_rows <- which(new_detail$Package == this_pkg)

  for (i in seq_along(new_rows))
  {
    if (new_detail[new_rows[i],]$Output %in% old_detail[old_rows,]$Output)
    {
      next
    } else
    {
      cat(paste0("\n### ", this_pkg, "\n\n"), file = etc_txt, append = TRUE)
      cat(paste0("- Version:  ", new_detail$Version[new_rows[i]], "\n"), file = etc_txt, append = TRUE)
      cat(paste0("- Check:  ", new_detail$Check[new_rows[i]], "\n"), file = etc_txt, append = TRUE)
      cat(paste0("- Status:  ", new_detail$Status[new_rows[i]], "\n"), file = etc_txt, append = TRUE)
      cat(paste0("- Output: ", new_detail$Output[new_rows[i]], "\n"), file = etc_txt, append = TRUE)
      cat(paste0("- Flags:  ", new_detail$Flags[new_rows[i]], "\n"), file = etc_txt, append = TRUE)
    }
  }
}

cat("\tAlternative Differences\n")

cat("\n## Alternate Differences\n\n", file = etc_txt, append = TRUE)
changes <- tools::check_packages_in_dir_changes(dir = new_dir, old = old_dir, output = TRUE)
capture.output(print(changes), file = etc_txt, append = TRUE)

#save(new_results, old_results, changes,
#     file = file.path(etc_dir, "reverse_dependency_results.Rdata"))

cat("\tDone\n")

