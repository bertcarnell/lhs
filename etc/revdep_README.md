# Reverse Dependency Checks for package  lhs 
2019-02-12 03:14:32 

##  acebayes   1.6.0 

#### No Change In  Errors 

 

#### No Change In  Warnings 

checking compilation flags used ... WARNING
Compilation used the following non-portable flag(s):
  ‘-Wdate-time’ ‘-Werror=format-security’ ‘-Wformat’ checking compiled code ... OK
 WARNING
‘qpdf’ is needed for checks on size reduction of PDFs 

#### No Change In  Notes 

checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Antony M. Overstall <A.M.Overstall@soton.ac.uk>’

The Date field is over a month old.

This build time stamp is over a month old. checking installed package size ... NOTE
  installed size is  5.0Mb
  sub-directories of 1Mb or more:
    libs   3.0Mb
    R      1.4Mb 

##  ATmet   1.2 

#### No Change In  Errors 

 

#### No Change In  Warnings 

 

####  Notes 

- Old version:

 checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Alexandre Allard <alexandre.allard@lne.fr>’

The Description field should not start with the package name,
  'This package' or similar.

The Date field is over a month old.

This build time stamp is over a month old. checking R code for possible problems ... NOTE
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
to your NAMESPACE file. checking examples ... NOTE
Examples with CPU or elapsed time > 5s
               user system elapsed
ATmet-package 8.304  0.012   8.316
LHSdesign     6.622  0.003   6.626 

- New version:

 checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Alexandre Allard <alexandre.allard@lne.fr>’

The Description field should not start with the package name,
  'This package' or similar.

The Date field is over a month old.

This build time stamp is over a month old. checking R code for possible problems ... NOTE
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
to your NAMESPACE file. checking examples ... NOTE
Examples with CPU or elapsed time > 5s
               user system elapsed
ATmet-package 8.320  0.008   8.328
LHSdesign     6.633  0.000   6.634 

##  BayesianTools   0.1.6 

#### No Change In  Errors 

 

#### No Change In  Warnings 

checking compilation flags used ... WARNING
Compilation used the following non-portable flag(s):
  ‘-Wdate-time’ ‘-Werror=format-security’ ‘-Wformat’ checking compiled code ... OK
 WARNING
‘qpdf’ is needed for checks on size reduction of PDFs 

####  Notes 

- Old version:

 checking examples ... NOTE
Examples with CPU or elapsed time > 5s
                    user system elapsed
marginalLikelihood 4.729  0.382   5.111 

##  DiceOptim   2.0 

#### No Change In  Errors 

 

#### No Change In  Warnings 

checking compilation flags used ... WARNING
Compilation used the following non-portable flag(s):
  ‘-Wdate-time’ ‘-Werror=format-security’ ‘-Wformat’ 

#### No Change In  Notes 

checking CRAN incoming feasibility ... NOTE
Maintainer: ‘V. Picheny <victor.picheny@toulouse.inra.fr>’

The Date field is over a month old.

This build time stamp is over a month old. checking compiled code ... NOTE
File ‘DiceOptim/libs/DiceOptim.so’:
  Found no calls to: ‘R_registerRoutines’, ‘R_useDynamicSymbols’

It is good practice to register native routines and to disable symbol
search.

See ‘Writing portable packages’ in the ‘Writing R Extensions’ manual. 

##  flacco   1.7 

#### No Change In  Errors 

 

#### No Change In  Warnings 

checking data for ASCII and uncompressed saves ... OK
 WARNING
‘qpdf’ is needed for checks on size reduction of PDFs 

#### No Change In  Notes 

checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Pascal Kerschke <kerschke@uni-muenster.de>’

The Date field is over a month old.

This build time stamp is over a month old. 

##  GAparsimony   0.9.2 

#### No Change In  Errors 

 

#### No Change In  Warnings 

 

####  Notes 

- Old version:

 checking CRAN incoming feasibility ... NOTE
Maintainer: ‘F.J. Martinez-de-Pison <fjmartin@unirioja.es>’

The Date field is over a month old.

This build time stamp is over a month old. checking examples ... NOTE
Examples with CPU or elapsed time > 5s
              user system elapsed
ga_parsimony 7.504  0.152   7.656
** found \donttest examples: check also with --run-donttest 

- New version:

 checking CRAN incoming feasibility ... NOTE
Maintainer: ‘F.J. Martinez-de-Pison <fjmartin@unirioja.es>’

