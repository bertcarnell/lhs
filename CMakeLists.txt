cmake_minimum_required(VERSION 2.8)
project(LHS)

# mkdir build
# cd build
# cmake ..

set(BCLIBDIR "${CMAKE_CURRENT_SOURCE_DIR}/../bclib")
set(OALIBDIR "${CMAKE_CURRENT_SOURCE_DIR}/../oa/src/oalib")
set(OALHSLIBDIR "${CMAKE_CURRENT_SOURCE_DIR}/../oa/src/oalhslib")
set(LHSLIBDIR "${CMAKE_CURRENT_SOURCE_DIR}/../lhslib/src/lhslib")
set(DESTDIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(BCLIBSRCFILES 
	"${BCLIBDIR}/CRandom.h"
	"${BCLIBDIR}/matrix.h"
	"${BCLIBDIR}/order.h")

# TODO:  Need to deal with multiple CommonDefines.h
set(LHSLIBSRCFILES 
	"${LHSLIBDIR}/LHSCommonDefines.h"
	"${LHSLIBDIR}/geneticLHS.cpp"
	"${LHSLIBDIR}/improvedLHS.cpp"
	"${LHSLIBDIR}/maximinLHS.cpp"
	"${LHSLIBDIR}/optimumLHS.cpp"
	"${LHSLIBDIR}/optSeededLHS.cpp"
	"${LHSLIBDIR}/randomLHS.cpp"
	"${LHSLIBDIR}/utilityLHS.cpp"
	"${LHSLIBDIR}/utilityLHS.h")

set(OALIBSRCFILES 
	"${OALIBDIR}/ak.h"
	"${OALIBDIR}/ak3.cpp"
	"${OALIBDIR}/akconst.cpp"
	"${OALIBDIR}/akn.cpp"
	"${OALIBDIR}/OACommonDefines.h"
	"${OALIBDIR}/construct.cpp"
	"${OALIBDIR}/construct.h"
	"${OALIBDIR}/COrthogonalArray.cpp"
	"${OALIBDIR}/COrthogonalArray.h"
	"${OALIBDIR}/galdef.h"
	"${OALIBDIR}/galois.cpp"
	"${OALIBDIR}/galois.h"
	"${OALIBDIR}/gfields.cpp"
	"${OALIBDIR}/oa.cpp"
	"${OALIBDIR}/oa.h"
	"${OALIBDIR}/primes.cpp"
	"${OALIBDIR}/primes.h"
	"${OALIBDIR}/runif.cpp"
	"${OALIBDIR}/runif.h"
	"${OALIBDIR}/rutils.cpp"
	"${OALIBDIR}/rutils.h"
	"${OALIBDIR}/xtndeclare.h"
	"${OALIBDIR}/xtndispatch.h"
	"${OALIBDIR}/xtnset.h")

set(OALHSLIBSRCFILES 
	"${OALHSLIBDIR}/oaLHS.cpp"
	"${OALHSLIBDIR}/oaLHS.h"
	"${OALHSLIBDIR}/oaLHSUtility.h")

file(COPY ${BCLIBSRCFILES} DESTINATION ${DESTDIR})
file(COPY ${LHSLIBSRCFILES} DESTINATION ${DESTDIR})
file(COPY ${OALIBSRCFILES} DESTINATION ${DESTDIR})
file(COPY ${OALHSLIBSRCFILES} DESTINATION ${DESTDIR})
				