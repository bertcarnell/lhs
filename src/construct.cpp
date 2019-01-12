/**
 * @file construct.cpp
 * @author Robert Carnell
 * @copyright Copyright (c) 2013, Robert Carnell
 * 
 * License:  This file may be freely used and shared according to the original license.
 * 
 * Reference:
 * <ul><li><a href="http://lib.stat.cmu.edu/designs/">Statlib Designs</a></li>
 * <li><a href="http://lib.stat.cmu.edu/designs/oa.c">Owen's Orthogonal Array Algorithms</a></li></ul>
 * 
 * Original Header:
 * <blockquote>
 * These programs construct and manipulate orthogonal arrays.  They were prepared by
 * 
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
 * </blockquote>
 */

#include "construct.h"

namespace oacpp
{
    namespace oaconstruct
    {
        int bosecheck(int q, int ncol)
        {
            std::ostringstream msg;
            if (ncol > q + 1)
            {
                msg << "Bose's design must have ncol <= q+1. Had q=" << q << " and ncol=" << ncol << ".\n";
                throw std::runtime_error(msg.str().c_str());
            }
            if (ncol <= 0)
            {
                msg << "Nonpositive number of columns requested for Bose's design\n";
                throw std::runtime_error(msg.str().c_str());
            }
            return SUCCESS_CHECK;
        }

        int bose(GF & gf, bclib::matrix<int> & A, int ncol)
        {
            size_t icol, irow;
            size_t q = static_cast<size_t>(gf.q);

            // bosecheck throws if it fails
            bosecheck(static_cast<int>(q), ncol);

            irow = 0;
            for (size_t i = 0; i < q; i++)
            {
                for (size_t j = 0; j < q; j++)
                {
                    icol = 0;
                    A(irow, icol++) = static_cast<int>(i);
                    if (ncol > 1)
                    {
                        A(irow, icol++) = static_cast<int>(j);
                    }
                    for (icol = 2; icol < static_cast<size_t>(ncol); icol++)
                    {
                        A(irow, icol) = gf.plus(j, gf.times(i, icol - 1));
                    }
                    irow++;
                }
            }

            return SUCCESS_CHECK;
        }

        int itopoly(int n, int q, int d, std::vector<int> & coef)
        {
            for (size_t i = 0; i <= static_cast<size_t>(d); i++)
            {
                coef[i] = n % q;
                n = n / q;
            }
            return UNCHECKED_RETURN;
        }

        /*  find  value = poly(arg) where poly is a polynomial of degree d  
            and all the arithmetic takes place in the given Galois field.*/
        int polyeval(GF & gf, int d, std::vector<int> & poly, int arg, int* value)
        {
            int ans = 0;
            /* note: cannot decrement with a size type because it is always > 0.  this needs to go < 1 to stop */
            //for (size_t i = static_cast<size_t>(d); i >= 0; --i) /* Horner's rule */
            for (int i = d; i >= 0; i--) /* Horner's rule */
            {
                size_t ui = static_cast<size_t>(i);
                size_t uans = static_cast<size_t>(ans);
                size_t uarg = static_cast<size_t>(arg);
    #ifdef RANGE_DEBUG
                size_t plusRow = static_cast<size_t>(gf.times.at(uans,uarg));
                size_t plusCol = static_cast<size_t>(poly.at(ui));
                ans = gf.plus.at(plusRow, plusCol);
    #else
                //ans = gf.plus(gf.times(ans,arg),poly[i]);
                size_t plusRow = static_cast<size_t>(gf.times(uans,uarg));
                size_t plusCol = static_cast<size_t>(poly[ui]);
                ans = gf.plus(plusRow, plusCol);
    #endif
            }

            *value = ans;
            return UNCHECKED_RETURN;
        }

        int bushcheck(int q, int str, int ncol)
        {
            std::ostringstream msg;
            if (ncol > q + 1)
            {
                msg << "Bush designs require ncol <= q+1. Cannot have q = " << q << " and ncol = " << ncol << ".\n";
                throw std::runtime_error(msg.str().c_str());
            }
            if (str > ncol)
            {
                msg << "It doesn't make sense to have an array of strength " << str << " with only " << ncol << "columns.\n";
                throw std::runtime_error(msg.str().c_str());
            }
            if (str >= q + 1) // LCOV_EXCL_START
            {
                PRINT_OUTPUT("Bush's (1952) theorem has a condition t<q where t\n");
                PRINT_OUTPUT("is the strength of the array and q is the number of symbols.\n");
                PRINT_OUTPUT("Here we have t = %d and q = %d.  The array may still\n", str, q);
                PRINT_OUTPUT("be useful, but a full factorial would have at least as\n");
                PRINT_OUTPUT("many columns.\n");
            } // LCOV_EXCL_STOP

            return SUCCESS_CHECK;
        }

