# Valgrind checks on Linux

Obtain a r-devel docker image from [here](https://github.com/wch/r-debug)

## Operations

### Check for previous running docker images and processes

```Shell
sudo docker ps -a
sudo docker rm <name>

sudo docker images
sudo docker rmi <imageid>
```

### Pull for the first time or update the image

```Shell
sudo docker pull wch1/r-debug
```

### Start the container

```Shell
sudo docker run --rm -ti --security-opt seccomp=unconfined -v ~/repositories:/mydir --name rdevel wch1/r-debug
```
- `--rm` Automatically clean up the container and remove the file system
- `-ti`  pseudo-tty and keep STDIN open
- `--security-opt="seccomp=unconfined"` Turn off seccomp confinement for the container
- `-v` attach a volume <host_dir>:<container_dir>

#### Inside the container

```Shell
apt-get install libgmp-dev qpdf
```

#### Valgrind

```Shell
RDvalgrind -e 'install.packages(c("Rcpp", "testthat", "assertthat", "DoE.base", "knitr", "rmarkdown", "covr"))'

# use valgrind with R CMD check
RDvalgrind CMD check --use-valgrind /mydir/lhs_<version>.tar.gz
vi lhs.Rcheck/tests/testthat.Rout

RDvalgrind CMD INSTALL /mydir/lhs_<version>.tar.gz

# use valgrind with the testthat tests only with options
cd /mydir/lhs/tests
VALGRIND_OPTS="--leak-check=full --track-origins=yes";RDvalgrind -d valgrind -f testthat.R
```

#### Address Sanitizers

```Shell
RDsan -e 'install.packages(c("Rcpp", "testthat", "assertthat", "DoE.base", "knitr", "rmarkdown", "covr"))'

RDsan CMD check /mydir/lhs_<version>.tar.gz
```

#### Clang Address Sanitizers

```Shell
RDcsan -e 'install.packages(c("Rcpp", "testthat", "assertthat", "DoE.base", "knitr", "rmarkdown", "covr"))'

RDcsan CMD check /mydir/lhs_<version>.tar.gz
```


