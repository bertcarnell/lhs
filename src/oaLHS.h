/**
 * @file oaLHS.h
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
     * @param n the number of rows or samples
     * @param k the number of columns or parameters
     * @param oa an orthogonal array
     * @param intlhs an integer based Latin hypercube sample
     * @param lhs a Latin hypercube sample
     * @param bVerbose will messages be printed
     * @param oRandom a random generator
     */
    void oaLHS(int n, int k, const bclib::matrix<int> & oa,
            bclib::matrix<int> & intlhs,
            bclib::matrix<double> & lhs, bool bVerbose,
            bclib::CRandom<double> & oRandom);

    /**
     * create a deterministic orthogonal array latin hypercube from an orthogonal array
     * @param n the number of rows or samples
     * @param k the number of columns or parameters
     * @param oa an orthogonal array
     * @param intlhs an integer based Latin hypercube sample
     * @param bVerbose will messages be printed
     */
    void oaLHS(int n, int k, const bclib::matrix<int> & oa,
        bclib::matrix<int> & intlhs,
        bool bVerbose);

    /**
     * print an orthogonal array and the unique levels
     * @param oa an orthogonal array
     * @param uniqueLevelsVector
     */
    void printOAandUnique(const bclib::matrix<int> & oa,
        const std::vector<std::vector<int> > & uniqueLevelsVector);

    /**
     * replace orthogonal array values
     * @param oa an orthogonal array
     * @param uniqueLevelsVector
     * @param intlhs an integer based Latin hypercube sample
     * @param oRandom a random number generator
     * @param isRandom is the result randomized
     */
    void replaceOAValues(const bclib::matrix<int> & oa,
        const std::vector<std::vector<int> > & uniqueLevelsVector,
        bclib::matrix<int> & intlhs,
        bclib::CRandom<double> & oRandom,
        bool isRandom);

    /**
     * generate an orthogonal array Latin hypercube
     * @param n the number of rows or samples
     * @param k the number of columns or parameters
     * @param oalhs the generated Latin hypercube sample
     * @param bChooseLargerDesign choose a larger design if the orthogonal array is not sufficient
     * @param bVerbose should messages be printed
     * @param oRandom a random generator
     */
    void generateOALHS(int n, int k, bclib::matrix<double> & oalhs,
        bool bChooseLargerDesign, bool bVerbose,
		bclib::CRandom<double> & oRandom);
}


#endif	/* OALHS_H */