        int bush(GF & gf, bclib::matrix<int> & A, int str, int ncol)
        {
            int q = gf.q;
            std::vector<int> coef(str);
            
            // bushcheck throws if it fails
            bushcheck(q, str, ncol);

            for (size_t i = 0; i < static_cast<size_t>(primes::ipow(q, str)); i++)
            {
                itopoly(static_cast<int>(i), q, str - 1, coef);
                A(i, static_cast<size_t>(0)) = coef[static_cast<size_t>(str) - 1];
                for (size_t j = 0; j < static_cast<size_t>(ncol) - 1; j++)
                {
                    polyeval(gf, str - 1, coef, static_cast<int>(j), &(A(i, 1 + j)));
                }
            }
            return SUCCESS_CHECK;
        }

        int addelkempcheck(int q, int p, int ncol)
        {
            std::ostringstream msg;
            if (p == 2 && q > 4)
            {
                msg << "This Addelman-Kempthorne OA(2q^2,ncol,q,2) is only\n";
                msg << "available for odd prime powers q and for even prime\n";
                msg << "powers q<=4.  q=" << q << " is not available, but a\n";
                msg << "Bose Bush construction exists for that design.\n";
                throw std::runtime_error(msg.str().c_str());
            }

            if (ncol > 2 * q + 1)
            {
                msg << "The Addelman-Kempthorne construction needs ncol <= 2q+1.\n";
                msg << "Can't have ncol = " << ncol << " with q = " << q << ".\n";
                throw std::runtime_error(msg.str().c_str());
            }

            if (ncol == 2 * q + 1) // LCOV_EXCL_START
            {
                PRINT_OUTPUT("\nWarning: The Addelman-Kempthorne construction with ncol = 2q+1\n");
                PRINT_OUTPUT("has a defect.  While it is still an OA(2q^2,2q+1,q,2),\n");
                PRINT_OUTPUT("there exist some pairs of rows that agree in three columns.\n");
                PRINT_OUTPUT("The final column in the array is involved in all of these\n");
                PRINT_OUTPUT("triple coincidences.\n");
            } // LCOV_EXCL_STOP
            
            return SUCCESS_CHECK;
        }

        int addelkemp(GF & gf, bclib::matrix<int> & A, int ncol)
        {
            int kay; /* A&K notation */
            int square, ksquare, temp;
			size_t row, col;

            int p = gf.p;
            size_t q = gf.q;

            std::vector<int> b(q);
            std::vector<int> c(q);
            std::vector<int> k(q);

            // addelkempcheck throws if it fails
            addelkempcheck(static_cast<int>(q), p, ncol);

            for (size_t i = 0; i < q; i++)
            { /* First q*q rows */
                square = gf.times(i,i);
                for (size_t j = 0; j < q; j++)
                {
                    row = i * q + j;
                    col = 0;
                    if (col < static_cast<size_t>(ncol))
                    {
                        A(row, col++) = static_cast<int>(j);
                    }
                    for (size_t m = 1; m < q && col < static_cast<size_t>(ncol); m++)
                    {
                        A(row,col++) = gf.plus(i,gf.times(m,j));
                    }
                    for (size_t m = 0; m < q && col < static_cast<size_t>(ncol); m++)
                    {
                        temp = gf.plus(j,gf.times(m,i));
                        A(row,col++) = gf.plus(temp,square); /* Rgt cols */
                    }
                    if (col < static_cast<size_t>(ncol))
                    {
                        A(row, col++) = static_cast<int>(i);
                    }
                }
            }

            if (p != 2) /* Constants kay,b,c,k for odd p */
            {
                oaaddelkemp::akodd(gf, &kay, b, c, k);
            }
            else /* Constants kay,b,c,k for even p */
            {
                oaaddelkemp::akeven(gf, &kay, b, c, k);
            }

            for (size_t i = 0; i < q; i++)
            { /* Second q*q rows */
                square = gf.times(i,i);
                ksquare = gf.times(kay,square);
                for (size_t j = 0; j < q; j++)
                {
                    row = q * q + i * q + j;
                    col = 0;
                    if (col < static_cast<size_t>(ncol))
                    {
                        A(row, col++) = static_cast<int>(j);
                    }
                    for (size_t m = 1; m < q && col < static_cast<size_t>(ncol); m++, col++)
                    {
                        A(row,col) = gf.plus(A(row - q * q,col),b[m]);
                    }
                    if (col < static_cast<size_t>(ncol))
                    {
                        A(row,col++) = gf.plus(ksquare,j); /* q+1 */
                    }
                    for (size_t m = 1; m < q && col < static_cast<size_t>(ncol); m++)
                    {
                        temp = gf.times(i,k[m]);
                        temp = gf.plus(ksquare,temp);
                        temp = gf.plus(j,temp);
                        A(row,col++) = gf.plus(temp,c[m]);
                    }
                    if (col < static_cast<size_t>(ncol))
                    {
                        A(row, col++) = static_cast<int>(i);
                    }
                }
            }

            return SUCCESS_CHECK;
        }

