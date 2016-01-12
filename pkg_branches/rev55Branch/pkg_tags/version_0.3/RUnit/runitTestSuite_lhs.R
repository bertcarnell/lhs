################################################################################
#
# Program Name:  runitTestSuite_lhs.R
# Purpose:       To provide test functions for the lhs package
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
defaultPath <- file.path("c:", "program files", "r", "lhs")
source(file.path(defaultPath, "R", "randomLHS.R"))
source(file.path(defaultPath, "R", "improvedLHS.R"))
source(file.path(defaultPath, "R", "maximinLHS.R"))
source(file.path(defaultPath, "R", "optimumLHS.R"))
source(file.path(defaultPath, "R", "geneticLHS.R"))
source(file.path(defaultPath, "R", "augmentLHS.R"))
source(file.path(defaultPath, "R", "optAugmentLHS.R"))
source(file.path(defaultPath, "R", "optSeededLHS.R"))

dllFileName <- file.path(defaultPath, "src", "lhs.dll")

dyn.load(dllFileName)

testSuite.lhs <- defineTestSuite("lhs", dirs=file.path(defaultPath, "RUnit"),
                  testFileRegexp="^runit_[[:alnum:]]+LHS\.[rR]$")

testResult <- runTestSuite(testSuite.lhs)

################# used in development ##########################################

htmlFile <- file.path(defaultPath, "RUnit", "Test Results.html")

## warning expected about gcc compiler
suppressWarnings(printHTMLProtocol(testResult, fileName=htmlFile))

browseURL(htmlFile, browser=getOption("browser"))

dyn.unload(dllFileName)
