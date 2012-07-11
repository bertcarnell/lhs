rem build and install lhs

echo off

set Rversion=R-2.14.2

set Rcommand="C:\Program Files\R\%Rversion%\bin\R.exe"
rem set Rcommand32="C:\Program Files\R\%Rversion%\bin\i386\R.exe"
rem set Rcommand64="C:\Program Files\R\%Rversion%\bin\x64\R.exe"

if "%1" == "check" (
	cd ..\..\pkg
	%Rcommand% CMD check lhs
	cd ..\trunk\lhs
) else if "%1" == "build" (
	cd ..\..\pkg
	%Rcommand% CMD build lhs
	%Rcommand% CMD INSTALL --build *.tar.gz
	cd ..\trunk\lhs
) else if "%1" == "install" (
	cd ..\..\pkg
	%Rcommand% CMD INSTALL lhs
	cd ..\trunk\lhs
)

PAUSE
