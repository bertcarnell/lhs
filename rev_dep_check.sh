# https://github.com/r-lib/revdepcheck
#
# need these packages on a clean install of ubuntu 18.04
# sudo apt-get install curl
# sudo apt-get install libcurl4-openssl-dev
# sudo apt-get install libssl-dev
#
# git clone https://github.com/bertcarnell/lhs
# cd lhs
#
# sudo R
# source("https://install-github.me/r-lib/revdepcheck")
#
# getwd() # ensure that the working director is the package directory
# library(revdepcheck)

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