The Date field is over a month old.

This build time stamp is over a month old. checking examples ... NOTE
Examples with CPU or elapsed time > 5s
              user system elapsed
ga_parsimony 7.528  0.149   7.676
** found \donttest examples: check also with --run-donttest 

##  hetGP   1.1.1 

#### No Change In  Errors 

 

#### No Change In  Warnings 

checking compilation flags used ... WARNING
Compilation used the following non-portable flag(s):
  ‘-Wdate-time’ ‘-Werror=format-security’ ‘-Wformat’ checking compiled code ... OK
 WARNING
‘qpdf’ is needed for checks on size reduction of PDFs 

####  Notes 

- Old version:

 checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Mickael Binois <mbinois@mcs.anl.gov>’

The Date field is over a month old.

This build time stamp is over a month old. checking installed package size ... NOTE
  installed size is  6.2Mb
  sub-directories of 1Mb or more:
    doc    1.0Mb
    libs   4.1Mb checking examples ... NOTE
Examples with CPU or elapsed time > 5s
             user system elapsed
ato         8.441  0.052   8.493
IMSPE_optim 7.202  0.008   7.211
SIR         5.379  0.020   5.399 

- New version:

 checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Mickael Binois <mbinois@mcs.anl.gov>’

The Date field is over a month old.

This build time stamp is over a month old. checking installed package size ... NOTE
  installed size is  6.2Mb
  sub-directories of 1Mb or more:
    doc    1.0Mb
    libs   4.1Mb checking examples ... NOTE
Examples with CPU or elapsed time > 5s
             user system elapsed
ato         9.036  0.036   9.072
IMSPE_optim 6.782  0.012   6.794
SIR         5.214  0.004   5.218 

##  IGP   0.1.0 

#### No Change In  Errors 

 

#### No Change In  Warnings 

 

#### No Change In  Notes 

checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Collin Erickson <collinberickson@gmail.com>’

This build time stamp is over a month old. 

##  kergp   0.4.0 

#### No Change In  Errors 

 

#### No Change In  Warnings 

checking compilation flags used ... WARNING
Compilation used the following non-portable flag(s):
  ‘-Wdate-time’ ‘-Werror=format-security’ ‘-Wformat’ checking compiled code ... OK
 WARNING
‘qpdf’ is needed for checks on size reduction of PDFs 

#### No Change In  Notes 

checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Olivier Roustant <roustant@emse.fr>’

The Date field is over a month old.

This build time stamp is over a month old. 

##  laGP   1.5-3 

#### No Change In  Errors 

 

#### No Change In  Warnings 

checking compilation flags used ... WARNING
Compilation used the following non-portable flag(s):
  ‘-Wdate-time’ ‘-Werror=format-security’ ‘-Wformat’ checking compiled code ... OK
 WARNING
‘qpdf’ is needed for checks on size reduction of PDFs 

####  Notes 

- Old version:

 checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Robert B. Gramacy  <rbg@vt.edu>’

The Date field is over a month old.

This build time stamp is over a month old. checking examples ... NOTE
Examples with CPU or elapsed time > 5s
       user system elapsed
alcGP 8.382  0.196   8.578 

- New version:

 checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Robert B. Gramacy  <rbg@vt.edu>’

The Date field is over a month old.

This build time stamp is over a month old. checking examples ... NOTE
Examples with CPU or elapsed time > 5s
       user system elapsed
alcGP 8.438  0.176   8.615 

##  maximin   1.0-2 

#### No Change In  Errors 

 

#### No Change In  Warnings 

 

#### No Change In  Notes 

 

##  mistat   1.0-5 

#### No Change In  Errors 

 

#### No Change In  Warnings 

 

#### No Change In  Notes 

checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Daniele Amberti <daniele.amberti@gmail.com>’

The Date field is over a month old.

This build time stamp is over a month old. 

##  moko   1.0.1 

#### No Change In  Errors 

 

#### No Change In  Warnings 

checking data for ASCII and uncompressed saves ... OK
 WARNING
‘qpdf’ is needed for checks on size reduction of PDFs 

####  Notes 

- Old version:

 checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Adriano Passos <adriano.utfpr@gmail.com>’

This build time stamp is over a month old. checking examples ... NOTE
Examples with CPU or elapsed time > 5s
      user system elapsed
EHVI 6.425  0.124   6.549 

- New version:

 checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Adriano Passos <adriano.utfpr@gmail.com>’

