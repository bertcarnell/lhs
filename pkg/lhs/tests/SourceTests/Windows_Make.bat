@echo off

set GCC=gcc -O2 -Wall -c -pedantic
set OUT=.\RRelease

set RINT_LIB=lhsTest.dll

set RPATH=C:\PROGRA~1\R\R-2.9.2


REM ******** Cleanup Old Builds ********
:Cleanup
if not exist %OUT% (
	echo Creating output directory: %OUT%
	mkdir %OUT%
) else ( 
	echo Cleaning output directory: %OUT%
	if exist %OUT%\*.o (
		del /Q %OUT%\*.o
	)
)
if exist %RINT_LIB% (
	echo Cleaning RInterface library: %RINT_LIB%
	del /Q %RINT_LIB%
)


REM ******** Create lhs Objects ********
:lhs
echo.
echo Compiling lhs objects.
echo.

set LHS_SRC=..\..\src
set LHS_INC=-I%RPATH%\include
set LHS_GCC=%GCC% %LHS_INC%

%LHS_GCC% -o%OUT%\improvedLHS_R.o	%LHS_SRC%\improvedLHS_R.c


REM ******** Link *******
:LinkLib
echo.
echo Linking RDoseResponseInterface library...
echo.

set LHS_OBJS=%OUT%\improvedLHS_R.o

echo on
gcc -shared -s -o%RINT_LIB% %LHS_OBJS% -L %RPATH%\bin -lR
echo off

PAUSE
