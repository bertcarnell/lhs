# Makefile from http://wiki.r-project.org/rwiki/doku.php?id=developers:runit

TOP=../../..
PKG=lhs
SUITE=doRUnit.R

all: inst test

inst: # Install package
	cd ${TOP};\
	R CMD INSTALL ${PKG}

test: # Run unit tests
	export RCMDCHECK=FALSE;\
	cd ${TOP}/lhs/tests;\
	R --vanilla --slave < ${SUITE}
