/**
 * @file lhs_r.h
 * @author Robert Carnell
 * @copyright Copyright (c) 2013, Robert Carnell
 * 
 * @license <a href="http://www.gnu.org/licenses/gpl.html">GNU General Public License (GPL v3)</a>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef LHS_R_H
#define	LHS_R_H

#include <Rcpp.h>
#include "LHSCommonDefines.h"
#include "lhs_r_utilities.h"
#include "RStandardUniform.h"
#include "bclibVersion.h"
#include "oalibVersion.h"
#include "lhslibVersion.h"

/**
 * Improved Latin hypercube sample algorithm
 * @param n (IntegerVector length 1) number of rows / samples in the lhs
 * @param k (IntegerVector length 1) number parameters / columns in the lhs
 * @param dup (IntegerVector length 1) A factor that determines the number of candidate points used in the search.
 * @return (NumericMatrix dim n x k) an lhs
 */
RcppExport SEXP improvedLHS_cpp(SEXP n, SEXP k, SEXP dup);
/**
 * Latin hypercube sample algorithm using the maximin algorithm
 * @param n (IntegerVector length 1) number of rows / samples in the lhs
 * @param k (IntegerVector length 1) number parameters / columns in the lhs
 * @param dup (IntegerVector length 1) A factor that determines the number of candidate points used in the search.
 * @return (NumericMatrix dim n x k) an lhs
 */
RcppExport SEXP maximinLHS_cpp(SEXP n, SEXP k, SEXP dup);
/**
 * Optimal Latin hypercube sample algorithm
 * @param n (IntegerVector length 1) number of rows / samples in the lhs
 * @param k (IntegerVector length 1) number parameters / columns in the lhs
 * @param maxsweeps (IntegerVector length 1) the maximum number of sweeps to use in the algorithm
 * @param eps (NumericVector length 1) The optimal stopping criterion
 * @param bVerbose (LogicalVector length 1) should messages be printed 
 * @return (NumericMatrix dim n x k) an lhs
 */
RcppExport SEXP optimumLHS_cpp(SEXP n, SEXP k, SEXP maxsweeps, SEXP eps, 
        SEXP bVerbose);
/**
 * Optimum Latin hypercube sample with a seed sample 
 * @param n (IntegerVector length 1) number of rows / samples in the lhs
 * @param k (IntegerVector length 1) number parameters / columns in the lhs
 * @param maxsweeps (IntegerVector length 1) the maximum number of sweeps to use in the algorithm
 * @param eps (NumericVector length 1) The optimal stopping criterion
 * @param pOld (NumericMatrix dim n x k) a seed matrix
 * @param bVerbose (LogicalVector length 1) should messages be printed?
 * @return (NumericMatrix dim n x k) an lhs
 */
RcppExport SEXP optSeededLHS_cpp(SEXP n, SEXP k, SEXP maxsweeps, SEXP eps, 
        SEXP pOld, SEXP bVerbose);
/**
 * a simple random Latin hypercube sample
 * @param n (IntegerVector length 1) number of rows / samples in the lhs
 * @param k (IntegerVector length 1) number parameters / columns in the lhs
 * @param preserveDraw (LogicalVector length 1) should be same draw be taken regardless of the number of parameters selected
 * @return (NumericMatrix dim n x k) an lhs
 */
RcppExport SEXP randomLHS_cpp(SEXP n, SEXP k, SEXP preserveDraw);
/**
 * A Latin hypercube sample using a genetic algorithm
 * @param n (IntegerVector length 1) number of rows / samples in the lhs
 * @param k (IntegerVector length 1) number parameters / columns in the lhs
 * @param pop (IntegerVector length 1) the number of designs in the initial population
 * @param gen (IntegerVector length 1) the number of generations over which the algorithm is applied
 * @param pMut (NumericVector length 1) The probability with which a mutation occurs in a column of the progeny
 * @param criterium (NumericVector length 1) The optimality criterium of the algorithm.  Default is S.  Maximin is also supported
 * @param bVerbose (LogicalVector length 1) Print informational messages
 * @return (NumericMatrix dim n x k) an lhs
 */
RcppExport SEXP geneticLHS_cpp(SEXP n, SEXP k, SEXP pop, SEXP gen, SEXP pMut, 
        SEXP criterium, SEXP bVerbose);

/**
 * Get the versions of the bclib, oa, and lhslib C++ libraries
 * @return String of version information
 */
RcppExport SEXP get_library_versions();

#endif	/* LHS_R_H */
