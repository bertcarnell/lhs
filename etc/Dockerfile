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
r-cran-bbmisc \
r-cran-dplyr \
r-cran-ggplot2 \
r-cran-lhs \
r-cran-mlr \
r-cran-paramhelpers \
r-cran-ranger \
r-cran-rcpparmadillo \
r-cran-rlang \
r-cran-rmarkdown

## install the reverse imports
RUN DEBIAN_FRONTEND=noninteractive apt-get update -qq \
	&& DEBIAN_FRONTEND=noninteractive apt-get install -t unstable -y \
  r-cran-ape \
  r-cran-backports \
  r-cran-benchmarkme \
  r-cran-bh \
  r-cran-biasedurn \
  r-cran-biocmanager \
  r-cran-callr \
  r-cran-checkmate \
  r-cran-cli \
  r-cran-collapse \
  r-cran-combinat \
  r-cran-corpcor \
  r-cran-crayon \
  r-cran-data.table \
  r-cran-deldir \
  r-cran-desolve \
  r-cran-dicedesign \
  r-cran-digest \
  r-cran-doparallel \
  r-cran-dorng \
  r-cran-dosnow \
  r-cran-e1071 \
  r-cran-ellipse \
  r-cran-fields \
  r-cran-filelock \
  r-cran-forcats \
  r-cran-foreach \
  r-cran-furrr \
  r-cran-future \
  r-cran-future.apply \
  r-cran-ggally \
  r-cran-ggforce \
  r-cran-ggpubr \
  r-cran-glmnet \
  r-cran-gridbase \
  r-cran-gridextra \
  r-cran-igraph \
  r-cran-interp \
  r-cran-isoband \
  r-cran-iterators \
  r-cran-jsonlite \
  r-cran-kableextra \
  r-cran-knitr \
  r-cran-lifecycle \
  r-cran-magrittr \
  r-cran-matrixstats \
  r-cran-mcmcpack \
  r-cran-microbenchmark \
  r-cran-minpack.lm \
  r-cran-mlmetrics \
  r-cran-mvnfast \
  r-cran-nloptr \
  r-cran-numderiv \
  r-cran-optimparallel \
  r-cran-parallelmap \
  r-cran-partitions \
  r-cran-patchwork \
  r-cran-pbapply \
  r-cran-phangorn \
  r-cran-phytools \
  r-cran-plotly \
  r-cran-pls \
  r-cran-pracma \
  r-cran-progressr \
  r-cran-purrr \
  r-cran-quantreg \
  r-cran-r.utils \
  r-cran-r6 \
  r-cran-rann \
  r-cran-raster \
  r-cran-rcppeigen \
  r-cran-rcppparallel \
  r-cran-rdpack \
  r-cran-readr \
  r-cran-reshape \
  r-cran-reshape2 \
  r-cran-reticulate \
  r-cran-rstan \
  r-cran-rstantools \
  r-cran-rstudioapi \
  r-cran-scales \
  r-cran-sf \
  r-cran-sfsmisc \
  r-cran-shiny \
  r-cran-spam \
  r-cran-spatstat.geom \
  r-cran-spatstat.random \
  r-cran-stanheaders \
  r-cran-stringr \
  r-cran-tensora \
  r-cran-terra \
  r-cran-tibble \
  r-cran-tidyr \
  r-cran-truncnorm \
  r-cran-uuid \
  r-cran-vegan \
  r-cran-viridis \
  r-cran-visnetwork \
  r-cran-xml

## install the reverse suggests
RUN DEBIAN_FRONTEND=noninteractive apt-get update -qq \
	&& DEBIAN_FRONTEND=noninteractive apt-get install -t unstable -y \
  r-cran-assertthat \
  r-cran-bookdown \
  r-cran-caret \
  r-cran-colorspace \
  r-cran-covr \
  r-cran-deoptim \
  r-cran-devtools \
  r-cran-dials \
  r-cran-eaf \
  r-cran-emoa \
  r-cran-fastmatch \
  r-cran-ggrepel \
  r-cran-glue \
  r-cran-hardhat \
  r-cran-ids \
  r-cran-insight \
  r-cran-irace \
  r-cran-irlba \
  r-cran-kernlab \
  r-cran-mda \
  r-cran-mlbench \
  r-cran-modeldata \
  r-cran-nleqslv \
  r-cran-plyr \
  r-cran-processx \
  r-cran-proto \
  r-cran-r.rsp \
  r-cran-rcpproll \
  r-cran-recipes \
  r-cran-rgenoud \
  r-cran-roxygen2 \
  r-cran-rsample \
  r-cran-shape \
  r-cran-spacefillr \
  r-cran-stringi \
  r-cran-testthat \
  r-cran-tgp \
  r-cran-tinytest \
  r-cran-vctrs \
  r-cran-viridislite

# reverse depends
RUN Rscript -e "install.packages(c('acebayes','compare','ContourFunctions','DiceKriging','mlrMBO','OSFD','randtoolbox','smoof','tuneRanger','twinning'), dependencies = c('Depends','Imports','LinkingTo'))"
# reverse imports
RUN Rscript -e "install.packages(c('abc','adaptivetau','AlgDesign','basefun','BayesianPlatformDesignTimeTrend','bbotk','binaryGP','clhs','conf.design','CVXR','dgpsi','dismo','DNAmf','DoE.base','DoE.wrapper','DSAIDE','DSAIRM','EasyABC','ENMeval','ENMTools','ezECM','fossil','FrF2','gamlss','gamlss.dist','gdistance','geiger','genalg','GenSA','ggseqplot','GPfit','GpGp','grapherator','gtools','hmer','hydroMOPSO','hydroTSM','imabc','inaparc','klaR','kpeaks','KrigInv','laGP','latticeExtra','logitnorm','LVGP','MaOEA','metRology','mlr3misc','mlr3tuning','mlrintermbo','mlt','mnormt','MuFiMeshGP','mvtnorm','nlrx','nls.multstart','nntmvn','nsga2R','optim.functions','OUwie','paleotree','paradox','pdist','pGPx','phylolm','plgp','poems','profExtrema','qs2','rcdd','RColorBrewer','RcppHungarian','Rfast','rJava','RNAmf','rrepast','rsm','sandwich','sensitivity','sensobol','seqHMM','SOAs','SVEMnet','tools4uplift','topolow','tram','TraMineR','tramnet','trend','TruncatedNormal','varycoef','xlsx','yager','zoo'), dependencies = c('Depends','Imports','LinkingTo'))"
# reverse suggests
RUN Rscript -e "install.packages(c('akima','binaryRL','box','carrier','ChemoSpec2D','ChemoSpecUtils','cmaes','CMLS','coro','CPoptim','crs','DepthProc','DiceOptim','doFuture','dynemu','dynparam','dynutils','fastGHQuad','flacco','GA','GAparsimony','GauPro','geomtextpath','ggDoE','GPvecchia','hetGP','keras','keras3','kindling','lbfgs','leapgp','lgr','maximin','mco','mirai','mixopt','mlr3','mlr3learners','mlr3mbo','mlr3pipelines','monomvn','multiRL','multiway','NeuralNetTools','nls2','nlstools','OptimaRegion','parsnip','pso','quadprog','quarto','Rdsdp','readJDX','redux','robustbase','rush','sfd','splitfngr','testthatmulti','ThreeWay','tictoc','torch','tune','unrepx','VeccTMVN','vip','workflows','xgboost','yardstick'), dependencies = c('Depends','Imports','LinkingTo'))"
