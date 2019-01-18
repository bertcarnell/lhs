# https://github.com/r-lib/revdepcheck

if [ "$(uname -s)" == "MSYS_NT-10.0-WOW" ]; then
  echo Windows Build
  RCMDPLATFORM="C:\Program Files\R\R-3.5.1\bin\x64\Rscript.exe"
else
  echo Linux
  RCMDPLATFORM=Rscript
fi

echo Cleaning
"$RCMDPLATFORM" -e "revdepcheck::revdep_reset()"
echo Checking
"$RCMDPLATFORM" -e "revdepcheck::revdep_check(pkg='.', dependencies='Depends', num_workers=1)"
echo Done
