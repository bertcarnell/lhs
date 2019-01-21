/**
 * @file OACommonDefines.h
 * @author Robert Carnell
 * @copyright Copyright (c) 2013, Robert Carnell
 * @license <a href="http://www.gnu.org/licenses/lgpl.html">GNU Lesser General Public License (LGPL v3)</a>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Reference:
 * <ul><li><a href="http://lib.stat.cmu.edu/designs/">Statlib Designs</a></li>
 * <li><a href="http://lib.stat.cmu.edu/designs/oa.c">Owen's Orthogonal Array Algorithms</a></li></ul>
 */

#ifndef OACOMMONDEFINES_H
#define	OACOMMONDEFINES_H

#include <exception>
#include <string>
#include <vector>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <stdexcept>
#include <sstream>
#include <numeric>

#ifdef RCOMPILE
#include <Rcpp.h>
/**
 * A print macro to enable operation with or without R
 */
#define PRINT_OUTPUT Rprintf
#else
/**
 * A print macro to enable operation with or without R
 */
#define PRINT_OUTPUT std::printf
#endif

/**
 * if NDEBUG is not defined, then debug mode is likely enabled
 */
#ifndef NDEBUG
#ifndef RANGE_DEBUG
#define RANGE_DEBUG
#endif
#endif

/**
 * When a method returns an int to indicate success
 */
#define SUCCESS_CHECK 1
/**
 * When a method returns an int to indicate failure
 */
#define FAILURE_CHECK 0
/**
 * When a method returns an int which is not normally checked
 */
#define UNCHECKED_RETURN 0

