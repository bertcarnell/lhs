/* 
 * File:   CommonDefines.h
 * Author: carnellr
 *
 * Created on November 22, 2013, 4:27 PM
 */

#ifndef COMMONDEFINES_H
#define	COMMONDEFINES_H

#include <cstdlib>
#include <cmath>
#include <exception>
#include <vector>
#include <algorithm>
#include <functional>
#include <cfloat>
#include <climits>
#include <cstdio>
#include "matrix.h"
#include "order.h"
#include "CRandom.h"

#ifdef RCOMPILE
#include "R.h"
#define PRINT_MACRO Rprintf
#define ERROR_MACRO Rprintf
#else // RCOMPILE
#define PRINT_MACRO printf
#define ERROR_MACRO printf
#endif // RCOMPILE

#define PRINT_RESULT 0

namespace lhslib 
{
    void improvedLHS(int n, int k, int dup, bclib::matrix<int> & result, 
            CRandom<double> & oRandom);
    void maximinLHS(int n, int k, int dup, bclib::matrix<int> & result, 
            CRandom<double> & oRandom);
    void optimumLHS(int n, int k, int maxSweeps, double eps, 
            bclib::matrix<int> & outlhs, int optimalityRecordLength, 
            CRandom<double> & oRandom, bool bVerbose);
    void optSeededLHS(int n, int k, int maxSweeps, double eps, 
            bclib::matrix<double> & pOld, int JLen, bool bVerbose);

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
}

#endif	/* COMMONDEFINES_H */
