/**
 * @file LHSCommonDefines.h
 * @author Robert Carnell
 * @copyright Copyright (c) 2014, Robert Carnell
 *
 * License <a href="http://www.gnu.org/licenses/lgpl.html">GNU Lesser General Public License (LGPL v3)</a>
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
 */

#ifndef LHSCOMMONDEFINES_H
#define	LHSCOMMONDEFINES_H

#include <cstdlib>
#include <cmath>
#include <exception>
#include <vector>
#include <algorithm>
#include <functional>
#include <numeric>
#include <cfloat>
#include <climits>
#include <cstdio>
#include <iostream>
#include "matrix.h"
#include "order.h"
#include "CRandom.h"

#ifdef RCOMPILE
#include <Rcpp.h>
#define PRINT_MACRO Rcpp::Rcout
#define ERROR_MACRO Rcpp::Rcerr
#else // RCOMPILE
/** Macro to choose the function for printing */
#define PRINT_MACRO std::cout
/** Macro to choose the function for error printing */
#define ERROR_MACRO std::cerr
#endif // RCOMPILE

/** Should results be printed */
#define PRINT_RESULT 0

/** RNG Macro (See lhs_r.cpp)*/
#define START_RNG Rcpp::RNGScope * tempRNG = new Rcpp::RNGScope(); // instantiate a pointer so that the destructor is not implicitly called
/** End RNG Macro (See lhs_r.cpp)*/
#define END_RNG delete tempRNG; // explicitly release the RNG state to avoid memory corruption

/**
 * @namespace lhslib LHS c++ Library namespace
 */
namespace lhslib
{
    /**
     * Improved Latin hypercube sample algorithm
     * @param n number of rows / samples in the lha
     * @param k number parameters / columns in the lhs
     * @param dup A factor that determines the number of candidate points used in the search.
     * @param result the result matrix
     * @param oRandom the random number stream
     */
    void improvedLHS(int n, int k, int dup, bclib::matrix<int> & result,
            bclib::CRandom<double> & oRandom);
    /**
     * Latin hypercube sample algorithm with maximin criterion
     * @param n number of rows / samples in the lha
     * @param k number parameters / columns in the lhs
     * @param dup A factor that determines the number of candidate points used in the search.
     * @param result the result matrix
     * @param oRandom the random number stream
     */
    void maximinLHS(int n, int k, int dup, bclib::matrix<int> & result,
            bclib::CRandom<double> & oRandom);
    /**
     * Optimum Latin hypercube sample algorithm
     * @param n number of rows / samples in the lha
     * @param k number parameters / columns in the lhs
     * @param maxSweeps the maximum number of sweeps to use in the algorithm
     * @param eps The optimal stopping criterion
     * @param outlhs the resultant lhs
     * @param optimalityRecordLength the length of a vector used in the calculations
     * @param oRandom the random number stream
     * @param bVerbose should messages be printed?
     */
    void optimumLHS(int n, int k, int maxSweeps, double eps,
            bclib::matrix<int> & outlhs, int optimalityRecordLength,
            bclib::CRandom<double> & oRandom, bool bVerbose);
    /**
     * Application of the optimum lhs method to a seeded Latin hypercube
     * @param n number of rows / samples in the lhs
     * @param k number parameters / columns in the lhs
     * @param maxSweeps the maximum number of sweeps to use in the algorithm
     * @param eps The optimal stopping criterion
     * @param oldHypercube the seeded lhs
     * @param optimalityRecordLength the length of a vector used in the calculations
     * @param bVerbose should messages be printed?
     */
    void optSeededLHS(int n, int k, int maxSweeps, double eps,
            bclib::matrix<double> & oldHypercube, int optimalityRecordLength, bool bVerbose);

    /**
     * type of size type for use with bclib::matrix<T>
     * @note the type of the matrix (i.e. int) is irrelevant for size_type
     */
    typedef bclib::matrix<int>::size_type msize_type;
    /**
     * type of size type for use with std::vector<T>
     * @note the type of the vector (i.e. int) is irrelevant for size_type
     */
    typedef std::vector<int>::size_type vsize_type;

    /**
     * Create a random latin hypercube sample
     * @param n number of rows / samples in the lhs
     * @param k number parameters / columns in the lhs
     * @param bPreserveDraw should the order of the draw be preserved if less columns are selected
     * @param result the lhs
     * @param oRandom the random number stream
     */
    void randomLHS(int n, int k, bool bPreserveDraw, bclib::matrix<double> & result, bclib::CRandom<double> & oRandom);

    /**
     * Create a random latin hypercube sample with integer values
     * @param n number of rows / samples in the lhs
     * @param k number parameters / columns in the lhs
     * @param result the lhs
     * @param oRandom the random number stream
     */
    void randomLHS(int n, int k, bclib::matrix<int> & result, bclib::CRandom<double> & oRandom);

    /**
     * Create a latin hypercube sample optimized by some criteria with a genetic algorithm
     * @param n number of rows / samples in the lhs
     * @param k number parameters / columns in the lhs
     * @param pop the population of the genetic algorithm in each iteration
     * @param gen the number of generations to use
     * @param pMut the mutation rate
     * @param criterium the optimization criterium
     * @param bVerbose should messages be printed?
     * @param result the lhs
     * @param oRandom the random number stream
     */
    void geneticLHS(int n, int k, int pop, int gen, double pMut, const std::string & criterium,
            bool bVerbose, bclib::matrix<double> & result, bclib::CRandom<double> & oRandom);
}

#endif	/* LHSCOMMONDEFINES_H */
