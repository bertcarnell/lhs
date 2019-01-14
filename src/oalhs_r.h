/**
 * @file oalhs_r.h
 * @author Robert Carnell
 * @copyright Copyright (c) 2019, Robert Carnell
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

#ifndef OALHS_R_H
#define	OALHS_R_H

#include <Rcpp.h>
#include "oa_r_utils.h"
#include "oaLHS.h"
#include "RStandardUniform.h"

/**
 * Create a Latin hypercube sample from an orthogonal array
 *
 * @param n the number of rows in the LHS
 * @param k the number of parameters or columns in the LHS
 * @param oa the orthogonal array to be used as the basis for the LHS
 * @param bverbose should information be printed d
 * @return a numeric (double) matrix
 */
RcppExport SEXP /*double matrix*/ oa_to_lhs(SEXP /*int*/ n, SEXP /*int*/ k,
                                        SEXP /*int matrix*/ oa, SEXP /*bool*/ bverbose);


/**
 * Create an Orthogonal Array Latin hypercube sample
 *
 * @param n the number of rows in the LHS
 * @param k the number of parameters or columns in the LHS
 * @param bChooseLargerDesign should a larger design than the one requested be created to match the oa generator
 * @param bverbose should information be printed d
 * @return a numeric (double) matrix
 */
RcppExport SEXP /*double matrix*/ create_oalhs(SEXP /*int*/ n, SEXP /*int*/ k,
                                               SEXP /*bool*/ bChooseLargerDesign,
                                               SEXP /*bool*/ bverbose);

#endif	/* OALHS_R_H */

