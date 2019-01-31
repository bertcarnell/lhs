# get lhs reverse dependencies

require(revdepcheck)
require(devtools)
lhs_rev_depends <- devtools::revdep(pkg = "lhs", dependencies = "Depends")
lhs_rev_imports <- devtools::revdep(pkg = "lhs", dependencies = "Imports")
lhs_rev_suggests <- devtools::revdep(pkg = "lhs", dependencies = "Suggests")

# get all the necessary packages that they depend on
lhs_rev_depends_req <- lapply(lhs_rev_depends, function(x) tools::package_dependencies(packages = x, which = "most"))
lhs_rev_imports_req <- lapply(lhs_rev_imports, function(x) tools::package_dependencies(packages = x, which = "most"))
lhs_rev_suggests_req <- lapply(lhs_rev_suggests, function(x) tools::package_dependencies(packages = x, which = "most"))

#all_unique <- unique(c(unlist(lhs_rev_depends_req),
#                     unlist(lhs_rev_imports_req),
#                     unlist(lhs_rev_suggests_req)))
#all_unique <- all_unique[-which(all_unique == "lhs")]
#cat(paste(paste("r-cran-", all_unique, sep = ""), collapse = " \\ \n"))

rev_dep_req_install <- function(rev_req)
{
  # install if not done already
  rev_depends_ureq <- unique(unlist(rev_req))
  for (i in seq_along(rev_depends_ureq))
  {
    # don't need to check or install lhs
    if (rev_depends_ureq[i] == "lhs")
      next
    # print separators to make scanning easier
    print("---------------------------------------------------------------------")
    print(paste(":::::::", rev_depends_ureq[i], ":::::::::::::::::::::::::::::::"))
    if (!require(rev_depends_ureq[i], character.only = TRUE))
    {
      install.packages(rev_depends_ureq[i])
    }
  }
}
rev_dep_req_install(lhs_rev_depends_req)
rev_dep_req_install(lhs_rev_imports_req)
rev_dep_req_install(lhs_rev_suggests_req)

# ensure you start in the package director
getwd()
revdepcheck::revdep_reset()
revdepcheck::revdep_check(num_workers = 4)
