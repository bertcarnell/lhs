## Setup

Review the notes [here](https://hub.docker.com/_/r-base)

```
sudo apt-get install docker docker.io
sudo docker pull r-base
cd ~/Documents/repositories/lhs/etc
sudo docker build --tag=lhs_r_base .
```

## Usage of the base image

```
# interactive mode
docker run -ti --rm r-base
# run a local script
#  -ti is TTY interactive
#  --rm is remove container when done
#  -v is bind mount a volume
#  -w is the working directory
#  -u is the user
sudo docker run -ti --rm -v ~/Documents/repositories:/home/docker -w /home/docker -u docker r-base R CMD build lhs
sudo docker run -ti --rm -v ~/Documents/repositories:/home/docker -w /home/docker -u docker r-base R CMD check lhs_*.tar.gz
```

## Usage of the built image for Reverse Dependency Checks

```
sudo docker run -ti --rm -v ~/Documents/repositories:/home/docker -w /home/docker -u docker lhs_r_base "/bin/bash"
# inside the docker
cd lhs/etc
Rscript lhs_rev_dep_check.R
```

#### For failed installations, check the package directly

```
# build the package from the repo
R CMD build <my package>
R CMD INSTALL <my package>_<ver>.tar.gz

cd <package>/revdep/checks/<dependency>
wget -r -l2 --accept-regex='<package>[_][0-9.-_]*[.]tar[.]gz' -R "*.txt" https://cran.r-project.org/src/contrib
mv cran.r-project.org/src/contrib/*.tar.gz .
rm -rf cran.r-project.org
R CMD check <dependency>_<rev>.tar.gz
```
