# Reverse Dependency Checks for package lhs 2021-09-30 21:07:30

## Old Results

Check results for packages in dir '/home/docker/revdep/old':

Check status summary:
                  WARN NOTE OK
  Source packages    0    1  0
  Reverse depends    4   14 16

Check results summary:
lhs ... NOTE
* checking installed package size ... NOTE
rdepends_activegp ... OK
rdepends_binaryGP ... NOTE
* checking LazyData ... NOTE
rdepends_DoE.wrapper ... NOTE
* checking LazyData ... NOTE
rdepends_DSAIDE ... NOTE
* checking installed package size ... NOTE
rdepends_DSAIRM ... OK
rdepends_DynamicGP ... OK
rdepends_EasyABC ... OK
rdepends_ENMTools ... OK
rdepends_GPfit ... OK
rdepends_GPM ... OK
rdepends_grapherator ... NOTE
* checking dependencies in R code ... NOTE
* checking LazyData ... NOTE
rdepends_hydroPSO ... OK
rdepends_imabc ... OK
rdepends_inaparc ... NOTE
* checking LazyData ... NOTE
rdepends_LVGP ... OK
rdepends_MaOEA ... NOTE
* checking LazyData ... NOTE
rdepends_mcMST ... WARN
* checking whether package ‘mcMST’ can be installed ... WARNING
* checking dependencies in R code ... NOTE
* checking LazyData ... NOTE
rdepends_mlrintermbo ... NOTE
* checking LazyData ... NOTE
rdepends_mlrMBO ... WARN
* checking whether package ‘mlrMBO’ can be installed ... WARNING
* checking LazyData ... NOTE
rdepends_nlrx ... OK
rdepends_optim.functions ... NOTE
* checking LazyData ... NOTE
rdepends_OUwie ... OK
rdepends_ParBayesianOptimization ... NOTE
* checking LazyData ... NOTE
rdepends_penalizedSVM ... NOTE
* checking dependencies in R code ... NOTE
rdepends_poems ... NOTE
* checking dependencies in R code ... NOTE
rdepends_profExtrema ... OK
rdepends_rrepast ... OK
rdepends_sensobol ... OK
rdepends_tools4uplift ... OK
rdepends_tramnet ... WARN
* checking whether package ‘tramnet’ can be installed ... WARNING
rdepends_TREXr ... NOTE
* checking dependencies in R code ... NOTE
rdepends_varycoef ... WARN
* checking whether package ‘varycoef’ can be installed ... WARNING
* checking dependencies in R code ... NOTE
rdepends_yager ... NOTE
* checking LazyData ... NOTE
rdepends_yap ... NOTE
* checking LazyData ... NOTE

## New Results

Check results for packages in dir '/home/docker/revdep/new':

Check status summary:
                  WARN NOTE OK
  Source packages    0    1  0
  Reverse depends    4   14 16

Check results summary:
lhs ... NOTE
* checking installed package size ... NOTE
rdepends_activegp ... OK
rdepends_binaryGP ... NOTE
* checking LazyData ... NOTE
rdepends_DoE.wrapper ... NOTE
* checking LazyData ... NOTE
rdepends_DSAIDE ... NOTE
* checking installed package size ... NOTE
rdepends_DSAIRM ... OK
rdepends_DynamicGP ... OK
rdepends_EasyABC ... OK
rdepends_ENMTools ... OK
rdepends_GPfit ... OK
rdepends_GPM ... OK
rdepends_grapherator ... NOTE
* checking dependencies in R code ... NOTE
* checking LazyData ... NOTE
rdepends_hydroPSO ... OK
rdepends_imabc ... OK
rdepends_inaparc ... NOTE
* checking LazyData ... NOTE
rdepends_LVGP ... OK
rdepends_MaOEA ... NOTE
* checking LazyData ... NOTE
rdepends_mcMST ... WARN
* checking whether package ‘mcMST’ can be installed ... WARNING
* checking dependencies in R code ... NOTE
* checking LazyData ... NOTE
rdepends_mlrintermbo ... NOTE
* checking LazyData ... NOTE
rdepends_mlrMBO ... WARN
* checking whether package ‘mlrMBO’ can be installed ... WARNING
* checking LazyData ... NOTE
rdepends_nlrx ... OK
rdepends_optim.functions ... NOTE
* checking LazyData ... NOTE
rdepends_OUwie ... OK
rdepends_ParBayesianOptimization ... NOTE
* checking LazyData ... NOTE
rdepends_penalizedSVM ... NOTE
* checking dependencies in R code ... NOTE
rdepends_poems ... NOTE
* checking dependencies in R code ... NOTE
rdepends_profExtrema ... OK
rdepends_rrepast ... OK
rdepends_sensobol ... OK
rdepends_tools4uplift ... OK
rdepends_tramnet ... WARN
* checking whether package ‘tramnet’ can be installed ... WARNING
rdepends_TREXr ... NOTE
* checking dependencies in R code ... NOTE
rdepends_varycoef ... WARN
* checking whether package ‘varycoef’ can be installed ... WARNING
* checking dependencies in R code ... NOTE
rdepends_yager ... NOTE
* checking LazyData ... NOTE
rdepends_yap ... NOTE
* checking LazyData ... NOTE

