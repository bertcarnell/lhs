# Reverse Dependency Checks for package lhs 2021-09-29 21:49:31

## Old Results

Check results for packages in dir '/home/docker/revdep/old':

Check status summary:
                  WARN NOTE OK
  Source packages    0    1  0
  Reverse depends    1    2  3

Check results summary:
lhs ... NOTE
* checking installed package size ... NOTE
rdepends_acebayes ... OK
rdepends_ATmet ... OK
rdepends_mtk ... NOTE
* checking dependencies in R code ... NOTE
* checking R code for possible problems ... NOTE
* checking data for non-ASCII characters ... NOTE
rdepends_netgen ... NOTE
* checking LazyData ... NOTE
rdepends_spsh ... OK
rdepends_tuneRanger ... WARN
* checking whether package ‘tuneRanger’ can be installed ... WARNING
* checking LazyData ... NOTE

## New Results

Check results for packages in dir '/home/docker/revdep/new':

Check status summary:
                  WARN NOTE OK
  Source packages    0    1  0
  Reverse depends    1    2  3

Check results summary:
lhs ... NOTE
* checking installed package size ... NOTE
rdepends_acebayes ... OK
rdepends_ATmet ... OK
rdepends_mtk ... NOTE
* checking dependencies in R code ... NOTE
* checking R code for possible problems ... NOTE
* checking data for non-ASCII characters ... NOTE
rdepends_netgen ... NOTE
* checking LazyData ... NOTE
rdepends_spsh ... OK
rdepends_tuneRanger ... WARN
* checking whether package ‘tuneRanger’ can be installed ... WARNING
* checking LazyData ... NOTE

## Differences

### tuneRanger

- Version:  0.5
- Check:  whether package can be installed
- Status:  WARNING
- Output: Found the following significant warnings:
  Warning: no DISPLAY variable so Tk is not available
See ‘/home/docker/revdep/new/tuneRanger.Rcheck/00install.out’ for details.
- Flags:  

## Alternate Differences

Package: tuneRanger
Check: whether package can be installed
Old result: WARNING
  Found the following significant warnings:
    Warning: no DISPLAY variable so Tk is not available
  See ‘/home/docker/revdep/old/tuneRanger.Rcheck/00install.out’ for details.
New result: WARNING
  Found the following significant warnings:
    Warning: no DISPLAY variable so Tk is not available
  See ‘/home/docker/revdep/new/tuneRanger.Rcheck/00install.out’ for details.
