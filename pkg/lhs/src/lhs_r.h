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
#include "CommonDefines.h"
#include "lhs_r_utilities.h"
#include "RStandardUniform.h"

/**
 * Improved Latin hypercube sample algorithm
 * @param n number of rows / samples in the lhs
 * @param k number parameters / columns in the lhs
 * @param dup A factor that determines the number of candidate points used in the search.
 * @return a NumericMatrix of an lhs
 */
RcppExport SEXP /*double matrix*/ improvedLHS_cpp(SEXP /*int*/ n, SEXP /*int*/ k, 
        SEXP /*int*/ dup);
/**
 * Latin hypercube sample algorithm using the maximin algorithm
 * @param n number of rows / samples in the lhs
 * @param k number parameters / columns in the lhs
 * @param dup A factor that determines the number of candidate points used in the search.
 * @return a NumericMatrix of an lhs
 */
RcppExport SEXP /*double matrix*/ maximinLHS_cpp(SEXP /*int*/ n, SEXP /*int*/ k, 
        SEXP /*int*/ dup);
/**
 * Optimal Latin hypercube sample algorithm
 * @param n number of rows / samples in the lhs
 * @param k number parameters / columns in the lhs
 * @param maxSweeps the maximum number of sweeps to use in the algorithm
 * @param eps The optimal stopping criterion
 * @param bVerbose should messages be printed 
 * @return a NumericMatrix of an lhs
 */
RcppExport SEXP /*double matrix*/ optimumLHS_cpp(SEXP /*int*/ n, SEXP /*int*/ k, 
        SEXP /*int*/ maxsweeps, SEXP /*double*/ eps, SEXP /*bool*/ bVerbose);
/**
 * Optimum Latin hypercube sample with a seed sample 
 * @param n number of rows / samples in the lhs
 * @param k number parameters / columns in the lhs
 * @param maxSweeps the maximum number of sweeps to use in the algorithm
 * @param eps The optimal stopping criterion
 * @param pOld a seed matrix
 * @param bVerbose should messages be printed?
 * @return a NumericMatrix of an lhs
 */
RcppExport SEXP /*double matrix*/ optSeededLHS_cpp(SEXP /*int*/ n, SEXP /*int*/ k, 
        SEXP /*int*/ maxsweeps, SEXP /*double*/ eps, SEXP /*int**/ pOld,
        SEXP /*bool*/ bVerbose);
/**
 * a simple random Latin hypercube sample
 * @param n number of rows / samples in the lhs
 * @param k number parameters / columns in the lhs
 * @param preserveDraw should be same draw be taken regardless of the number of parameters selected
 * @return a NumericMatrix of an lhs
 */
RcppExport SEXP randomLHS_cpp(SEXP n, SEXP k, SEXP preserveDraw);
/**
 * A Latin hypercube sample using a genetic algorithm
 * @param n number of rows / samples in the lhs
 * @param k number parameters / columns in the lhs
 * @param pop
 * @param gen
 * @param pMut
 * @param criterium
 * @param bVerbose
 * @return a NumericMatrix of an lhs
 */
RcppExport SEXP geneticLHS_cpp(SEXP /*int*/ n, SEXP /*int*/ k, SEXP /*int*/ pop,
        SEXP /*int*/ gen, SEXP /*double*/ pMut, SEXP criterium,
        SEXP /*bool*/ bVerbose);

#endif	/* LHS_R_H */
