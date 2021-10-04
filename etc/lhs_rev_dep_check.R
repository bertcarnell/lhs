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

################################################################################

require(tools)

#  File src/library/tools/R/checktools.R
#  Part of the R package, https://www.R-project.org
#
#  Copyright (C) 2013-2020 The R Core Team
#  Modified by Robert Carnell.  Copyright 2021
my_check_packages_in_dir <-
  function(dir,
           check_args = character(),
           check_args_db = list(),
           reverse = NULL,
           check_env = character(),
           xvfb = FALSE,
           Ncpus = getOption("Ncpus", 1L),
           clean = TRUE,
           ...)
  {
    owd <- getwd()
    dir <- normalizePath(dir)
    setwd(dir)
    on.exit(setwd(owd))

    .check_packages_in_dir_retval <-
      function(dir,
               pfiles,
               pnames = character(),
               rnames = character()) {
        structure(pfiles,
                  dir = dir,
                  pnames = pnames,
                  rnames = rnames,
                  class = "check_packages_in_dir")
      }

    pfiles <- Sys.glob("*.tar.gz")
    if(!length(pfiles)) {
      message("no packages to check")
      return(invisible(.check_packages_in_dir_retval(dir, pfiles)))
    }

    pnames <- sub("_.*", "", pfiles)

    os_type <- .Platform$OS.type

    ## Xvfb usage and options.
    ## We do not use Xvfb on Windows.
    ## Otherwise, if argument 'xvfb' is
    ## * a logical, Xvfb is used only if identical to TRUE;
    ## * something else, then as.character(xvfb) gives the Xvfb options.
    xvfb_options <- "-screen 0 1280x1024x24"
    if(os_type == "windows")
      xvfb <- FALSE
    else if(is.logical(xvfb)) {
      if(!isTRUE(xvfb))
        xvfb <- FALSE
    } else {
      xvfb_options <- as.character(xvfb)
      xvfb <- TRUE
    }

    curl <- if(os_type == "windows")
      sprintf("file:///%s", dir)
    else
      sprintf("file://%s", dir)

    libdir <- file.path(dir, "Library")
    dir.create(libdir, showWarnings = FALSE)
    outdir <- file.path(dir, "Outputs")
    dir.create(outdir, showWarnings = FALSE)

    ## Determine packages using fake/no install for checking.
    ## Handle these as follows:
    ## * For packages using '--install=no', forward dependencies do not
    ##   need to installed, and reverse dependencies do not need to be
    ##   checked.
    ## * For packages using '--install=fake', forward dependencies must
    ##   be available for checking, and checking reverse dependencies
    ##   makes sense (e.g, to spot missing Rd xrefs).
    pnames_using_install_no <- character()
    pnames_using_install_fake <- character()
    check_args_db <- as.list(check_args_db)
    if(length(check_args_db) &&
       !is.null(nms <- names(check_args_db))) {
      args <- lapply(check_args_db,
                     function(e)
                       scan(text = e, what = character(), quiet = TRUE))
      pnames_using_install_no <-
        nms[vapply(args, function(e) any(e == "--install=no"), NA)]
      pnames_using_install_fake <-
        nms[vapply(args, function(e) any(e == "--install=fake"), NA)]
    } else {
      ## If check_args_db has no names it is useless.
      ## Perhaps complain?
      check_args_db <- list()
    }

    ## Build a package db from the source packages in the working
    ## directory.
    tools:::write_PACKAGES(dir, type = "source")
    if(dir.exists(depdir <- file.path(dir, "Depends"))) {
      tools:::write_PACKAGES(depdir, type = "source")
      curl <- c(curl, paste0(curl, "/Depends"))
    }
    ## Determine packages available locally (for checking) and in the
    ## repositories, and merge the information giving preference to the
    ## former.
    localones <- utils::available.packages(contriburl = curl,
                                           type = "source")
    curls <- utils::contrib.url(getOption("repos"), type = "source")
    available <- utils::available.packages(contriburl = curls,
                                           type = "source")
    available <- rbind(localones, available)
    available <-
      available[!duplicated(available[, "Package"]), , drop = FALSE]
    curls <- c(curl, curls)

    ## As of c52164, packages with OS_type different from the current
    ## one are *always* checked with '--install=no'.
    ## These packages are also filtered out by default (via the OS_type
    ## filter) from the repository package computations.
    ## Hence move packages in the install=fake list not listed by
    ## available.packages() to the install=no list.
    pnames_using_install_no <-
      c(pnames_using_install_no,
        setdiff(pnames_using_install_fake, available[, "Package"]))
    pnames_using_install_fake <-
      intersect(pnames_using_install_fake, available[, "Package"])

    if(!is.null(reverse) && !isFALSE(reverse)) {
      ## Determine and download reverse dependencies to be checked as
      ## well.

      reverse <- as.list(reverse)
      ## Merge with defaults, using partial name matching.
      defaults <- list(which = c("Depends", "Imports", "LinkingTo"),
                       recursive = FALSE,
                       repos = getOption("repos"))
      pos <- pmatch(names(reverse), names(defaults), nomatch = 0L)
      defaults[pos] <- reverse[pos > 0L]

      subset_reverse_repos <- !identical(defaults$repos, getOption("repos"))
      if(subset_reverse_repos &&
         !all(defaults$repos %in% getOption("repos")))
        stop("'reverse$repos' should be a subset of getOption(\"repos\")")

      rnames <- if(is.list(defaults$which)) {
        ## No recycling of repos for now.
        defaults$recursive <- rep_len(as.list(defaults$recursive),
                                      length(defaults$which))
        unlist(Map(function(w, r)
          tools::package_dependencies(setdiff(pnames,
                                              pnames_using_install_no),
                                      available,
                                      which = w,
                                      recursive = r,
                                      reverse = TRUE),
          defaults$which,
          defaults$recursive),
          use.names = FALSE)
      } else {
        tools::package_dependencies(setdiff(pnames,
                                            pnames_using_install_no),
                                    available,
                                    which = defaults$which,
                                    recursive = defaults$recursive,
                                    reverse = TRUE)
      }

      add_recommended_maybe <-
        tools:::config_val_to_logical(Sys.getenv("_R_TOOLS_C_P_I_D_ADD_RECOMMENDED_MAYBE_",
                                                 "FALSE"))
      if(add_recommended_maybe) {
        ## Add all recommended packages with any dependency on the
        ## packages to be checked.
        rnames <-
          c(rnames,
            names(Filter(length,
                         lapply(tools::package_dependencies(tools:::.get_standard_package_names()$recommended,
                                                            available,
                                                            which = "all"),
                                intersect,
                                pnames))))
      }

      rnames <- intersect(unlist(rnames, use.names = FALSE),
                          available[, "Package"])
      rnames <- setdiff(rnames, pnames)

      pos <- match(rnames, available[, "Package"], nomatch = 0L)
      if(subset_reverse_repos) {
        pos <- split(pos[pos > 0L], available[pos, "Repository"])
        ## Only want the reverse dependencies for which Repository
        ## starts with an entry in defaults$repos.
        nms <- names(pos)
        ind <- (rowSums(outer(nms, defaults$repos, startsWith)) > 0)
        pos <- unlist(pos[ind], use.names = FALSE)
      }
      rnames <- available[pos, "Package"]
      rfiles <- sprintf("%s_%s.tar.gz",
                        rnames,
                        available[pos, "Version"])

      if(length(rfiles)) {
        message("downloading reverse dependencies ...")
        rfurls <- sprintf("%s/%s",
                          available[pos, "Repository"],
                          rfiles)
        for(i in seq_along(rfiles)) {
          message(sprintf("downloading %s ... ", rfiles[i]),
                  appendLF = FALSE)
          status <- if(!utils::download.file(rfurls[i], rfiles[i],
                                             quiet = TRUE))
            "ok" else "failed"
          message(status)
        }
        message("")
      }

    } else {
      rfiles <- rnames <- character()
    }

    pnames <- c(pnames, rnames)

    ## Install what is needed.

    if(xvfb) {
      pid <- tools:::start_virtual_X11_fb(xvfb_options)
      on.exit(tools:::close_virtual_X11_db(pid), add = TRUE)
    }

    depends <-
      tools::package_dependencies(pnames, available, which = "most")
    depends <- setdiff(unique(unlist(depends, use.names = FALSE)),
                       tools:::.get_standard_package_names()$base)

    ## Need to install depends which are not installed or installed but
    ## old.
    libs <- c(libdir, .libPaths())
    installed <- utils::installed.packages(libs)
    installed <- installed[!duplicated(installed[, "Package"]), ,
                           drop = FALSE]


    ## (10/3/2021)
    ## The original R version of this function also updates any package that is
    ## old.  Removing that functionality

    #outofdate <- utils::old.packages(instPkgs = installed,
    #                                 available = available)[, "Package"]
    installed <- installed[, "Package"]

    #depends <- c(setdiff(depends, installed),
    #             intersect(intersect(depends, installed), outofdate))
    depends <- setdiff(depends, installed)


    if(length(depends)) {
      message(paste(strwrap(sprintf("installing dependencies %s",
                                    paste(sQuote(sort(depends)),
                                          collapse = ", ")),
                            exdent = 2L),
                    collapse = "\n"), domain = NA)
      ## <NOTE>
      ## Ideally we would capture stdout and stderr in e.g.
      ##   outdir/install_stdout.txt
      ##   outdir/install_stderr.txt
      ## But using several CPUs uses Make to install, which seems to
      ## write to stdout/stderr "directly" ... so using sink() will
      ## not work.  Hence, use 'keep_outputs' to capture "outputs"
      ## (combining install stdout and stderr into one file).
      message("")
      iflags <- as.list(rep.int("--fake",
                                length(pnames_using_install_fake)))
      names(iflags) <- pnames_using_install_fake
      tmpdir <- tempfile(tmpdir = outdir)
      dir.create(tmpdir)
      utils::install.packages(depends, lib = libdir,
                              contriburl = curls,
                              available = available,
                              dependencies = NA,
                              INSTALL_opts = iflags,
                              keep_outputs = tmpdir,
                              Ncpus = Ncpus,
                              type = "source")
      outfiles <- Sys.glob(file.path(tmpdir, "*.out"))
      file.rename(outfiles,
                  file.path(outdir,
                            sprintf("install_%s",
                                    basename(outfiles))))
      unlink(tmpdir, recursive = TRUE)
      message("")
      ## </NOTE>
    }

    ## Merge check_args and check_args_db into check_args_db used for
    ## checking.
    check_args <- if(is.list(check_args)) {
      c(rep.int(list(check_args[[1L]]), length(pfiles)),
        rep.int(list(check_args[[2L]]), length(rfiles)))
    } else {
      rep.int(list(check_args), length(pnames))
    }
    check_args_db <- check_args_db[pnames]
    check_args_db <- Map(c, check_args, check_args_db)
    names(check_args_db) <- pnames

    check_env <- if(is.list(check_env)) {
      c(rep.int(list(check_env[[1L]]), length(pfiles)),
        rep.int(list(check_env[[2L]]), length(rfiles)))
    } else {
      rep.int(list(check_env), length(pnames))
    }
    ## No user level check_env_db for now.
    check_env_db <- as.list(check_env)
    names(check_env_db) <- pnames

    pfiles <- c(pfiles, rfiles)

    ## sub-R processes need to use libdir + current library trees
    oldrlibs <- Sys.getenv("R_LIBS")
    Sys.setenv(R_LIBS = paste(libs, collapse = .Platform$path.sep))
    on.exit(Sys.setenv(R_LIBS = oldrlibs), add = TRUE)

    message(sprintf("Starting Checks with _R_CHECK_FORCE_SUGGESTS = %s",
                    Sys.getenv("_R_CHECK_FORCE_SUGGESTS_")))

    check_package <- function(pfile, args_db = NULL, env_db = NULL) {
      message(sprintf("checking %s %s ...", pfile, Sys.time()))
      pname <- sub("_.*", "", basename(pfile))
      out <- file.path(outdir,
                       sprintf("check_%s_stdout.txt", pname))
      err <- file.path(outdir,
                       sprintf("check_%s_stderr.txt", pname))
      lim <- tools:::get_timeout(Sys.getenv("_R_CHECK_ELAPSED_TIMEOUT_"))
      system.time(system2(file.path(R.home("bin"), "R"),
                          c("CMD",
                            "check",
                            "--timings",
                            args_db[[pname]],
                            pfile),
                          stdout = out,
                          stderr = err,
                          env = env_db[[pname]],
                          timeout = lim))
    }

    if(Ncpus > 1L) {
      if(os_type != "windows") {
        timings <- parallel::mclapply(pfiles,
                                      check_package,
                                      check_args_db,
                                      check_env_db,
                                      mc.cores = Ncpus)
      } else {
        cl <- parallel::makeCluster(Ncpus)
        timings <- parallel::parLapply(cl,
                                       pfiles,
                                       check_package,
                                       check_args_db,
                                       check_env_db)
        parallel::stopCluster(cl)
      }
    } else {
      timings <- lapply(pfiles,
                        check_package,
                        check_args_db,
                        check_env_db)
    }

    timings <- do.call(rbind, lapply(timings, summary))
    rownames(timings) <- pnames
    utils::write.table(timings, "timings.tab")

    file.rename(sprintf("%s.Rcheck", rnames),
                sprintf("rdepends_%s.Rcheck", rnames))

    if(clean) {
      file.remove(rfiles)
    } else {
      file.rename(rfiles, sprintf("rdepends_%s", rfiles))
    }

    invisible(.check_packages_in_dir_retval(dir,
                                            pfiles,
                                            setdiff(pnames, rnames),
                                            rnames))
  }

################################################################################

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

# Don't want to install any extra suggested packages because it takes much longer
#   And does not complete in the 3 hr allotted by github
Sys.setenv("_R_CHECK_FORCE_SUGGESTS_" = "FALSE")
new_results <- my_check_packages_in_dir(dir = new_dir,
											check_args = c("--no-build-vignettes", "--no-manual"),
											reverse = list(which = which_type))

warnings()

cat("\tChecking Old\n")
old_results <- my_check_packages_in_dir(dir = old_dir,
											check_args = c("--no-build-vignettes", "--no-manual"),
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

cat("\n## Differences Checking for Exact Message Matches\n", file = etc_txt, append = TRUE)

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

cat("\n## Differences using check_packages_in_dir_changes()\n\n", file = etc_txt, append = TRUE)
changes <- tools::check_packages_in_dir_changes(dir = new_dir, old = old_dir, output = TRUE)
capture.output(print(changes), file = etc_txt, append = TRUE)

#save(new_results, old_results, changes,
#     file = file.path(etc_dir, "reverse_dependency_results.Rdata"))

cat("\tDone\n")

