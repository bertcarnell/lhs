## Setup

Review the notes [here](https://hub.docker.com/_/r-base)
```
sudo apt-get install docker docker.io
docker pull r-base
```

## Usage

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

```
docker build --tag=lhs_r_base .
docker run -ti --rm lhs_r_base "/bin/bash"
```




