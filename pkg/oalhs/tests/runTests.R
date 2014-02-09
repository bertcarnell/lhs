# function based on BiocGenerics:::testPackage("MyPackage")
# from this web page in 2013, http://master.bioconductor.org/developers/how-to/unitTesting-guidelines/
# however, I copied it to eliminate the dependency on bioconductor

testPackage <- function (pkgname, subdir = "unitTests", pattern = "^runit_.*\\.[Rr]$") 
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
    
    #suite <- defineTestSuite(name = paste(pkgname, "RUnit Tests"), 
    #    dirs = dir, testFileRegexp = pattern, rngKind = "default", 
    #    rngNormalKind = "default")
    
    result <- runTestSuite(suite)
    cat("\n\n")
    printTextProtocol(result, showDetails = FALSE)

  ## Default report name
  pathReport <- file.path(dir, "Result")

  ## Report to stdout and text files and html
  printTextProtocol(result, showDetails=FALSE,
                    fileName=paste(pathReport, "Summary.txt", sep=""))
  printTextProtocol(result, showDetails=TRUE,
                    fileName=paste(pathReport, ".txt", sep=""))
  printHTMLProtocol(result, fileName=paste(pathReport, ".html", sep=""))

    
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
    result
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

test.oa_type1.standard <- function(methodname, q, ncol, expectedrow, expectedcol)
{
  eval(parse(text=paste("A <- ", methodname, "(", q, ", ", ncol, ", FALSE)")))
  # matrix is correct size
  checkEquals(expectedrow, nrow(A), "A1")
  checkEquals(expectedcol, ncol(A), "A2")
  # without randomizing, you get the same result
  eval(parse(text=paste("B <- ", methodname, "(", q, ", ", ncol, ", FALSE)")))
  checkEqualsNumeric(A, B, "B1", tolerance=1E-12)
  # with randomizing, you get a different result
  set.seed(1976)
  eval(parse(text=paste("D <- ", methodname, "(", q, ", ", ncol, ", TRUE)")))
  checkTrue(!all(abs(B - D) < 1E-12), "D1")
  # with the same seed, you get the same result
  set.seed(1976)
  eval(parse(text=paste("E <- ", methodname, "(", q, ", ", ncol, ", TRUE)")))
  checkEqualsNumeric(D, E, "E1", tolerance=1E-12)
  # with a different seed, you get a different result
  set.seed(1077)
  eval(parse(text=paste("G <- ", methodname, "(", q, ", ", ncol, ", TRUE)")))
  checkTrue(!all(abs(G - E) < 1E-12), "G1")
  
  # NA for q or Ncol throws an error
  eval(parse(text=paste("checkException(", methodname, "(NA, ", ncol, ", FALSE), silent=TRUE)")))
  eval(parse(text=paste("checkException(", methodname, "(", q, ",NA, FALSE), silent=TRUE)")))
  # NA for logical does not throw
  #checkException(createBush(3, 3, NA))

  # wrong type of algorithm throws
  checkException(.Call("oa_type1", "junk", as.integer(3), as.integer(3), 
               as.logical(FALSE)), silent=TRUE)

  # sending in vectors throws an error
  eval(parse(text=paste("checkException(", methodname, "(c(3,4), ", ncol, ", FALSE), silent=TRUE)")))
  eval(parse(text=paste("checkException(", methodname, "(", q, ",c(3,4), FALSE), silent=TRUE)")))
  eval(parse(text=paste("checkException(", methodname, "(", q, ", ", ncol, ", C(TRUE,FALSE)), silent=TRUE)")))

  # sending in Inf for the integers throws an error and a warning
  eval(parse(text=paste("suppressWarnings(checkException(", methodname, "(Inf, ", ncol, ", FALSE), silent=TRUE))")))
  eval(parse(text=paste("suppressWarnings(checkException(", methodname, "(", q, ",Inf, FALSE), silent=TRUE))")))
  #checkException(createBush(3, 3, Inf), silent=TRUE) # same reason as an NA
  
  # check orthogonality
  eval(parse(text=paste("A <- ", methodname, "(", q, ", ", ncol, ", FALSE)")))
  test <- t(A) %*% A
  checkTrue(all(diag(test) == test[0,0]))
  checkTrue(all(c(test[upper.tri(test)]) == test[1,2]))
  # check orthogonality of a randomized oa
  set.seed(111111)
  eval(parse(text=paste("A <- ", methodname, "(", q, ", ", ncol, ", FALSE)")))
  test <- t(A) %*% A
  checkTrue(all(diag(test) == test[0,0]))
  checkTrue(all(c(test[upper.tri(test)]) == test[1,2]))
}

testPackage("oalhs")
