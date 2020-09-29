# Copyright 2019 Rob Carnell

args <- commandArgs(trailingOnly = TRUE)
# test if there is at least one argument: if not, return an error
if (length(args) == 0) {
  stop("At least one argument must be supplied (target_package)")
} else if (length(args) == 1) {
  target_package <- args[1]
} else {
  cat("Too many arguments supplied\nUsing the first.")
  target_package <- args[1]
}

################################################################################
stopifnot(require(devtools))
get_rev_deps <- function(x) tools::package_dependencies(packages = x, which = "most")

rev_dep_req_install <- function(rev_req)
{
  # install if not done already
  rev_depends_ureq <- unique(unlist(rev_req))
  packages_requiring_installation <- NULL
  for (i in seq_along(rev_depends_ureq))
  {
    # don't need to check or install the target_pacakge
    if (rev_depends_ureq[i] == target_package)
      next
    # print separators to make scanning easier
    cat("\n\n")
    cat("---------------------------------------------------------------------\n")
    cat(paste(":::::::", rev_depends_ureq[i], "(", i, "of", 
      length(rev_depends_ureq), "):::::::::::::::::::::::::::::::\n"))
    if (!require(rev_depends_ureq[i], character.only = TRUE))
    {
      packages_requiring_installation <- c(packages_requiring_installation, rev_depends_ureq[i])
      install.packages(rev_depends_ureq[i], repos="https://cran.rstudio.com", dependencies = TRUE)
    }
    # after installation check the result and error if not working
    if (!require(rev_depends_ureq[i], character.only = TRUE))
    {
      stop(paste("Installation of ", rev_depends_ureq[i], " failed"))
    }
  }
  return(packages_requiring_installation)
}

################################################################################

# get all the reverse dependencies of the target_package
lhs_rev_depends <- devtools::revdep(pkg = target_package, dependencies = "Depends")
lhs_rev_imports <- devtools::revdep(pkg = target_package, dependencies = "Imports")
lhs_rev_suggests <- devtools::revdep(pkg = target_package, dependencies = "Suggests")

# get all the necessary packages that they depend on so they can operate fully
#   in the reverse dependency checks
lhs_rev_depends_req <- lapply(lhs_rev_depends, get_rev_deps)
lhs_rev_imports_req <- lapply(lhs_rev_imports, get_rev_deps)
lhs_rev_suggests_req <- lapply(lhs_rev_suggests, get_rev_deps)

# Install the packages if they are not already installed
installed_depends <- rev_dep_req_install(lhs_rev_depends_req)
installed_imports <- rev_dep_req_install(lhs_rev_imports_req)
installed_suggests <- rev_dep_req_install(lhs_rev_suggests_req)

# Print the packages that required installation to add to the debian packages section
all_unique <- unique(c(installed_depends, installed_imports, installed_suggests))
all_unique <- all_unique[-which(all_unique == "lhs")]
print("----- Consider Installing These Packages -----")
cat(paste(paste("r-cran-", all_unique, sep = ""), collapse = " \\ \n"))

