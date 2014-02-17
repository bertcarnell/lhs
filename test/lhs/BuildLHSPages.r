rm(list=ls())

require(knitr)
require(markdown)

repositoryPath <- file.path("F:","Repositories","lhs")
vignettePath <- file.path(repositoryPath, "pkg","lhs","vignettes")
webPath <- file.path(repositoryPath, "www")

pages <- c(
  "lhs_basics.Rmd",
  "augmentLHS_Example.Rmd"
)

pdfs <- NULL

################################################################################

filenames <- file.path(vignettePath, pages)

stopifnot(all(sapply(filenames, function(x){
  file.exists(x)
})))

### knit the files to html
dummy <- sapply(pages, function(x) {
  #knitr::knit2html(file.path(vignettePath, x), 
  #                 output=file.path(webPath, gsub("[.]Rmd", ".md", x)), quiet=FALSE)
  setwd(file.path(webPath))
  knitr::knit(file.path(vignettePath, x),
              output=file.path(webPath, gsub("[.]Rmd", ".md", x)),
              quiet=FALSE)
  markdownToHTML(file.path(webPath, gsub("[.]Rmd", ".md", x)),
                        output=file.path(webPath, gsub("[.]Rmd", ".html", x)))
})

if (!is.null(pdfs))
{
  ### knit the pdfs
  filenames <- file.path(vignettePath, pdfs)
  
  stopifnot(all(sapply(filenames, function(x){
    file.exists(x)
  })))
  
  intermediatePdfs <- file.path(webPath, gsub("[.]Rtex", "-knitr.tex", pdfs))
  dummy <- sapply(pdfs, function(x) {
    Sweave2knitr(file.path(vignettePath, x), 
                     output=intermediatePdfs)
  })
  intermediateTexs <- gsub("-knitr.tex", ".tex", intermediatePdfs)
  dummy <- sapply(pdfs, function(x) {
    knitr::knit(intermediatePdfs, 
                     output=intermediateTexs, quiet=FALSE)
    tools::texi2pdf(intermediateTexs)
  })
}

### copy the results to the gh-pages branch
#dummy <- mapply(function(x,y) {
#  file.copy(file.path(x, "results.html"), 
#            file.path(pagesPath, paste(y, ".html", sep="")), 
#            overwrite=TRUE)
#  }, filenamesNoExt, races[1:4])