        int bosebushcheck(int q, int p, int ncol)
        {
            std::ostringstream msg;
            if (p != 2)
            {
                msg << "This version of Bose and Bush needs q=2^n for some n.\n";
                throw std::runtime_error(msg.str().c_str());
            }

            if (ncol > 2 * q + 1)
            {
                msg << "The Bose-Bush construction needs ncol <= 2q+1.\n";
                msg << "Can't have ncol = " << ncol << " with q = " << q << ".\n";
                throw std::runtime_error(msg.str().c_str());
            }

            if (ncol == 2 * q + 1) // LCOV_EXCL_START
            {
                PRINT_OUTPUT("\nWarning: The Bose-Bush construction with ncol = 2q+1\n");
                PRINT_OUTPUT("has a defect.  While it is still an OA(2q^2,2q+1,q,2),\n");
                PRINT_OUTPUT("there exist some pairs of rows that agree in three columns.\n\n\n");
            } // LCOV_EXCL_STOP
            
            return SUCCESS_CHECK;
        }

        int bosebush(GF & gf, bclib::matrix<int> & B, int ncol)
        {
            int p;
            int mul;
			size_t irow;

            p = gf.p; /* GF(q) used to generate design with q/2 levels */
            size_t q = static_cast<size_t>(gf.q);
            size_t s = q / 2; /* number of levels in design */
            bclib::matrix<int> A(s, q);

            // bosebushcheck throws if it fails
            bosebushcheck(static_cast<int>(s), p, ncol);

            irow = 0;
            for (size_t i = 0; i < q; i++)
            {
                for (size_t j = 0; j < q; j++)
                {
                    mul = gf.times(i,j);
                    mul = mul % s;
                    for (size_t k = 0; k < s; k++)
                    {
                        A(k,j) = gf.plus(mul,k);
                    }
                }
                for (size_t k = 0; k < s; k++)
                {
                    for (size_t j = 0; j < static_cast<size_t>(ncol) && j < 2 * s + 1; j++)
                    {
                        B(irow,j) = A(k,j);
                    }
                    if (static_cast<size_t>(ncol) == 2 * s + 1)
                    {
                        B(irow, static_cast<size_t>(ncol) - 1) = static_cast<int>(i % s);
                    }
                    irow++;
                }
            }
            return SUCCESS_CHECK;
        }

        int bosebushlcheck(int s, int p, int lam, int ncol)
        {
            std::ostringstream msg;
            if (!primes::isprime(p))
            {
                msg << "Bose Bush routine given a nonprime.\n";
                throw std::runtime_error(msg.str().c_str());
            }

            if (ncol > lam * s + 1)
            {
                msg << "The Bose-Bush construction needs ncol <= lambda*q+1.\n";
                msg << "Can't have ncol = " << ncol << " with lam = " << lam << "\n";
                msg << "and q = " << s << ".\n";
                throw std::runtime_error(msg.str().c_str());
            }

            if (ncol == lam * s + 1) // LCOV_EXCL_START
            {
                PRINT_OUTPUT("\nWarning: The Bose-Bush construction with ncol = lambda*q+1\n");
                PRINT_OUTPUT("has a defect.  While it is still an OA(lambda*q^2,lambda*q+1,q,2),\n");
                PRINT_OUTPUT("it may have worse coincidence properties than\n");
                PRINT_OUTPUT("OA(lambda*q^2,lambda*q+1,q,2).\n");
            } // LCOV_EXCL_STOP
            
            return SUCCESS_CHECK;
        }

        int bosebushl(GF & gf, int lam, bclib::matrix<int> & B, int ncol)
        /* Implement Bose and Bush's 1952 A.M.S. method with given lambda */
        {
            int p, irow;
            int mul;

            p = gf.p; /* GF(q) used to generate design with q/lam levels */
            size_t q = static_cast<size_t>(gf.q);
            size_t s = q / lam; /* number of levels in design */
            bclib::matrix<int> A(s,q);

            // bosebushlcheck throws if it fails
            bosebushlcheck(static_cast<int>(s), p, lam, ncol);

            irow = 0;
            for (size_t i = 0; i < q; i++)
            {
                for (size_t j = 0; j < q; j++)
                {
                    mul = gf.times(i,j);
                    mul = mul % s;
                    for (size_t k = 0; k < s; k++)
                    {
                        A(k,j) = gf.plus(mul,k);
                    }
                }
                for (size_t k = 0; k < s; k++)
                {
                    for (size_t j = 0; j < static_cast<size_t>(ncol) && j < lam * s + 1; j++)
                    {
                        B(irow,j) = A(k,j);
                    }
                    if (ncol == lam * static_cast<int>(s) + 1)
                    {
                        B(irow, static_cast<size_t>(ncol) - 1) = static_cast<int>(i % s);
                    }
                    irow++;
                }
            }
            return SUCCESS_CHECK;
        }
    } // end namespace
} // end namespace  
