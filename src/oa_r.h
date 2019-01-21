/**
 * @file oa_r.h
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

#ifndef OA_R_H
#define	OA_R_H

#include <sstream>
#include <algorithm>
#include <Rcpp.h>
#include "COrthogonalArray.h"
#include "matrix.h"
#include "oa_r_utils.h"

/**
 * An entry point for a set of Orthogonal Array algorithms
 * 
 * @see oacpp::COrthogonalArray::bose
 * @see oacpp::COrthogonalArray::bosebush
 * @see oacpp::COrthogonalArray::bush
 * @see oacpp::COrthogonalArray::addelkemp
 * @see oacpp::COrthogonalArray::addelkemp3
 * @todo test if q, ncol, n is a vector, Rcpp::as<int> should throw
 * @todo test of NA's are not caught as expected
 * @todo test if infinities are not caught as expected
 * @todo do tests in c++ for all to determine what must be checked in R
 * @param type The type of orthogonal array algorithm to use <ul><li>bose</li><li>bosebush</li><li>bush</li><li>addelkemp</li><li>addelkemp3</li></ul>
 * @param q the number of symbols in the array
 * @param ncol the number of columns in the array
 * @param bRandom whether the array should be randomized
 * @return an integer matrix
 */
RcppExport SEXP /*int matrix*/ oa_type1(SEXP /*char*/ type, SEXP /*int*/ q, SEXP /*int*/ ncol, SEXP /*bool*/ bRandom);
/**
 * An entry point for a set of Orthogonal Array algorithms
 * @see oacpp::COrthogonalArray::busht
 * @see oacpp::COrthogonalArray::bosebushl
 * @see oacpp::COrthogonalArray::addelkempn
 * @param type The type of orthogonal array algorithm to use <ul><li>busht</li><li>bosebushl</li><li>addelkempn</li></ul>
 * @param int1 a parameter that depends on the context <ul><li>busht: the strength</li><li>bosebush: lambda</li><li>addelkemp: the exponent on q</li></ul>
 * @param q the number of symbols in the array
 * @param ncol the number of columns in the array
 * @param bRandom whether the array should be randomized
 * @return an integer matrix
 */
RcppExport SEXP /*int matrix*/ oa_type2(SEXP /*char*/ type, SEXP /*int*/ int1, SEXP /*int*/ q, SEXP /*int*/ ncol, SEXP /*bool*/ bRandom);

namespace typeConstants
{
	/** bush algorithm indicator */
    const char * BUSH = "bush";
	/** bose algorithm indicator */
    const char * BOSE = "bose";
	/** bosebush algorithm indicator */
    const char * BOSEBUSH = "bosebush";
	/** busht algorithm indicator */
    const char * BUSHT = "busht";
	/** bosebushl algorithm indicator */
    const char * BOSEBUSHL = "bosebushl";
	/** addelkemp algorithm indicator */
    const char * ADDELKEMP = "addelkemp";
	/** addelkemp3 algorithm indicator */
    const char * ADDELKEMP3 = "addelkemp3";
	/** addelkempn algorithm indicator */
    const char * ADDELKEMPN = "addelkempn";
} // end namespace

#endif	/* OA_R_H */

