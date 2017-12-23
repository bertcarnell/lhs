# function based on BiocGenerics:::testPackage("MyPackage")
# from this web page in 2013, http://master.bioconductor.org/developers/how-to/unitTesting-guidelines/
# however, I copied it to eliminate the dependency on bioconductor

testPackage <- function (pkgname, subdir = "unitTests", pattern = "^runit_.*\\.[Rr]$", outputHTML=FALSE) 
{
    .failure_details <- function(result) 
    {
        res <- result[[1L]]
        if (res$nFail > 0 || res$nErr > 0) 
        {
            Filter(function(x) length(x) > 0, lapply(res$sourceFileResults, 
                function(fileRes) {
                  names(Filter(function(x) x$kind != "success", 
                    fileRes))
                }))
        }
        else list()
    }
    
    require(pkgname, quietly = TRUE, character.only = TRUE) || 
        stop("package '", pkgname, "' not found")
    dir <- system.file(subdir, package = pkgname)
    if (nchar(dir) == 0L) 
        stop("unable to find unit tests, no '", subdir, "' dir")
    require("RUnit", quietly = TRUE) || stop("RUnit package not found")
    RUnit_opts <- getOption("RUnit", list())
    RUnit_opts$verbose <- 0L
    RUnit_opts$silent <- TRUE
    RUnit_opts$verbose_fail_msg <- TRUE
    options(RUnit = RUnit_opts)

    ## The default RNG for RUnit is rngKind = "Marsaglia-Multicarry",
    ##  rngNormalKind = "Kinderman-Ramage")
    ## This sets the default to the R default 2.9.2
    suite <- defineTestSuite(name = paste(pkgname, "RUnit Tests"), 
        dirs = dir, testFileRegexp = pattern, rngKind = "Mersenne-Twister", 
        rngNormalKind = "Inversion")
    
    result <- runTestSuite(suite)
    cat("\n\n")
    printTextProtocol(result, showDetails = TRUE)

    if (outputHTML)
    {
      ## Default report name
      pathReport <- file.path(dir, "Result")

      printHTMLProtocol(result, fileName=paste(pathReport, ".html", sep=""))
    }

    
    if (length(details <- .failure_details(result)) > 0) 
    {
        cat("\nTest files with failing tests\n")
        for (i in seq_along(details)) 
        {
            cat("\n  ", basename(names(details)[[i]]), "\n")
            for (j in seq_along(details[[i]])) 
            {
                cat("    ", details[[i]][[j]], "\n")
            }
        }
        cat("\n\n")
        stop("unit tests failed for package ", pkgname)
    }
}

checkLatinHypercube <- function(X)
{
  # check that the matrix is a latin hypercube
  g <- function(Y)
  {
    # check that this column contains all the cells
    breakpoints <- seq(0,1,length=length(Y)+1)
    h <- hist(Y, plot=FALSE, breaks=breakpoints)
    all(h$counts == 1)
  }
  # check all the columns
  all(apply(X, 2, g))
}

testPackage("lhs")
