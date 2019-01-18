/**
 * @file geneticLHS.cpp
 * @author Robert Carnell
 * @copyright Copyright (c) 2014, Robert Carnell
 * 
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
 */

#include "LHSCommonDefines.h"
#include "utilityLHS.h"

namespace lhslib 
{
    // TODO: multi-thread the iterations over population
    void geneticLHS(int n, int k, int pop, int gen, double pMut, std::string criterium,
            bool bVerbose, bclib::matrix<double> & result, bclib::CRandom<double> & oRandom)
    {
        if (n < 1 || k < 1)
        {
            throw std::runtime_error("nsamples are less than 1 (n) or nparameters less than 1 (k)");
        }
        msize_type m_n = static_cast<msize_type>(n);
        msize_type m_k = static_cast<msize_type>(k);
        if (result.rowsize() != m_n || result.colsize() != m_k)
        {
            throw std::runtime_error("result should be n x k for the lhslib::geneticLHS call");
        }
        if (gen < 1 || pop < 1)
        {
            throw std::invalid_argument("pop, and gen should be integers greater than 0");
        }
        msize_type m_pop = static_cast<msize_type>(pop);
        msize_type m_gen = static_cast<msize_type>(gen);
        
        if (pMut <= 0 || pMut >= 1)
        {
            throw std::invalid_argument("pMut should be between 0 and 1");
        }
        if (m_pop % 2 != 0)
        {
            throw std::invalid_argument("pop should be an even number");
        }

        std::vector<bclib::matrix<int> > A = std::vector<bclib::matrix<int> >(m_pop);
        for (msize_type i = 0; i < m_pop; i++)
        {
            A[i] = bclib::matrix<int>(m_n, m_k);
        }

        for (msize_type i = 0; i < m_pop; i++)
        {
            // fill A with random hypercubes
            randomLHS(static_cast<int>(m_n), static_cast<int>(m_k), A[i], oRandom);
#ifdef _DEBUG
            if (!lhslib::isValidLHS(A[i])) PRINT_MACRO("A is not valid at %d in randomLHS\n", static_cast<int>(i));
#endif
        }
        std::vector<double> B;
        std::vector<bclib::matrix<int> > J;
        bclib::matrix<double> dist;
        std::vector<double>::iterator it;
        std::vector<double> distnonzero = std::vector<double>();
        for (msize_type v = 0; v < m_gen; v++)
        {
            B = std::vector<double>(m_pop);
            for (msize_type i = 0; i < m_pop; i++)
            {
                if (criterium == "S")
                {
                    B[i] = calculateSOptimal<int>(A[i]);
                }
                else if (criterium == "Maximin")
                {
                    //B[i] <- min(dist(A[, , i]))
                    dist = bclib::matrix<double>(A[i].rowsize(), A[i].rowsize());
                    calculateDistance<int>(A[i], dist);
                    // we want to find the minimum distance element, but there are zeros in the dist matrix
                    distnonzero.clear();
                    for (bclib::matrix<double>::const_iterator mit = dist.begin(); mit != dist.end(); ++mit)
                    {
                        if (*mit > 0.0)
                        {
                            distnonzero.push_back(*mit);
                        }
                    }
                    it = std::min_element(distnonzero.begin(), distnonzero.end());
                    B[i] = *it;
                } 
                else 
                {
                    std::stringstream msg;
                    msg << "Criterium not recognized: S and Maximin are available: " << criterium.c_str() << " was provided.\n";
                    throw std::invalid_argument(msg.str().c_str());
                }
            }
            // H is used as an index on vector of matrices, A, so it should be using zero based order
            std::vector<int> H = std::vector<int>(B.size());
            bclib::findorder_zero(B, H);
            int posit = static_cast<int>(std::max_element(B.begin(), B.end()) - B.begin());

            J = std::vector<bclib::matrix<int> >(m_pop);
            for (std::vector<bclib::matrix<int> >::iterator i = J.begin(); i != J.end(); ++i)
            {
                *i = bclib::matrix<int>(m_n, m_k);
            }
#ifdef _DEBUG
            if (!lhslib::isValidLHS(A[posit])) PRINT_MACRO("A is not valid at %d in randomLHS\n", static_cast<int>(posit));
#endif
            // the first half of the next population gets the best hypercube from the first population
            for (msize_type i = 0; i < (m_pop / 2); i++)
            {
                J[i] = A[posit];
            }
            if (m_pop / 2 == 1)
            {
                break;
            }
            // the second half of the next population gets the decreasingly best hypercubes from the first population
            for (msize_type i = 0; i < (m_pop / 2); i++)
            {
                J[i + m_pop / 2] = A[H[i]];
#ifdef _DEBUG                
                if (!lhslib::isValidLHS(J[i + m_pop / 2]))
                {
					PRINT_MACRO("J is not valid at %d %d %d in 2nd half setup\n", static_cast<int>(i + m_pop / 2), static_cast<int>(i), static_cast<int>(m_pop/2));
					PRINT_MACRO("J is equal to A[H[i]], 1 is true %d", (int)(J[i+m_pop/2] == A[H[i]]));
					PRINT_MACRO("\n%s\n", J[i + m_pop / 2].toString());
                    
					PRINT_MACRO("\n%s\n", A[H[i]].toString());
					PRINT_MACRO("H: ");
                    for (vsize_type iv = 0; iv < H.size(); iv++)
                    {
						PRINT_MACRO("%d,", H[iv]);
                    }
					PRINT_MACRO("\n");
                    return;
                }
#endif
            }
            int temp1, temp2;
            // skip the first best hypercube in the next generation
            // in the others in the first half of the population, randomly permute a column from the second half into the first half
            for (msize_type i = 1; i < (m_pop / 2); i++)
            {
                runifint<int>(0, static_cast<int>(m_k)-1, &temp1, oRandom);
                runifint<int>(0, static_cast<int>(m_k)-1, &temp2, oRandom);
                for (msize_type irow = 0; irow < m_n; irow++)
                {
                    J[i](irow, temp1) = J[i + m_pop / 2](irow, temp2);
                }
#ifdef _DEBUG
                if (!lhslib::isValidLHS(J[i]))
                {
					PRINT_MACRO("J is not valid at %d in 1st half permute\n", static_cast<int>(i));
					PRINT_MACRO("\n%s\n", J[i].toString());
                    return;
                }
#endif
            }
            // for the second half of the population, randomly permute a column from the best hypercube
            for (msize_type i = m_pop / 2; i < m_pop; i++)
            {
                runifint<int>(0, static_cast<int>(m_k)-1, &temp1, oRandom);
                runifint<int>(0, static_cast<int>(m_k)-1, &temp2, oRandom);
                for (msize_type irow = 0; irow < m_n; irow++)
                {
                    J[i](irow, temp1) = A[posit](irow, temp2);
                }
                if (!lhslib::isValidLHS(J[i])) PRINT_MACRO("J is not valid at %d in second half permute\n", static_cast<int>(i));
            }
            // randomly exchange two numbers in pMut percent of columns
            std::vector<double> y = std::vector<double>(m_k);
            for (msize_type i = 1; i < m_pop; i++)
            {
                runif_std(static_cast<unsigned int>(m_k), y, oRandom);
                for (msize_type j = 0; j < m_k; j++)
                {
                    if (y[j] <= pMut)
                    {
                        std::vector<int> z = std::vector<int>(2);
                        runifint<int>(2u, 0, static_cast<int>(m_n-1), z, oRandom);
                        int a = J[i](z[0], j);
                        int b = J[i](z[1], j);
                        J[i](z[0], j) = b;
                        J[i](z[1], j) = a;
                    }
                }
            }
            // put all of J back into A to start the next round
            A = J;
            if (v != m_gen && bVerbose)
            {
				PRINT_MACRO("Generation %d completed\n", static_cast<int>(v)); // LCOV_EXCL_LINE
            }
        }

        if (bVerbose)
        {
			PRINT_MACRO("Last generation completed\n"); // LCOV_EXCL_LINE
        }
#ifdef _DEBUG
        if (!lhslib::isValidLHS(J[0])) PRINT_MACRO("J[0] is not valid\n");
#endif
        std::vector<double> eps = std::vector<double>(m_n*m_k);
        runif_std(static_cast<unsigned int>(m_n * m_k), eps, oRandom);
        unsigned int count = 0;
        for (unsigned int j = 0; j < static_cast<unsigned int>(m_k); j++)
        {
            for (unsigned int i = 0; i < static_cast<unsigned int>(m_n); i++)
            {
                result(i,j) = (static_cast<double>(J[0](i,j)) - 1.0 + eps[count]) / static_cast<double>(m_n);
                count++;
            }
        }
    }
}
