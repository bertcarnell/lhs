if [ "$(uname -s)" == "MSYS_NT-10.0-WOW" ]; then
  echo Windows Build
  RCMDPLATFORM="C:\Program Files\R\R-3.5.1\bin\x64\Rscript.exe"
else
  echo Linux
  RCMDPLATFORM=Rscript
fi

BCLIBDIR=../bclib
OALIBDIR=../oa/src/oalib
OALHSLIBDIR=../oa/src/oalhslib
LHSLIBDIR=../lhslib/src/lhslib
DESTDIR=src

BCLIBSRCFILES="CRandom.h matrix.h order.h"
LHSLIBSRCFILES="LHSCommonDefines.h geneticLHS.cpp improvedLHS.cpp maximinLHS.cpp \
  optimumLHS.cpp optSeededLHS.cpp randomLHS.cpp utilityLHS.cpp utilityLHS.h"
OALIBSRCFILES="ak.h ak3.cpp akconst.cpp akn.cpp OACommonDefines.h \
  construct.cpp construct.h COrthogonalArray.cpp COrthogonalArray.h galdef.h \
  galois.cpp galois.h gfields.cpp oa.cpp oa.h primes.cpp \
  primes.h runif.cpp runif.h rutils.cpp rutils.h xtndeclare.h \
  xtndispatch.h xtnset.h"
OALHSLIBSRCFILES="oaLHS.cpp oaLHS.h oaLHSUtility.h"

echo Copying from bclib, oa, and lhslib to the lhs package...
for f in $BCLIBSRCFILES; do cp $BCLIBDIR/$f $DESTDIR/$f; done;
for f in $LHSLIBSRCFILES; do cp $LHSLIBDIR/$f $DESTDIR/$f; done;
for f in $OALIBSRCFILES; do cp $OALIBDIR/$f $DESTDIR/$f; done;
for f in $OALHSLIBSRCFILES; do cp $OALHSLIBDIR/$f $DESTDIR/$f; done;
echo Done copying

echo Creating init.c ...
"$RCMDPLATFORM" -e "tools::package_native_routine_registration_skeleton('.', 'src/init.c')"
echo Done with init.c
