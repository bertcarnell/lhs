require(roxygen2)

fi <- file.path("F:","Repositories","lhs","pkg","oalhs")
roxygenize(fi, roclets="rd")
