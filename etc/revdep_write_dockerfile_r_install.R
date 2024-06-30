## write the R dependencies section of the Dockerfile

require(jsonlite)

################################################################################

dependencies_to_install <- function(pkg, reverse_type, depends_types, exclusions)
{
  base_exclusions <- c("base", "compiler", "datasets", "graphics", "grDevices",
                       "grid", "methods", "parallel", "splines", "stats",
                       "stats4", "tcltk", "tools", "translations", "utils")
  rec_exclusions <- c("KernSmooth", "MASS", "Matrix", "boot", "class",
                      "cluster", "codetools", "foreign", "lattice",
                      "mgcv", "nlme", "nnet", "rpart", "spatial", "survival")
  other_exclusions <- tools::package_dependencies(packages = pkg,
                                                  which = c("Depends", "Imports", "LinkingTo"))[[1]]

  x <- tools::package_dependencies(packages = pkg, which = reverse_type, reverse = TRUE)
  x2 <- sapply(x[[1]], function(z) tools::package_dependencies(packages = z,
                                                               which = depends_types))
  x3 <- sort(unique(c(x[[1]], unlist(x2))))
  x3a <- x3[-which(x3 %in% base_exclusions |
                     x3 %in% rec_exclusions |
                     x3 %in% other_exclusions |
                     x3 %in% exclusions)]
  return(x3a)
}

create_install_lines <- function(pkgs)
{
  install_extra <- NULL
  res <- NULL
  for (i in seq_along(pkgs))
  {
    resp <- jsonlite::fromJSON(paste0("https://sources.debian.org/api/search/r-cran-", tolower(pkgs[i])))
    if (!is.null(resp$results$exact))
      res <- c(res, paste0("r-cran-", tolower(pkgs[i]), " \\"))
    else
      install_extra <- c(install_extra, pkgs[i])
  }
  res <- c(res, paste0("install.packages(c('",
                       paste0(install_extra, collapse="','"),
                       "'), dependencies = c('Depends','Imports','LinkingTo'))"))
  return(res)
}

################################################################################

reverse_depends_to_install <- dependencies_to_install("lhs", "Depends",
                                                      c("Depends", "Imports", "LinkingTo"), NA)
reverse_imports_to_install <- dependencies_to_install("lhs", "Imports",
                                                      c("Depends", "Imports", "LinkingTo"),
                                                      reverse_depends_to_install)
reverse_suggests_to_install <- dependencies_to_install("lhs", "Suggests",
                                                       c("Depends", "Imports", "LinkingTo", "Suggests"),
                                                       c(reverse_depends_to_install, reverse_imports_to_install))

a1 <- create_install_lines(reverse_depends_to_install)
a2 <- create_install_lines(reverse_imports_to_install)
a3 <- create_install_lines(reverse_suggests_to_install)

writeLines(c(a1, a2, a3), con = file.path("etc", "temporary_install_output.txt"))
