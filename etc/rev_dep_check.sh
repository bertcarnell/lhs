# https://github.com/r-lib/revdepcheck
#
# need these packages on a clean minimal install of ubuntu 18.04
# sudo apt-get install curl
# sudo apt-get install libcurl4-openssl-dev
# sudo apt-get install libssl-dev
# sudo apt-get install texlive-full ### (Or maybe just texlive) ###
# sudo apt-get install libgmp-dev
# sudo apt-get install default-jdk
# sudo apt-get install libxml2-dev
# sudo apt-get install python-dev
# sudo apt-get install libcgal-dev libglu1-mesa-dev libglu1-mesa-dev
# sudo apt-get install libfreetype6-dev
# sudo apt-get install xorg libx11-dev libftgl2
# sudo apt-get install libmagick++-dev
#
# git clone https://github.com/bertcarnell/lhs
# cd lhs
#
# sudo R
# source("https://install-github.me/r-lib/revdepcheck")
#
# getwd() # ensure that the working director is the package directory
# library(revdepcheck)
#
# run the script in rev_dep_check.R
#

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

# sudo apt-get install docker docker.io
# https://github.com/rocker-org/rocker
# https://hub.docker.com/_/r-base
# sudo docker pull r-base
