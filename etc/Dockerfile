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
	qpdf

RUN DEBIAN_FRONTEND=noninteractive apt-get update -qq \
	&& apt-get install -t unstable -y \
	r-recommended \
	r-cran-rcpp \
	r-cran-rcpparmadillo \
	r-cran-rcppeigen \
	r-cran-rcppgsl \
	r-cran-msm \
	r-cran-stringr \
	r-cran-xml \
	r-cran-rgl \
	r-cran-bbmisc \
	r-cran-mvtnorm \
	r-cran-checkmate \
	r-cran-ggplot2 \
	r-cran-lpsolve \
	r-cran-igraph \
	r-cran-testthat \
	r-cran-ranger \
	r-cran-lubridate \
	r-cran-mlr \
	r-cran-paramhelpers \
	r-cran-nloptr \
	r-cran-corpcor \
	r-cran-numderiv \
	r-cran-ape \
	r-cran-phytools \
	r-cran-phylobase \
	r-cran-viridis \
	r-cran-shiny \
	r-cran-desolve \
	r-cran-dplyr \
	r-cran-gridextra \
	r-cran-tidyr \
	r-cran-knitr \
	r-cran-rmarkdown \
	r-cran-pls \
	r-cran-mnormt \
	r-cran-pracma \
	r-cran-foreach \
	r-cran-doparallel \
	r-cran-iterators \
	r-cran-reshape2 \
	r-cran-vegan \
	r-cran-deldir \
	r-cran-magrittr \
	r-cran-hmisc \
	r-cran-sp \
	r-cran-zoo \
	r-cran-vioplot \
	r-cran-scatterplot3d \
	r-cran-glmnet \
	r-cran-matrixstats \
	r-cran-caret \
	r-cran-rcppeigen \
	r-cran-parallelmap \
	r-cran-gtools \
	r-cran-plyr \
	r-cran-batchjobs \
	r-cran-backports \
	r-cran-data.table \
	r-cran-rcolorbrewer \
	r-cran-earth \
	r-cran-emoa \
	r-cran-ggally \
	r-cran-kernlab \
	r-cran-nnet \
	r-cran-randomforest \
	r-cran-rgenoud \
	r-cran-e1071 \
	r-cran-statmod \
	r-cran-tgp \
	r-cran-quantreg \
	r-cran-digest \
	r-cran-expm \
	r-cran-rjava \
	r-cran-plotrix \
	r-cran-psych \
	r-cran-purrr \
	r-cran-tibble \
	r-cran-coda \
	r-cran-tmvtnorm \
	r-cran-ellipse \
	r-cran-bridgesampling \
	r-cran-roxygen2 \
	r-cran-pbivnorm \
	r-cran-devtools \
	r-cran-mda \
	r-cran-mlbench \
	r-cran-plotly \
	r-cran-shape \
	r-cran-dorng \
	r-cran-r6 \
	r-cran-reshape \
	r-cran-inline \
	r-cran-car \
	r-cran-tseries \
	r-cran-learnbayes \
	r-cran-fastmatch \
	r-cran-eaf \
	r-cran-irace \
	r-cran-testit \
	r-cran-fnn \
	r-cran-scales \
	r-cran-gam

## r-cran-ragg is not available
RUN Rscript -e 'install.packages("ragg")'

COPY ["rev_dep_docker_packages.R", "/home/docker/rev_dep_docker_packages.R"]

RUN Rscript /home/docker/rev_dep_docker_packages.R lhs


