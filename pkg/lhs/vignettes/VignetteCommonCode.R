# short set of utilities to handle figure and Table naming in .Rmd files

numEnv <- new.env()
assign("figureList", list(), envir=numEnv)
assign("tableList", list(), envir=numEnv)

##################################

registerObject <- function(idName, objectListName)
{
  # get the figure list since we can't just add a list element using assign
  objectListLocal <- get(objectListName, envir=numEnv)
  # if the idName is already used, error
  if (!is.null(eval(parse(text=paste("objectListLocal$", idName, sep="")))))
  {
    stop(paste("idName already used prior to registerObject", idName))
  }
  # the new number is the old number of figures plus one
  num <- length(objectListLocal) + 1
  # assign to the local figure list
  eval(parse(text=paste("objectListLocal$", idName, " <- ", num, sep="")))
  # put the local figure list in the one contained in the environment
  assign(objectListName, objectListLocal, pos=numEnv)
  return(getObjectLink(idName, objectListName))
}

registerTable <- function(idName)
{
  registerObject(idName, "tableList")
}

registerFigure <- function(idName)
{
  registerObject(idName, "figureList")
}

getObjectCaption <- function(idName, objectListName)
{
  num <- getObjectNum(idName, objectListName)
  if (objectListName == "figureList")
  {
    return(paste("Figure", num))
  } else if (objectListName == "tableList")
  {
    return(paste("Table", num))
  } else
  {
    stop(paste("objectListName:", objectListName, "not recognized"))
  }
}

getTableCaption <- function(idName)
{
  getObjectCaption(idName, "tableList")
}

getFigureCaption <- function(idName)
{
  getObjectCaption(idName, "figureList")
}

getObjectLink <- function(idName, objectListName)
{
  num <- getObjectNum(idName, objectListName)
  if (objectListName == "figureList")
  {
    return(paste("<a href=\"#", idName, "\">Figure ", num, "</a>", sep=""))
  } else if (objectListName == "tableList")
  {
    return(paste("<a href=\"#", idName, "\">Table ", num, "</a>", sep=""))
  } else
  {
    stop(paste("objectListName:", objectListName, "not recognized"))
  }
}

getTableLink <- function(idName)
{
  return(getObjectLink(idName, "tableList"))
}

getFigureLink <- function(idName)
{
  getObjectLink(idName, "figureList")
}

getObjectNum <- function(idName, objectListName)
{
  objectListLocal <- get(objectListName, envir=numEnv)
  num <- eval(parse(text=paste("objectListLocal$", idName, sep="")))
  if (is.null(num))
  {
    stop(paste("idName is not registered for", idName, "in", objectListName))  
  }
  return(num)
}

getTableNum <- function(idName)
{
  return(getObjectNum(idName, "tableList"))
}

getFigureNum <- function(idName)
{
  getObjectNum(idName, "figureList")
}

addTableCaption <- function(idName, caption, register=FALSE)
{
  cap <- ifelse(register, registerTable(idName), getTableCaption(idName))
  paste("<div id=\"", idName, "\" style=\"text-align:center;text-size:11pt;font-weight:bold\">",
        cap, ".  ", caption, "</div>", sep="")
}

addFigureCaption <- function(idName, caption, register=FALSE)
{
  cap <- ifelse(register, registerFigure(idName), getFigureCaption(idName))
  paste("<div id=\"", idName, "\" style=\"text-align:center;text-size:11pt;font-weight:bold\">",
        cap, ".  ", caption, "</div>", sep="")
}

#########################

if (FALSE)
{
registerFigure("X")
getFigureCaption("X")
getFigureLink("X")
getFigureNum("X")
getFigureNum("Y") # error
registerFigure("Y")
getFigureCaption("Y")
getFigureLink("Y")
getFigureNum("Y")
registerFigure("Y") # error

registerTable("X")
getTableCaption("X")
getTableLink("X")
getTableNum("X")
getTableNum("Y") # error
registerTable("Y")
getTableCaption("Y")
getTableLink("Y")
getTableNum("Y")
registerTable("Y") #error
}
