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
# acebayes
# install.packages(c("randtoolbox", "R.rsp"))
# ATmet - pdf issues
# binaryGP
# install.packages("GPfit")
# DoE.wrapper
# install.packages(c("FrF2", "DoE.base"))
# DynamicGP - pdf issues
# EasyABC
# install.packages("abc")
# GPfit - pdf issues
# GPM
# install.packages(c("randtoolbox","doParallel"))
# hetGP
# install.packages("monomvn")
# inaparc - pdf issues
# kergp
# install.packages(c("doParallel", "doFuture"))
# LVGP
# install.packages("randtoolbox")
# maximin
# install.packages("plgp")
# netgen - pdf issues
# optim-functions
# install.packages(c("randtoolbox", "covr"))
# install.packages("covr")
# ParamHelpers - internal test failure
# install.packages("GGally")
# penalizedSVM - pdf issues
# plspolychaos - pdf issues
# install.packages("polychaosbasics")
# polychaosbasics - pdf issues
# profExtrema
# install.packages(c("KrigInv","pGPx","quantreg","rcdd"))
# qle
# install.packages("spatstat")
# rrepast
# install.packages(c("rJava","xlsx","doParallel"))
# spartan
# install.packages("XML")
# vdg
# install.packages("quantreg")
# grapherator
# install.packages("vegan")
# hydroP8O
# install.packages(c("Hmisc","hydroTSM","hydroGOF","vioplot"))
# IGP
# install.packages("PythonInR")
# ParamHelpers - segfault
# metagen
# install.packages(c("BatchJobs","BatchExperiements"))
# mtk
# install.packages("rgl")
# DiceOptim and moko
# install.packages("GPareto")
# ParamHelpers
# install.packages("fastmatch")

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
