/**
 * @file COrthogonalArray.cpp
 * @author Robert Carnell
 * @copyright Copyright (c) 2013, Robert Carnell
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
 * 
 * Reference:
 * <ul><li><a href="http://lib.stat.cmu.edu/designs/">Statlib Designs</a></li>
 * <li><a href="http://lib.stat.cmu.edu/designs/oa.c">Owen's Orthogonal Array Algorithms</a></li></ul>
 */

#include "COrthogonalArray.h"

namespace oacpp {

COrthogonalArray::COrthogonalArray()
{
	m_nrow = 0;
	m_ncol = 0;
	m_q = 0;
}

void COrthogonalArray::createGaloisField(int q)
{
	bool test = galoisfield::GF_getfield(q, m_gf) == SUCCESS_CHECK ? true : false;
	if (!test)
	{
		throw std::runtime_error("Could not construct the Galois field"); // LCOV_EXCL_TEST
	}
}

void COrthogonalArray::checkDesignMemory()
{
	if (m_A.isEmpty())
	{
		throw std::runtime_error("Could not allocate array for the design memory."); // LCOV_EXCL_TEST
	}
}

int COrthogonalArray::checkMaxColumns(int k, int maxColumns)
{
	if (k < 2)
	{
		return maxColumns;
	}
	else if (k > maxColumns)
	{
        std::ostringstream s;
        s << "At most " << maxColumns << "columns are possible for the design.";
		const std::string ss = s.str();
		throw std::runtime_error(ss.c_str());
	}
	else
	{
		return k;
	}
}

void COrthogonalArray::checkResult(int result, int nvalue, int * n)
{
	if (result)
	{
		*n = nvalue;
	}
	else
	{
	  throw std::runtime_error("Unable to construct design"); // LCOV_EXCL_TEST
	}
}

void COrthogonalArray::addelkemp(int q, int k, int* n)
{
	k = checkMaxColumns(k, 2*q+1);
	createGaloisField(q);
	int matrows = 2 * q * q;
    m_A = bclib::matrix<int>(matrows, k);
	checkDesignMemory();
	int result = oaconstruct::addelkemp(m_gf, m_A, k);
	checkResult(result, 2*q*q, n);
    m_q = q; m_ncol=k; m_nrow=*n;
}

void COrthogonalArray::addelkemp3(int q, int k, int* n)
{
	k = checkMaxColumns(k, 2*q*q + 2*q + 1); /*  2(q^3-1)/(q-1) - 1  */
	createGaloisField(q);
	int matrows = 2 * q * q * q;
    m_A = bclib::matrix<int>(static_cast<size_t>(matrows), k);
	checkDesignMemory();
	int result = oaaddelkemp::addelkemp3(m_gf, m_A, k);
	checkResult(result, 2*q*q*q, n);
    m_q = q; m_ncol=k; m_nrow=*n;
}

void COrthogonalArray::addelkempn(int akn, int q, int k, int* n) // LCOV_EXCL_START
{
	k = checkMaxColumns(k, 2*(primes::ipow(q,akn)-1)/(q-1) - 1); /*  2(q^3-1)/(q-1) - 1  */
	createGaloisField(q);
	int matrows = 2 * primes::ipow(q, akn);
    m_A = bclib::matrix<int>(matrows, k);
	checkDesignMemory();
	int result = oaaddelkemp::addelkempn(m_gf, akn, m_A, k);
	checkResult(result, 2*primes::ipow(q,akn), n);
    m_q = q; m_ncol=k; m_nrow=*n;
} // LCOV_EXCL_STOP

void COrthogonalArray::bose(int q, int k, int* n)
{
	k = checkMaxColumns(k, q+1);
	createGaloisField(q);
	int matrows = q * q;
    m_A = bclib::matrix<int>(matrows, k);
	checkDesignMemory();
	int result = oaconstruct::bose(m_gf, m_A, k);
	checkResult(result, q*q, n);
    m_q = q; m_ncol=k; m_nrow=*n;
}

void COrthogonalArray::bosebush(int q, int k, int *n)
{
	if (q%2)
	{
		throw std::runtime_error("This implementation of Bose-Bush only works for a number of levels equal to a power of 2");
	}
	k = checkMaxColumns(k, 2*q);
	createGaloisField(2*q);
	int matrows = 2 * q * q;
    m_A = bclib::matrix<int>(matrows, k);
	checkDesignMemory();
	int result = oaconstruct::bosebush(m_gf, m_A, k);
	checkResult(result, 2*q*q, n);
    m_q = q; m_ncol=k; m_nrow=*n;
}

void COrthogonalArray::bosebushl(int lambda, int q, int k, int* n)
{
	int pq, nq, isppq,  pl, nl, isppl;

	k = checkMaxColumns(k, q*lambda);

	primes::primepow(lambda, &pl, &nl, &isppl);
	primes::primepow(q , &pq, &nq, &isppq);

	if (!isppq)
	{
		throw std::runtime_error("The Bose-Bush design requires that q be prime raised to a positive integral power.");
	}
	if (!isppl)
	{
		throw std::runtime_error("The Bose-Bush design requires that lambda be a prime raised to a positive integral power.");
	}
	if (pl != pq)
	{
		throw std::runtime_error("The Bose-Bush design requires that lambda and q be powers of the same prime.");
	}

	createGaloisField(lambda*q);
	int matrows = lambda * q * q;
    m_A = bclib::matrix<int>(matrows, k);
	checkDesignMemory();
	int result = oaconstruct::bosebushl(m_gf, lambda, m_A, k);
	checkResult(result, lambda*q*q, n);
    m_q = q; m_ncol=k; m_nrow=*n;
}

void COrthogonalArray::bush(int q, int k, int* n)
{
	k = checkMaxColumns(k, q+1);
	createGaloisField(q);
	int matrows = q * q * q;
    m_A = bclib::matrix<int>(matrows, k);
	checkDesignMemory();
	int result = oaconstruct::bush(m_gf, m_A, 3, k);
	checkResult(result, q*q*q, n);
    m_q = q; m_ncol=k; m_nrow=*n;
}

void COrthogonalArray::busht(int str, int q, int k, int* n)
{
	k = checkMaxColumns(k, q+1);
	if (str < 2)
	{
		throw std::runtime_error("Bush designs not provided for strength < 2");
	}

	createGaloisField(q);
    m_A = bclib::matrix<int>(primes::ipow(q,str), k);
	checkDesignMemory();
	int result = oaconstruct::bush(m_gf, m_A, str, k);
	checkResult(result, primes::ipow(q,str), n);
    m_q = q; m_ncol=k; m_nrow=*n;
}

int COrthogonalArray::oaagree(bool verbose)
{
	int agree, maxagr;
	int mrow1, mrow2;
	maxagr = mrow1 = mrow2 = 0;

	for (int i = 0; i < m_nrow; i++)
	{
	  for (int j = i+1; j < m_nrow; j++)
	  {
		agree = 0;
		for (int k = 0; k < m_ncol; k++)
		{
		  agree += (m_A(i,k) == m_A(j,k));
		}
		if (agree > maxagr)
		{
		  maxagr = agree;
		  mrow1 = i;
		  mrow2 = j;
		  if (verbose)
		  {
			PRINT_OUTPUT << "New max " << i << " " << j << " " << agree << "\n"; // LCOV_EXCL_LINE
		  }
		}
	  }
	  if (i && i % ROWCHECK == 0 && verbose)
      {
		PRINT_OUTPUT << "Checked rows <= " << i << " vs all other rows.\n"; // LCOV_EXCL_LINE
      }
	}
	if (verbose) // LCOV_EXCL_START
	{
		if (maxagr == 0)
		{
		  PRINT_OUTPUT << "No two distinct rows agree in any columns.\n";
		}
		else
		{
		  PRINT_OUTPUT << "Maximum number of columns matching for two distinct rows is " << maxagr << ".\n";
		  PRINT_OUTPUT << "This is attained by rows " << mrow1 << " and " << mrow2 << ".\n";
		}
	} // LCOV_EXCL_STOP
	return maxagr;
}

int COrthogonalArray::oatriple(bool verbose)
{
	/* Count triple agreements among rows of an array */
	int a3/*, q*/;
	int num3 = 0;

	for (int j1 = 0; j1 < m_ncol; j1++)
	{
		for (int j2 = j1+1; j2 < m_ncol; j2++)
		{
			for (int j3 = j2+1; j3 < m_ncol; j3++)
			{
				a3 = 0;
				for (int i1 = 0; i1 < m_nrow; i1++)
				{
					for (int i2 = i1+1; i2 < m_nrow; i2++)
					{
						a3 += ( m_A(i1,j1)==m_A(i2,j1) )&&( m_A(i1,j2)==m_A(i2,j2) )&&( m_A(i1,j3)==m_A(i2,j3) );
					}
					if (a3)
					{
                        if (verbose)
                        {
                            PRINT_OUTPUT << "Cols " << j1 << " " << j2 << " " << j3 << " match in " << a3 << " distinct pairs of rows.\n"; // LCOV_EXCL_LINE
                        }
						num3++;
					}
				}
			}
		}
	}
	if (verbose) // LCOV_EXCL_START
	{
		PRINT_OUTPUT << "There are " << num3 << " distinct triples of columns that agree\n";
		PRINT_OUTPUT << "in at least two distinct rows.\n";
	} // LCOV_EXCL_STOP
	return num3;
}

void COrthogonalArray::oarand(int is, int js, int ks, int ls)
{
    m_randomClass.seed(is, js, ks, ls);
    std::vector<int> pi = std::vector<int>(m_q);
	for (int j = 0; j < m_ncol; j++)
	{
        rutils::unifperm(pi, m_q, m_randomClass);
		for (int i = 0; i < m_nrow; i++)
		{
			m_A(i,j) = pi[ m_A(i,j) ];
		}
	}
}

int COrthogonalArray::oastr(bool verbose)
{
	int str;
	int bverb = (verbose) ? ALLMESSAGES : NOMESSAGES;
	oastrength::OA_strength(m_q, m_A, &str, bverb);

	if (verbose) // LCOV_EXCL_START
	{
		if (str < 0)
		{
		  PRINT_OUTPUT << "\nThe array does not even have strength 0, meaning that\n";
		  PRINT_OUTPUT << "it is not composed of symbols 0 through " << m_q << ".\n";
		}
		else
		{
		  PRINT_OUTPUT << "\nThe array has strength " << str << " and no higher strength.\n";
		}
	} // LCOV_EXCL_STOP
	return str;
}

bool COrthogonalArray::oastr1(bool verbose)
{
	int bverb = (verbose) ? ALLMESSAGES : NOMESSAGES;
    return (oastrength::OA_str1(m_q, m_A, bverb) == SUCCESS_CHECK);
}

bool COrthogonalArray::oastr2(bool verbose)
{
	int bverb = (verbose) ? ALLMESSAGES : NOMESSAGES;
    return (oastrength::OA_str2(m_q, m_A, bverb) == SUCCESS_CHECK);
}

bool COrthogonalArray::oastr3(bool verbose)
{
	int bverb = (verbose) ? ALLMESSAGES : NOMESSAGES;
    return (oastrength::OA_str3(m_q, m_A, bverb) == SUCCESS_CHECK);
}

bool COrthogonalArray::oastr4(bool verbose)
{
	int bverb = (verbose) ? ALLMESSAGES : NOMESSAGES;
    return (oastrength::OA_str4(m_q, m_A, bverb) == SUCCESS_CHECK);
}

bool COrthogonalArray::oastrt(int t, bool verbose)
{
	int bverb = (verbose) ? ALLMESSAGES : NOMESSAGES;
	return (oastrength::OA_strt(m_q, m_A, t, bverb) == SUCCESS_CHECK);
}

} // end namespace
