# Makefile from http://wiki.r-project.org/rwiki/doku.php?id=developers:runit

TOP=../../..
PKG=lhs
SUITE=doRUnit.R

all: inst test

# Install package
#   first build the package into a .tar.gz
#   then install from the .tar.gz (this prevents the .svn files from being copied)
#   then remove the .tar.gz
inst:
	cd ${TOP};\
	R CMD BUILD ${PKG};\
	R CMD INSTALL ${PKG}_*;\
	rm ${PKG}_*

# Run unit tests
#   First export a symbol to be read in SUITE
#   then run the tests
test:
	export RCMDCHECK=FALSE;\
	cd ${TOP}/lhs/tests;\
	R --vanilla --slave < ${SUITE}