/**
 * @page oa_main_page Orthogonal Array Library
 * 
 * From the original documentation by Owen:
 * 
 *<blockquote>
 * From: owen@stat.stanford.edu
 * 
 * These programs construct and manipulate orthogonal 
 * arrays.  They were prepared by
 * - Art Owen
 * - Department of Statistics
 * - Sequoia Hall
 * - Stanford CA 94305
 * 
 * They may be freely used and shared.  This code comes
 * with no warranty of any kind.  Use it at your own
 * risk.
 * 
 * I thank the Semiconductor Research Corporation and
 * the National Science Foundation for supporting this
 * work.
 * 
 * I thank Randall Tobias of SAS Inc. for many helpful
 * electronic discussions that lead to improvements in
 * these programs.
 * </blockquote>
 * 
 * @tableofcontents
 * 
 * @section orthogonal_arrays_sec Orthogonal Arrays
 * <blockquote>
 * An orthogonal array <code>A</code> is a matrix of <code>n</code> rows, <code>k</code> 
 * columns with every element being one of <code>q</code> symbols
 * <code>0,...,q-1</code>.  The array has strength <code>t</code> if, in every <code>n</code> by <code>t</code>
 * submatrix, the <code>q^t</code> possible distinct rows, all appear
 * the same number of times.  This number is the index
 * of the array, commonly denoted <code>lambda</code>.  Clearly, 
 * <code>lambda*q^t = n</code>. Geometrically, if one were to "plot" the 
 * submatrix with one plotting axis for each of the <code>t</code> columns
 * and one point in <code>t</code> dimensional space for each row, the
 * result would be a grid of <code>q^t</code> distinct points.  There would
 * be <code>lambda</code> "overstrikes" at each point of the grid.
 * 
 * The notation for such an array is <code>OA( n, k, q, t )</code>.
 * 
 * If <code>n <= q^(t+1)</code>, then the <code>n</code> rows "should" plot as
 * <code>n</code> distinct points in every <code>n</code> by <code>t+1</code> dimensional subarray.
 * When this fails to hold, the array has the "coincidence
 * defect".
 * 
 * Owen (1992,199?) describes some uses for randomized
 * orthogonal arrays, in numerical integration, computer
 * experiments and visualization of functions.  Those
 * references contain further references to the literature,
 * that provide further explanations.  A strength 1 randomized 
 * orthogonal array is a Latin hypercube
 * sample, essentially so or exactly so, depending on
 * the definition used for Latin hypercube sampling.
 * The arrays constructed here have strength 2 or more, it
 * being much easier to construct arrays of strength 1.
 * 
 * The randomization is achieved by independent
 * uniform permutation of the symbols in each column.
 * 
 * To investigate a function <code>f</code> of <code>d</code> variables, one
 * has to have an array with <code>k >= d</code>.  One may also
 * have a maximum value of <code>n</code> in mind and a minimum value
 * for the number <code>q</code> of distinct levels to investigate.
 * 
 * It is entirely possible that no array of strength <code>t > 1</code>
 * is compatible with these conditions.  The programs
 * below provide some choices to pick from, hopefully
 * without too much of a compromise.
 * 
 * The constructions used are based on published
 * algorithms that exploit properties of Galois fields.
 * Because of this the number of levels <code>q</code> must be
 * a prime power.  That is <code>q = p^r</code> where <code>p</code> is prime
 * and <code>r >= 1</code> is an integer.
 * 
 * The Galois field arithmetic for the prime powers is
 * based on tables published by Knuth and Alanen (1964)
 * below.  The resulting fields have been tested by the
 * methods described in Appendix 2 of that paper and
 * they passed.  This is more a test of the accuracy of
 * my transcription than of the original tables.
 * </blockquote>
 * 
 * @section avail_prime_sec Available Prime Powers
 * 
 * <blockquote>
 * The designs given here require a prime power for
 * the number of levels.  They presently work for the 
 * following prime powers:
 * 
 * All Primes
 * All prime powers <code>q = p^r</code> where <code>p < 50</code> and <code>q < 10^9</code>
 * 
 * Here are some of the smaller prime powers:
 * 
 * - Powers of 2:  4 8 16 32 64 128 256 512
 * - Powers of 3:  9 27 81 243 729
 * - Powers of 5:  25 125 625
 * - Powers of 7:  49 343 
 * - Square of 11: 121
 * - Square of 13: 169
 * 
 * Here are some useful primes:
 * 
 * - 2,3,5,7,11,13,17,19,23,29,31,37,101,251,401
 * 
 * The first row are small primes, the second row are
 * primes that are 1 more than a "round number".  The small
 * primes lead to small arrays.  An array with 101 levels
 * is useful for exploring a function at levels 0.00 0.01
 * through 1.00.  Keep in mind that a strength 2 array on
 * 101 levels requires <code>101^2 = 10201</code> experimental runs,
 * so it is only useful where large experiments are possible.
 * 
 * Note that some of these will require more
 * memory than your computer has.  For example,
 * with a large prime like 10663, the program knows
 * the Galois field, but can't allocate enough
 * memory:
 * 
 * <code>bose 10663</code>
 * - Unable to allocate 1927'th row in an integer matrix.
 * - Unable to allocate space for Galois field on 10663 elements.
 * - Construction failed for <code>GF(10663)</code>.
 * - Could not construct Galois field needed for Bose design.
 * 
 * The smallest prime power not covered is <code>53^2 = 2809</code>.
 * The smallest strength 2 array with 2809 symbols has
 * <code>2809^2 = 7890481</code> rows.  Therefore the missing prime powers
 * are only needed in certain enormous arrays, not in the
 * small ones of most practical use.  In any event there
 * are some large primes and prime powers in the program
 * if an enormous array is needed.
 * 
 * To add <code>GF(p^r)</code> for some new prime power p^r,
 * consult Alanen and Knuth for instructions on how
 * to search for an appropriate indexing polynomial,
 * and for how to translate that polynomial into a
 * replacement rule for <code>x^r</code>.  
 * </blockquote>
 * 
 * @section methods Methods
 * 
 * <ul>
 * <li>@ref oacpp::COrthogonalArray::bose</li>
 * <li>@ref oacpp::COrthogonalArray::bush</li>
 * <li>@ref oacpp::COrthogonalArray::busht</li>
 * <li>@ref oacpp::COrthogonalArray::bosebush</li>
 * <li>@ref oacpp::COrthogonalArray::bosebushl</li>
 * <li>@ref oacpp::COrthogonalArray::addelkemp</li>
 * <li>@ref oacpp::COrthogonalArray::addelkemp3</li>
 * <li>@ref oacpp::COrthogonalArray::oarand</li>
 * <li>@ref oacpp::COrthogonalArray::oastr</li>
 * <li>@ref oacpp::COrthogonalArray::oastr1</li>
 * <li>@ref oacpp::COrthogonalArray::oastr2</li>
 * <li>@ref oacpp::COrthogonalArray::oastr3</li>
 * <li>@ref oacpp::COrthogonalArray::oastr4</li>
 * <li>@ref oacpp::COrthogonalArray::oatriple</li>
 * <li>@ref oacpp::COrthogonalArray::oaagree</li>
 * <li>@ref oacpp::COrthogonalArray::oadimen</li>
 * </ul>
 * 
 * @section tips Tips On Use
 * 
 * <blockquote>
 * It is faster to generate only the columns you need.
 * For example
 * <code>bose 101 4</code>
 * only generates the first 4 columns of the array, whereas
 * <code>bose 101</code>
 * generates 102 columns.  If you only want 4 columns the
 * former saves a lot of time.
 * 
 * Passing the <code>q n k</code> on the command line is more difficult
 * than letting the computer figure them out, but it
 * allows more error checking.
 * 
 * In practical use, I would try first to use a Bose
 * design.  Then I would consider either an Addelman-
 * Kempthorne or Bose-Bush design to see whether it
 * could accommodate the desired number of columns with
 * fewer runs.  Obviously this advice depends on the
 * sort of problems I expect to handle.  When a very
 * large number of runs is possible a Bush design may
 * work well, since it can have high strength.
 * </blockquote>
 * 
 * @section references References
 * 
 * <blockquote>
 * Here are the references for the constructions used:
 * <ul>
 * <li>S. Addelman and O. Kempthorne (1961) Annals of Mathematical Statistics, Vol 32 pp 1167-1176.</li>
 * <li>J.D. Alanen and D.E. Knuth (1964) Sankhya Ser. A Vol. 26, pp 305-328</li>
 * <li>R.C. Bose (1938) Sankhya Vol 3 pp 323-338</li>
 * <li>K.A. Bush (1952) Annals of Mathematical Statistics, Vol 23 pp 426-434</li>
 * <li>R.C. Bose and K.A. Bush (1952) Annals of Mathematical Statistics, Vol 23 pp 508-524.</li>
 * </ul>
 * This book provides a large list of orthogonal array constructions:
 * <ul><li>Aloke Dey (1985) "Orthogonal Fractional Factorial Designs" Halstead Press</li></ul>
 * 
 * These papers discuss randomized orthogonal arrays, the second
 * is being revised in parallel with development of the software
 * described here:
 * <ul>
 * <li>A.B. Owen (1992)  Statistica Sinica, v2 n2 pp 439-452</li>
 * <li>A.B. Owen (199?)  Annals of Statistics, to appear "Lattice Sampling Revisited: Monte Carlo Variance of Means Over Randomized Orthogonal Arrays"</li>
 * <li>H.D. Patterson (1954) J.R.S.S. B 16, 140-149</li>
 * </ul>
 * These papers discuss Latin hypercube sampling:
 * <ul>
 * <li>M.D. McKay, W.J. Conover and R.J. Beckman (1979) Technometrics 21, 239-245</li>
 * <li>A.B. Owen (1992) J.R.S.S. B 541-551</li>
 * <li>H.D. Patterson (1954) J.R.S.S. B 16, 140-149</li>
 * <li>M. Stein (1987) Technometrics 29, 143-151</li>
 * </ul>
 * </blockquote>
 * 
 * @section implement Implementation Details
 * 
 * <blockquote>
 * Galois fields are implemented through arrays that
 * store their addition and multiplication tables.  Some
 * space could have been saved by using powers of primitive
 * marks in place of the multiplication table.  But since
 * the multiplication tables itself is only as large as
 * the smallest possible column in a strength 2 array it
 * was not considered to be a burden.   Subtraction and
 * division are implemented through vectors of additive
 * and multiplicative inverses, derived from the tables.
 * The tables for <code>GF(p^r)</code> are constructed using a 
 * representation of the field elements as polynomials in <code>x</code>
 * with coefficients as integers modulo <code>p</code> and a special
 * rule (derived from minimal polynomials) for handling
 * products involving <code>x^r</code>.  These rules are taken from
 * published references.  The rules have not all
 * been checked for accuracy, because some of the fields are 
 * very large (e.g. 16807 elements).
 * 
 * The functions that manipulate orthogonal arrays
 * keep the arrays in integer matrices.  This might be
 * a problem for applications that require enormous
 * arrays.  The reason for keeping them in memory is
 * that it makes it easier for others to lift out the
 * functions and embed them in applications or to put
 * on a GUI front end.  It was also thought that any
 * array that is too large to store in a computer, is
 * likely to be too large to use in integration/experimentation
 * on that same computer.  The arrays are generated
 * row by row, so it is not too hard to change the program
 * to place the elements on an output stream as they
 * are computed and do away with the storage.
 * 
 * The functions that test the strength of the
 * arrays may be very far from optimally fast.
 * </blockquote>
 * 
 * @section compile_oa Compiling oalib
 * When compiling <code>oalib</code> these preprocessor directives are used:
 * - NDEBUG defined for a release build
 * - RCOMPILE defined for building with R
 */

#endif	/* OACOMMONDEFINES_H */
