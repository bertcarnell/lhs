# ATmet

Version: 1.2

## In both

*   checking R code for possible problems ... NOTE
    ```
    LHSdesign: no visible global function definition for ‘qnorm’
    LHSdesign: no visible global function definition for ‘qunif’
    LHSdesign: no visible global function definition for ‘qt’
    MCdesign: no visible global function definition for ‘rnorm’
    MCdesign: no visible global function definition for ‘runif’
    MCdesign: no visible global function definition for ‘rt’
    Undefined global functions or variables:
      qnorm qt qunif rnorm rt runif
    Consider adding
      importFrom("stats", "qnorm", "qt", "qunif", "rnorm", "rt", "runif")
    to your NAMESPACE file.
    ```

# GAparsimony

Version: 0.9.2

## In both

*   checking package dependencies ... NOTE
    ```
    Package suggested but not available for checking: ‘doRNG’
    ```

# grapherator

Version: 1.0.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘reshape2’
      All declared Imports should be used.
    ```

# hetGP

Version: 1.1.1

## In both

*   R CMD check timed out
    

*   checking installed package size ... NOTE
    ```
      installed size is  5.1Mb
      sub-directories of 1Mb or more:
        doc    1.0Mb
        libs   3.0Mb
    ```

# hydroPSO

Version: 0.4-1

## In both

*   checking whether package ‘hydroPSO’ can be installed ... WARNING
    ```
    Found the following significant warnings:
      Warning: no DISPLAY variable so Tk is not available
    See ‘/home/pi/Documents/repositories/lhs/revdep/checks/hydroPSO/new/hydroPSO.Rcheck/00install.out’ for details.
    ```

# kernDeepStackNet

Version: 2.0.2

## In both

*   checking installed package size ... NOTE
    ```
      installed size is  6.3Mb
      sub-directories of 1Mb or more:
        libs   5.9Mb
    ```

# laGP

Version: 1.5-3

## In both

*   R CMD check timed out
    

# mcMST

Version: 1.0.1

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘parallelMap’ ‘reshape2’
      All declared Imports should be used.
    ```

# metagen

Version: 1.0

## In both

*   checking R code for possible problems ... NOTE
    ```
    ...
    pivotalStream: no visible global function definition for ‘rchisq’
    pivotalStream : <anonymous>: no visible global function definition for
      ‘rchisq’
    pivotalStream: no visible global function definition for ‘rnorm’
    rBinomGauss: no visible global function definition for ‘rnorm’
    rBinomGauss: no visible global function definition for ‘rbinom’
    rD: no visible global function definition for ‘rchisq’
    rY: no visible global function definition for ‘rnorm’
    render: no visible global function definition for ‘pdf’
    render: no visible global function definition for ‘dev.off’
    renderSVG: no visible global function definition for ‘svg’
    renderSVG: no visible global function definition for ‘dev.off’
    Undefined global functions or variables:
      data dev.off pdf qchisq qnorm qt quantile rbinom rchisq rnorm svg
      uniroot var
    Consider adding
      importFrom("grDevices", "dev.off", "pdf", "svg")
      importFrom("stats", "qchisq", "qnorm", "qt", "quantile", "rbinom",
                 "rchisq", "rnorm", "uniroot", "var")
      importFrom("utils", "data")
    to your NAMESPACE file.
    ```

# mistat

Version: 1.0-5

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘grDevices’
      All declared Imports should be used.
    ```

# mlrMBO

Version: 1.1.2

## In both

*   checking package dependencies ... NOTE
    ```
    Packages suggested but not available for checking: ‘earth’ ‘party’
    ```

# mtk

Version: 1.0

## In both

*   checking dependencies in R code ... NOTE
    ```
    'library' or 'require' call to ‘MASS’ in package code.
      Please use :: or requireNamespace() instead.
      See section 'Suggested packages' in the 'Writing R Extensions' manual.
    ```

*   checking R code for possible problems ... NOTE
    ```
    ...
    plmm.mtk: no visible global function definition for ‘stepAIC’
    plot.plmm: no visible global function definition for ‘par’
    plot.plmm: no visible global function definition for ‘barplot’
    plot.plmm: no visible global function definition for ‘segments’
    plot.plmm: no visible global function definition for ‘abline’
    plot.plmm: no visible global function definition for ‘title’
    plot.plmm: no visible global function definition for ‘legend’
    plot.regressionSI: no visible global function definition for ‘par’
    plot.regressionSI: no visible global function definition for ‘title’
    plot.regressionSI: no visible global function definition for ‘abline’
    plot,mtkProcess: no visible global function definition for ‘dev.new’
    Undefined global functions or variables:
      abline barplot dev.new formula legend lm lm.fit par poly runif
      segments stepAIC title update var
    Consider adding
      importFrom("grDevices", "dev.new")
      importFrom("graphics", "abline", "barplot", "legend", "par",
                 "segments", "title")
      importFrom("stats", "formula", "lm", "lm.fit", "poly", "runif",
                 "update", "var")
    to your NAMESPACE file.
    ```

*   checking data for non-ASCII characters ... NOTE
    ```
      Note: found 2 marked UTF-8 strings
    ```

# penalizedSVM

Version: 1.1.2

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘lhs’
      All declared Imports should be used.
    ```

# spartan

Version: 3.0.2

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespace in Imports field not imported from: ‘gplots’
      All declared Imports should be used.
    ```

# suropt

Version: 0.1.1

## In both

*   checking dependencies in R code ... NOTE
    ```
    Namespaces in Imports field not imported from:
      ‘DiceOptim’ ‘GPareto’ ‘rgenoud’
      All declared Imports should be used.
    ```