## Differences

### mcMST

- Version:  1.0.1
- Check:  whether package can be installed
- Status:  WARNING
- Output: Found the following significant warnings:
  Warning: no DISPLAY variable so Tk is not available
See ‘/home/docker/revdep/new/mcMST.Rcheck/00install.out’ for details.
- Flags:  --no-manual --no-build-vignettes

### mlrMBO

- Version:  1.1.5
- Check:  whether package can be installed
- Status:  WARNING
- Output: Found the following significant warnings:
  Warning: no DISPLAY variable so Tk is not available
See ‘/home/docker/revdep/new/mlrMBO.Rcheck/00install.out’ for details.
- Flags:  --no-manual --no-build-vignettes

### tramnet

- Version:  0.0-6
- Check:  whether package can be installed
- Status:  WARNING
- Output: Found the following significant warnings:
  Warning: no DISPLAY variable so Tk is not available
See ‘/home/docker/revdep/new/tramnet.Rcheck/00install.out’ for details.
- Flags:  --no-manual --no-build-vignettes

### varycoef

- Version:  0.3.1
- Check:  whether package can be installed
- Status:  WARNING
- Output: Found the following significant warnings:
  Warning: no DISPLAY variable so Tk is not available
See ‘/home/docker/revdep/new/varycoef.Rcheck/00install.out’ for details.
- Flags:  --no-manual --no-build-vignettes

## Alternate Differences

Package: mcMST
Check: whether package can be installed
Old result: WARNING
  Found the following significant warnings:
    Warning: no DISPLAY variable so Tk is not available
  See ‘/home/docker/revdep/old/mcMST.Rcheck/00install.out’ for details.
New result: WARNING
  Found the following significant warnings:
    Warning: no DISPLAY variable so Tk is not available
  See ‘/home/docker/revdep/new/mcMST.Rcheck/00install.out’ for details.

Package: mlrMBO
Check: whether package can be installed
Old result: WARNING
  Found the following significant warnings:
    Warning: no DISPLAY variable so Tk is not available
  See ‘/home/docker/revdep/old/mlrMBO.Rcheck/00install.out’ for details.
New result: WARNING
  Found the following significant warnings:
    Warning: no DISPLAY variable so Tk is not available
  See ‘/home/docker/revdep/new/mlrMBO.Rcheck/00install.out’ for details.

Package: tramnet
Check: whether package can be installed
Old result: WARNING
  Found the following significant warnings:
    Warning: no DISPLAY variable so Tk is not available
  See ‘/home/docker/revdep/old/tramnet.Rcheck/00install.out’ for details.
New result: WARNING
  Found the following significant warnings:
    Warning: no DISPLAY variable so Tk is not available
  See ‘/home/docker/revdep/new/tramnet.Rcheck/00install.out’ for details.

Package: varycoef
Check: whether package can be installed
Old result: WARNING
  Found the following significant warnings:
    Warning: no DISPLAY variable so Tk is not available
  See ‘/home/docker/revdep/old/varycoef.Rcheck/00install.out’ for details.
New result: WARNING
  Found the following significant warnings:
    Warning: no DISPLAY variable so Tk is not available
  See ‘/home/docker/revdep/new/varycoef.Rcheck/00install.out’ for details.
