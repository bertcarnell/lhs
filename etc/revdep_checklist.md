# Reverse Dependency Checklist

## Collect dependencies

- In RStudio, run `revdep_write_dockerfile_r_install.R`
- Copy the packages to be built into `Dockerfile` from `temporary_install_output.txt`

## Build Docker Images

- `docker build --no-cache -t bertcarnell/lhs_revdep --progress=plain etc`

- `docker push bertcarnell/lhs_revdep`

## Local Operation

- `docker run -ti --rm -v /mnt/c/repositories:/home/docker -w /home/docker -u docker --name build_lhs lhs_revdep R CMD build lhs`
- `docker run -ti --rm -v /mnt/c/repositories:/home/docker -w /home/docker -u docker --name lhs_revdep_check lhs_revdep Rscript /home/docker/lhs/etc/lhs_rev_dep_check.R`

## Github Actions

