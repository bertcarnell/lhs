echo off
REM ----------------------------------------------------------------------
REM
REM Run the Sweave command in R
REM
REM ----------------------------------------------------------------------
echo on

R CMD BATCH --vanilla "C://Documents and Settings//carnellr//My Documents//R Packages//lhs//vignettes//Sweave_Command.r"

echo off
REM ----------------------------------------------------------------------
REM
REM Create output PDF file
REM
REM Run pdflatex twice to get the page numbers right
REM
REM ----------------------------------------------------------------------
echo on

"C:\Program Files\MiKTeX 2.6\miktex\bin\pdflatex.exe" -interaction=nonstopmode -quiet augmentLHS_Example.tex
"C:\Program Files\MiKTeX 2.6\miktex\bin\pdflatex.exe" -interaction=nonstopmode augmentLHS_Example.tex

"C:\Program Files\Adobe\Reader 9.0\Reader\AcroRd32.exe" augmentLHS_Example.pdf

PAUSE
