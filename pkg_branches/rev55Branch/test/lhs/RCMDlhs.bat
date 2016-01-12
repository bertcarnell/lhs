rem build and install lhs

echo off

set Rversion=R-3.0.1

set Rcommand="C:\Program Files\R\%Rversion%\bin\R.exe"
rem set Rcommand32="C:\Program Files\R\%Rversion%\bin\i386\R.exe"
rem set Rcommand64="C:\Program Files\R\%Rversion%\bin\x64\R.exe"
:: %Rcommand% CMD INSTALL --build lhs_*.tar.gz

if "%1" == "check" (
	%Rcommand% CMD check ..\..\pkg\lhs
) else if "%1" == "build" (
	echo **** R CMD build lhs ****
	%Rcommand% CMD build ..\..\pkg\lhs
	echo **** R CMD install --build
	%Rcommand% CMD INSTALL --build ..\..\pkg\lhs
) else if "%1" == "install" (
	%Rcommand% CMD INSTALL ..\..\pkg\lhs
)

PAUSE
