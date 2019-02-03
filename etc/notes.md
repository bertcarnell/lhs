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
docker run -ti --rm -v ~/Documents/repositories:/home/docker -w /home/docker -u docker r-base R CMD build lhs
docker run -ti --rm -v ~/Documents/repositories:/home/docker -w /home/docker -u docker r-base R CMD check lhs_*.tar.gz
```

## Usage of the built image

```
docker run -ti --rm -v ~/Documents/repositories:/home/docker -w /home/docker -u docker lhs_r_base "/bin/bash"
# inside the docker
cd lhs
R
revdepcheck::revdep_check(pkg='.', dependencies='Depends', num_workers=1)
# revdep folder may be owned by root, use sudo chown -hR pi revdep from outside of the docker to allow docker access
revdepcheck::revdep_summary()
revdepcheck::revdep_reset()
```

## For failed installations, check the package directly

```
cd <package>/revdep/checks/<dependency>
wget https://cran.r-project.org/src/contrib/<dependency>_<rev>.tar.gz
R CMD check <dependency>_<rev>.tar.gz
```

