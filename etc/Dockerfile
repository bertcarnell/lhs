## start with the Docker "base R" Debian-based image
FROM r-base

## keep the packages current
RUN apt-get update -qq \
	&& apt-get dist-upgrade -y

## install requirements for R packages
## best practice to run update each time in case the build restarts later
RUN DEBIAN_FRONTEND=noninteractive apt-get update -qq \
	&& DEBIAN_FRONTEND=noninteractive apt-get install -t unstable -y \
	libgmp-dev \
	curl \
	libcurl4-openssl-dev \
	python3 \
	python3-dev \
	libssl-dev \
	default-jdk \
	libxml2-dev \
	libcgal-dev \
	libfreetype6-dev \
	xorg \
	libx11-dev \
	libftgl2 \
	texinfo \
	texlive-base \
	texlive-extra-utils \
	texlive-fonts-extra \
	texlive-fonts-recommended \
	texlive-generic-recommended \
	texlive-latex-base \
	texlive-latex-extra \
	texlive-latex-recommended \
	git \
	libfreetype6-dev \
	libpng-dev \
	libtiff5-dev \
	libjpeg-dev \
	libgeos-dev \
	libgsl-dev \
	qpdf \
	libfontconfig1-dev \
	libharfbuzz-dev \
	libfribidi-dev \
	libgdal-dev

## Install base R and target package with its dependencies
RUN DEBIAN_FRONTEND=noninteractive apt-get update -qq \
	&& DEBIAN_FRONTEND=noninteractive apt-get install -t unstable -y \
	r-recommended \
	r-cran-lhs \
	r-cran-rcpp

## install the reverse dependencies
RUN DEBIAN_FRONTEND=noninteractive apt-get update -qq \
	&& DEBIAN_FRONTEND=noninteractive apt-get install -t unstable -y \
  r-cran-checkmate \
  r-cran-ggplot2 \
  r-cran-hypergeo \
  r-cran-igraph \
  r-cran-lubridate \
  r-cran-mlr \
  r-cran-msm \
  r-cran-pracma \
  r-cran-ranger \
  r-cran-stringr

## install the reverse imports
RUN DEBIAN_FRONTEND=noninteractive apt-get update -qq \
	&& DEBIAN_FRONTEND=noninteractive apt-get install -t unstable -y \
  r-cran-ape \
  r-cran-backports \
  r-cran-callr \
  r-cran-corpcor \
  r-cran-crayon \
  r-cran-data.table \
  r-cran-deldir \
  r-cran-digest \
  r-cran-dplyr \
  r-cran-e1071 \
  r-cran-forcats \
  r-cran-foreach \
  r-cran-furrr \
  r-cran-geosphere \
  r-cran-ggpubr \
  r-cran-glmnet \
  r-cran-interp \
  r-cran-iterators \
  r-cran-knitr \
  r-cran-magrittr \
  r-cran-nloptr \
  r-cran-pbapply \
  r-cran-phangorn \
  r-cran-phytools \
  r-cran-plotly \
  r-cran-pls \
  r-cran-purrr \
  r-cran-quantreg \
  r-cran-raster \
  r-cran-readr \
  r-cran-reshape2 \
  r-cran-reticulate \
  r-cran-rgdal \
  r-cran-rlang \
  r-cran-rstudioapi \
  r-cran-scales \
  r-cran-scatterplot3d \
  r-cran-sf \
  r-cran-shiny \
  r-cran-sp \
  r-cran-spam \
  r-cran-spatstat \
  r-cran-spatstat.core \
  r-cran-spatstat.geom \
  r-cran-statmod \
  r-cran-tgp \
  r-cran-tibble \
  r-cran-tidyr \
  r-cran-truncnorm \
  r-cran-vegan \
  r-cran-vioplot

## install the reverse suggests
RUN DEBIAN_FRONTEND=noninteractive apt-get update -qq \
	&& DEBIAN_FRONTEND=noninteractive apt-get install -t unstable -y \
  r-cran-assertthat \
  r-cran-bookdown \
  r-cran-bridgesampling \
  r-cran-caret \
  r-cran-coda \
  r-cran-colorspace \
  r-cran-covr \
  r-cran-devtools \
  r-cran-dfoptim \
  r-cran-eaf \
  r-cran-ellipse \
  r-cran-emoa \
  r-cran-fastmatch \
  r-cran-fields \
  r-cran-geometry \
  r-cran-irace \
  r-cran-irlba \
  r-cran-kernlab \
  r-cran-mclust \
  r-cran-mda \
  r-cran-mlbench \
  r-cran-plyr \
  r-cran-progress \
  r-cran-proxy \
  r-cran-reshape \
  r-cran-rmarkdown \
  r-cran-roxygen2 \
  r-cran-shape \
  r-cran-testit \
  r-cran-testthat \
  r-cran-tinytest \
  r-cran-tmvtnorm

# reverse depends
RUN Rscript -e "install.packages(c('acebayes','ATmet','BBmisc','compare','DEoptim','DiceDesign','DiceKriging','FME','metRology','mlrMBO','mtk','mvtnorm','netgen','ParamHelpers','randtoolbox','RcppArmadillo','Rdpack','rgl','sensitivity','smoof','spsh','tuneRanger','XML'), dependencies = c('Depends','Imports','LinkingTo'))"
# reverse imports
RUN Rscript -e "install.packages(c('abc','activegp','adaptivetau','AlgDesign','basefun','bbotk','BiasedUrn','binaryGP','chron','CVXR','dbscan','deSolve','dismo','DoE.base','DoE.wrapper','doParallel','doSNOW','DSAIDE','DSAIRM','DynamicGP','EasyABC','ecr','ENMeval','ENMTools','FrF2','gdistance','geiger','genalg','GenSA','GPfit','GPM','grapherator','gridExtra','gtools','hetGP','Hmisc','hydroGOF','hydroPSO','hydroTSM','imabc','inaparc','kpeaks','KrigInv','latticeExtra','logitnorm','LVGP','MaOEA','matrixStats','mcMST','microbenchmark','mlegp','MLmetrics','mlr3misc','mlr3tuning','mlrintermbo','mlt','mnormt','nlrx','nsga2R','numDeriv','optim.functions','optimParallel','OUwie','paleotree','paradox','parallelMap','ParBayesianOptimization','penalizedSVM','pGPx','phylolm','poems','profExtrema','progressr','R6','RandomFields','rcdd','RColorBrewer','Rfast','rgeos','rJava','rrepast','rsm','sandwich','sensobol','solaR','tensorA','tools4uplift','tram','tramnet','trend','TREXr','varycoef','xlsx','yager','yap','zoo'), dependencies = c('Depends','Imports','LinkingTo'))"
# reverse suggests
RUN Rscript -e "install.packages(c('AcceptanceSampling','akima','BayesianTools','car','carrier','CGP','ChemoSpec2D','ChemoSpecUtils','CMLS','comparer','ContourFunctions','crs','DepthProc','DHARMa','DiceEval','DiceOptim','DiceView','Dodge','doRNG','dynparam','dynutils','emulator','fdapace','flacco','FNN','gap','GAparsimony','GauPro','GGally','GPareto','IDPmisc','IGP','laGP','LearnBayes','liGP','maximin','mco','mistat','moko','monomvn','multiway','OptimaRegion','pinp','plgp','qcc','R.rsp','R.utils','randomForest','RANN','RcppEigen','RcppGSL','RcppRoll','Rdsdp','readJDX','RKHSMetaMod','robustbase','SACOBRA','snow','ThreeWay','tseries','vdg','Vdgraph','xgboost'), dependencies = c('Depends','Imports','LinkingTo'))"
