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
                ostringstream_runtime_error(msg);
			}
            if (ncol <= 0)
            {
                msg << "Nonpositive number of columns requested for Bose's design\n";
                ostringstream_runtime_error(msg);
            }
            return SUCCESS_CHECK;
        }

        int bose(GaloisField & gf, bclib::matrix<int> & A, int ncol)
        {
            size_t icol, irow;

            // bosecheck throws if it fails
            bosecheck(gf.q, ncol);

            irow = 0;
            for (size_t i = 0; i < gf.u_q; i++)
            {
                for (size_t j = 0; j < gf.u_q; j++)
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
        int polyeval(GaloisField & gf, int d, std::vector<int> & poly, int arg, int* value)
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
                ostringstream_runtime_error(msg);
            }
            if (str > ncol)
            {
                msg << "It doesn't make sense to have an array of strength " << str << " with only " << ncol << "columns.\n";
                ostringstream_runtime_error(msg);
			}

            return SUCCESS_CHECK;
        }

        int bush(GaloisField & gf, bclib::matrix<int> & A, int str, int ncol)
        {
            std::vector<int> coef(str);
            
            // bushcheck throws if it fails
            bushcheck(gf.q, str, ncol);

            size_t qToStr = static_cast<size_t>(primes::ipow(gf.q, str));

            for (size_t i = 0; i < qToStr; i++)
            {
                itopoly(static_cast<int>(i), gf.q, str - 1, coef);
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
                ostringstream_runtime_error(msg);
            }

            if (ncol > 2 * q + 1)
            {
                msg << "The Addelman-Kempthorne construction needs ncol <= 2q+1.\n";
                msg << "Can't have ncol = " << ncol << " with q = " << q << ".\n";
                ostringstream_runtime_error(msg);
            }

            return SUCCESS_CHECK;
        }

        int addelkemp(GaloisField & gf, bclib::matrix<int> & A, int ncol)
        {
            int kay; /* A&K notation */
            int square, ksquare, temp;
			size_t row, col;
            size_t u_ncol = static_cast<size_t>(ncol);

            std::vector<int> b(gf.u_q);
            std::vector<int> c(gf.u_q);
            std::vector<int> k(gf.u_q);

            // addelkempcheck throws if it fails
            addelkempcheck(gf.q, gf.p, ncol);

            for (size_t i = 0; i < gf.u_q; i++)
            { /* First q*q rows */
                square = gf.times(i,i);
                for (size_t j = 0; j < gf.u_q; j++)
                {
                    row = i * gf.u_q + j;
                    col = 0;
                    if (col < u_ncol)
                    {
                        A(row, col++) = static_cast<int>(j);
                    }
                    for (size_t m = 1; m < gf.u_q && col < u_ncol; m++)
                    {
                        A(row,col++) = gf.plus(i,gf.times(m,j));
                    }
                    for (size_t m = 0; m < gf.u_q && col < u_ncol; m++)
                    {
                        temp = gf.plus(j,gf.times(m,i));
                        A(row,col++) = gf.plus(temp,square); /* Rgt cols */
                    }
                    if (col < u_ncol)
                    {
                        A(row, col++) = static_cast<int>(i);
                    }
                }
            }

            if (gf.p != 2) /* Constants kay,b,c,k for odd p */
            {
                oaaddelkemp::akodd(gf, &kay, b, c, k);
            }
            else /* Constants kay,b,c,k for even p */
            {
                oaaddelkemp::akeven(gf, &kay, b, c, k);
            }

            for (size_t i = 0; i < gf.u_q; i++)
            { /* Second q*q rows */
                square = gf.times(i,i);
                ksquare = gf.times(kay,square);
                for (size_t j = 0; j < gf.u_q; j++)
                {
                    row = gf.u_q * gf.u_q + i * gf.u_q + j;
                    col = 0;
                    if (col < u_ncol)
                    {
                        A(row, col++) = static_cast<int>(j);
                    }
                    for (size_t m = 1; m < gf.u_q && col < u_ncol; m++, col++)
                    {
                        A(row,col) = gf.plus(A(row - gf.u_q * gf.u_q, col), b[m]);
                    }
                    if (col < u_ncol)
                    {
                        A(row,col++) = gf.plus(ksquare,j); /* q+1 */
                    }
                    for (size_t m = 1; m < gf.u_q && col < u_ncol; m++)
                    {
                        temp = gf.times(i,k[m]);
                        temp = gf.plus(ksquare,temp);
                        temp = gf.plus(j,temp);
                        A(row,col++) = gf.plus(temp,c[m]);
                    }
                    if (col < u_ncol)
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
                ostringstream_runtime_error(msg);
            }

            if (ncol > 2 * q + 1)
            {
                msg << "The Bose-Bush construction needs ncol <= 2q+1.\n";
                msg << "Can't have ncol = " << ncol << " with q = " << q << ".\n";
                ostringstream_runtime_error(msg);
            }

            return SUCCESS_CHECK;
        }

        int bosebush(GaloisField & gf, bclib::matrix<int> & B, int ncol)
        {
            int mul;
			size_t irow;
            size_t u_ncol = static_cast<size_t>(ncol);
            size_t q_star = gf.u_q;
            size_t s = q_star / 2; // s is the same as q since q_star = 2 * q
            
            bclib::matrix<int> A(s, q_star);

            // bosebushcheck throws if it fails
            bosebushcheck(static_cast<int>(s), gf.p, ncol);

            irow = 0;
            for (size_t i = 0; i < q_star; i++)
            {
                for (size_t j = 0; j < q_star; j++)
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
                    // the original code has this j < ncol && j < 2*s+1
                    //   however, A has dimensions of [s,2*q] so this must stop at either the number of columns or 2*q
                    //   for (size_t j = 0; j < u_ncol && j < 2 * s + 1; j++)
                    for (size_t j = 0; j < u_ncol && j < 2 * s; j++)
                    {
                        B(irow,j) = A(k,j);
                    }
                    if (u_ncol == 2 * s + 1)
                    {
                        B(irow, u_ncol - 1) = static_cast<int>(i % s);
                    }
                    irow++;
                }
            }
            return SUCCESS_CHECK;
        }

        int bosebushlcheck(int s, int p, int lam, int ncol)
        {
            std::ostringstream msg;
            if (primes::isprime(p) == 0)
            {
                msg << "Bose Bush routine given a nonprime.\n";
                ostringstream_runtime_error(msg);
            }

            if (ncol > lam * s + 1)
            {
                msg << "The Bose-Bush construction needs ncol <= lambda*q+1.\n";
                msg << "Can't have ncol = " << ncol << " with lam = " << lam << "\n";
                msg << "and q = " << s << ".\n";
                ostringstream_runtime_error(msg);
            }

            return SUCCESS_CHECK;
        }

        int bosebushl(GaloisField & gf, int lam, bclib::matrix<int> & B, int ncol)
        /* Implement Bose and Bush's 1952 A.M.S. method with given lambda */
        {
            int irow;
            int mul;
            size_t u_ncol = static_cast<size_t>(ncol);

            size_t s = gf.u_q / lam; /* number of levels in design */
            bclib::matrix<int> A(s, gf.u_q);

            // bosebushlcheck throws if it fails
            bosebushlcheck(static_cast<int>(s), gf.p, lam, ncol);

            irow = 0;
            for (size_t i = 0; i < gf.u_q; i++)
            {
                for (size_t j = 0; j < gf.u_q; j++)
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
                    for (size_t j = 0; j < u_ncol && j < lam * s + 1 && j < gf.u_q; j++)
                    {
                        B(irow,j) = A(k,j);
                    }
                    if (ncol == lam * static_cast<int>(s) + 1)
                    {
                        B(irow, u_ncol - 1) = static_cast<int>(i % s);
                    }
                    irow++;
                }
            }
            return SUCCESS_CHECK;
        }
    } // end namespace
} // end namespace  
