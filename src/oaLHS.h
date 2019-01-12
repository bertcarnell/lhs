/* 
 * File:   oaLHS.h
 * Author: carnellr
 *
 * Created on March 3, 2014, 10:44 PM
 */

#ifndef OALHS_H
#define	OALHS_H

#include "OACommonDefines.h"
#include "matrix.h"
#include "CRandom.h"
#include "primes.h"
#include "order.h"
#include "oaLHSUtility.h"
#include "COrthogonalArray.h"

namespace oalhslib
{
    /**
     * create an orthogonal array latin hypercube from an orthogonal array
     * @param n
     * @param k
     * @param oa
     * @param intlhs
     * @param lhs
     * @param bVerbose
     * @param oRandom
     */
    void oaLHS(int n, int k, const bclib::matrix<int> & oa, 
            bclib::matrix<int> & intlhs,
            bclib::matrix<double> & lhs, bool bVerbose, 
            bclib::CRandom<double> & oRandom);
    /**
     * create a deterministic orthogonal array latin hypercube from an orthogonal array
     * @param n
     * @param k
     * @param oa
     * @param intlhs
     * @param bVerbose
     */
    void oaLHS(int n, int k, const bclib::matrix<int> & oa, 
        bclib::matrix<int> & intlhs,
        bool bVerbose);

    void printOAandUnique(const bclib::matrix<int> & oa, 
        const std::vector<std::vector<int> > & uniqueLevelsVector);
    
    void replaceOAValues(const bclib::matrix<int> & oa,
        const std::vector<std::vector<int> > & uniqueLevelsVector,
        bclib::matrix<int> & intlhs,
        bclib::CRandom<double> & oRandom,
        bool isRandom);
    
    void generateOALHS(int n, int k, bclib::matrix<double> & oalhs,
        bool bChooseLargerDesign, bool bVerbose);
}


#endif	/* OALHS_H */
