################################################################################
#
# Program Name:  runitTestSuite_triangle.R
# Purpose:       To provide test functions for teh triangle package
# Author:        Rob Carnell
# Date:          June 2006
#
# Required Packages:  RUnit
# R version:          2.3.0 (>=2.0.0)
#
# Notes:  Build lhs.dll using R CMD SHLIB -o lhs.dll improvedLHS_R.c maximinLHS_R.c
#
################################################################################

require(RUnit)

## used as part of package
#require(lhs)
#defaultPath <- chartr("/", "//", paste(.path.package("lhs"), "/RUnit", sep=""))

################# used in development ##########################################
defaultPath <- "c:////program files//r//lhs//RUnit"                            #
source("c:////program files//r//lhs//R//randomLHS.R")                          #
source("c:////program files//r//lhs//R//improvedLHS.R")                        #
source("c:////program files//r//lhs//R//maximinLHS.R")                         #
source("c:////program files//r//lhs//R//optimumLHS.R")                         #
source("c:////program files//r//lhs//R//geneticLHS.R")                         #
source("c:////program files//r//lhs//R//augmentLHS.R")                         #
source("c:////program files//r//lhs//R//optAugmentLHS.R")                      #
source("c:////program files//r//lhs//R//optSeededLHS.R")                       #

dyn.load("c:/program files/R/lhs/src/lhs.dll")

testSuite.lhs <- defineTestSuite("lhs", dirs=defaultPath)

testResult <- runTestSuite(testSuite.lhs)

################# used in development ##########################################
                                                                               #
## warning expected about gcc compiler                                         #
suppressWarnings(printHTMLProtocol(testResult,                                 #
  fileName=paste(defaultPath, "//Test Results.html", sep="")))                 #
                                                                               #
browseURL(paste(defaultPath, "//Test Results.html",sep=""),                    #
          browser=getOption("browser"))                                        #

dyn.unload("c:/program files/R/lhs/src/lhs.dll")