This build time stamp is over a month old. checking examples ... NOTE
Examples with CPU or elapsed time > 5s
      user system elapsed
EHVI 6.447  0.077   6.523 

##  mtk   1.0 

#### No Change In  Errors 

 

#### No Change In  Warnings 

 

#### No Change In  Notes 

checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Juhui WANG <Juhui.Wang@jouy.inra.fr>’

The Title field should be in title case, current version then in title case:
‘Mexico ToolKit library (MTK)’
‘Mexico ToolKit Library (MTK)’

The Description field should not start with the package name,
  'This package' or similar.

The Date field is over a month old.

This build time stamp is over a month old. checking dependencies in R code ... NOTE
'library' or 'require' call to ‘MASS’ in package code.
  Please use :: or requireNamespace() instead.
  See section 'Suggested packages' in the 'Writing R Extensions' manual. checking R code for possible problems ... NOTE
basicMonteCarlo: no visible global function definition for ‘runif’
Designer.sobol: no visible global function definition for ‘runif’
lhs003: no visible global function definition for ‘runif’
plmm.mtk : GenereXplmm: no visible binding for global variable ‘poly’
plmm.mtk : calc.plm: no visible global function definition for ‘lm.fit’
plmm.mtk: no visible global function definition for ‘var’
plmm.mtk: no visible global function definition for ‘lm’
plmm.mtk: no visible global function definition for ‘formula’
plmm.mtk: no visible global function definition for ‘update’
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
  importFrom("graphics", "abline", "barplot", "legend", "par",
             "segments", "title")
  importFrom("grDevices", "dev.new")
  importFrom("stats", "formula", "lm", "lm.fit", "poly", "runif",
             "update", "var")
to your NAMESPACE file. 

##  netgen   1.3 

#### No Change In  Errors 

 

#### No Change In  Warnings 

 

#### No Change In  Notes 

checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Jakob Bossek <j.bossek@gmail.com>’

The Date field is over a month old.

This build time stamp is over a month old. 

##  ParamHelpers   1.12 

#### No Change In  Errors 

 

#### No Change In  Warnings 

checking compilation flags used ... WARNING
Compilation used the following non-portable flag(s):
  ‘-Wdate-time’ ‘-Werror=format-security’ ‘-Wformat’ 

#### No Change In  Notes 

 

##  SACOBRA   0.7 

#### No Change In  Errors 

 

#### No Change In  Warnings 

 

####  Notes 

- Old version:

 checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Samineh Bagheri <samineh.bagheri@fh-koeln.de>’

The Date field is over a month old.

This build time stamp is over a month old. checking examples ... NOTE
Examples with CPU or elapsed time > 5s
            user system elapsed
multiCOBRA 6.557  0.024   6.581 

- New version:

 checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Samineh Bagheri <samineh.bagheri@fh-koeln.de>’

The Date field is over a month old.

This build time stamp is over a month old. checking examples ... NOTE
Examples with CPU or elapsed time > 5s
           user system elapsed
multiCOBRA 6.65  0.027   6.678 

##  tuneRanger   0.4 

#### No Change In  Errors 

 

#### No Change In  Warnings 

 

#### No Change In  Notes 

 

##  vdg   1.2.0 

#### No Change In  Errors 

 

#### No Change In  Warnings 

checking DESCRIPTION meta-information ... WARNING
Dependence on R version ‘3.3.1’ not with patchlevel 0 checking compiled code ... NOTE
File ‘vdg/libs/vdg.so’:
  Found no calls to: ‘R_registerRoutines’, ‘R_useDynamicSymbols’

It is good practice to register native routines and to disable symbol
search.

See ‘Writing portable packages’ in the ‘Writing R Extensions’ manual.
 WARNING
‘qpdf’ is needed for checks on size reduction of PDFs 

#### No Change In  Notes 

checking CRAN incoming feasibility ... NOTE
Maintainer: ‘Pieter Schoonees <schoonees@gmail.com>’

The Date field is over a month old.

This build time stamp is over a month old. checking compiled code ... NOTE
File ‘vdg/libs/vdg.so’:
  Found no calls to: ‘R_registerRoutines’, ‘R_useDynamicSymbols’

It is good practice to register native routines and to disable symbol
search.

See ‘Writing portable packages’ in the ‘Writing R Extensions’ manual.
 WARNING
‘qpdf’ is needed for checks on size reduction of PDFs 

