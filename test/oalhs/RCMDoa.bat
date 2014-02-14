:: build and install lhs

echo off
echo *******
echo This check must be run as an administrator
echo check, build, install, roxygen
echo *******

set CYGWIN=nodosfilewarning

set Rversion=R-3.0.2
set ACTION=%1
set PACKAGE=oalhs

set Rcommand="F:\ProgramFiles\R\%Rversion%\bin\R.exe"

echo ****
echo **** removing old checks ****
echo ****
rm -rf ..\..\pkg\%PACKAGE%\src-i386
rm -rf ..\..\pkg\%PACKAGE%\src-x64

if "%ACTION%" == "check" (
	%Rcommand% CMD check ..\..\pkg\%PACKAGE%
) else if "%ACTION%" == "build" (
	echo **** R CMD build %PACKAGE% ****
	%Rcommand% CMD build ..\..\pkg\%PACKAGE%
	echo **** R CMD install --build %PACKAGE%
	%Rcommand% CMD INSTALL --build ..\..\pkg\%PACKAGE%
) else if "%ACTION%" == "install" (
	echo **** R CMD INSTALL %PACKAGE%
	%Rcommand% CMD INSTALL ..\..\pkg\%PACKAGE%
) else if "%ACTION%" == "roxygen" (
	echo **** R roxygen
	%Rcommand% --arch x64 --vanilla -f roxygen_oalhs.R
)

echo on

PAUSE
