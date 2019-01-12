/**
 * @file ak3.cpp
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

#include "ak.h"

namespace oacpp
{
    namespace oaaddelkemp
    {
        int addelkemp3check(int q, int p, int ncol)
        {
            std::string msg;
            if (p == 2 && q > 4)
            {
                msg = "This Addelman-Kempthorne OA(2q^3,ncol,q,2) is only \n available for odd prime powers q and for even prime \n powers q<=4.\n";
                throw std::runtime_error(msg.c_str());
            }

            if (q == 8)
            { /* Moot */
                msg = "This Addelman-Kempthorne OA(2*8^3,ncol,8,2) is experimental and not yet working.";
                throw std::runtime_error(msg.c_str());
            }

            if (ncol > 2 * q * q + 2 * q + 1)
            {
                std::ostringstream s;
                s << "The Addelman-Kempthorne (n=3) construction needs ncol <= 2q^2+2q+1. Can't have ncol = " << ncol << " with q = " << q << "\n";
                throw std::runtime_error(s.str().c_str());
            }

            return SUCCESS_CHECK;
        }

        /* Implement Addelman and Kempthorne's 1961 A.M.S. method with n=3 */
        int addelkemp3(GF & gf, bclib::matrix<int> & A, int ncol)
        {
            int kay;
            //std::vector<int> b, c, k; /* A&K notation */
            int square, ksquare;
			size_t row, col;

            int p = gf.p;
            size_t q = static_cast<size_t>(gf.q);

			// Throws on any error
			addelkemp3check(static_cast<int>(q), p, ncol);

            std::vector<int> b(q);
            std::vector<int> c(q);
            std::vector<int> k(q);

            for (size_t i1 = 0; i1 < q; i1++)
            { /* First q^3 rows */
                square = gf.times(i1,i1);
                for (size_t i2 = 0; i2 < q; i2++)
                {
                    for (size_t i3 = 0; i3 < static_cast<size_t>(q); i3++)
                    {
                        row = i3 + q * i2 + q * q * i1;
                        col = 0;
                        if (col < static_cast<size_t>(ncol))
                        {
                            A(row, col++) = static_cast<int>(i2); /*      y       */
                        }
                        for (size_t m1 = 1; m1 < q && col < static_cast<size_t>(ncol); m1++) /* x + my       */
                        {
                            A(row,col++) = gf.plus(i1,gf.times(m1,i2));
                        }
                        if (col < static_cast<size_t>(ncol))
                        {
                            A(row, col++) = static_cast<int>(i3); /*           z  */
                        }
                        for (size_t m2 = 1; m2 < q && col < static_cast<size_t>(ncol); m2++) /* x      + mz  */
                        {
                            A(row,col++) = gf.plus(i1,gf.times(m2,i3));
                        }
                        for (size_t m2 = 1; m2 < q && col < static_cast<size_t>(ncol); m2++) /*      y + mz  */
                        {
                            A(row,col++) = gf.plus(i2,gf.times(m2,i3));
                        }
                        for (size_t m1 = 1; m1 < q && col < static_cast<size_t>(ncol); m1++) /* x + my + nz  */
                        {
                            for (size_t m2 = 1; m2 < q && col < static_cast<size_t>(ncol); m2++)
                            {
                                A(row,col++) =
                                    gf.plus(i1,gf.plus(gf.times(m1,i2),gf.times(m2,i3)));
                            }
                        }
                        for (size_t m1 = 0; m1 < q && col < static_cast<size_t>(ncol); m1++) /* x^2 + mx + y */
                        {
                            A(row,col++) = gf.plus(square,
                                gf.plus(i2,
                                gf.times(m1,i1)));
                        }

                        for (size_t m1 = 0; m1 < q && col < static_cast<size_t>(ncol); m1++) /* x^2 + mx + z */
                        {
                            A(row,col++) = gf.plus(square,
                                gf.plus(i3,
                                gf.times(m1,i1)));
                        }

                        for (size_t m1 = 0; m1 < q && col < static_cast<size_t>(ncol); m1++) /* x^2 + mx + y + nz */
                        {
                            for (size_t m2 = 1; m2 < q && col < static_cast<size_t>(ncol); m2++)
                            {
                                A(row,col++)
                                    = gf.plus(square,
                                    gf.plus(i2,
                                    gf.plus( gf.times(m2,i3) ,
                                    gf.times(m1,i1)
                                    )
                                    )
                                    );
                            }
                        }
                        if (col < static_cast<size_t>(ncol))
                        {
                            A(row, col++) = static_cast<int>(i1); /* x            */
                        }
                    }
                }
            }

            if (p != 2)
            {
                akodd(gf, &kay, b, c, k); /* Get kay,b,c,k for odd p  */
            }
            else
            {
                akeven(gf, &kay, b, c, k); /* Constants kay,b,c,k for even p */
            }

            for (size_t i1 = 0; i1 < q; i1++)
            { /* Second q^3 rows */
                square = gf.times(i1,i1);
                ksquare = gf.times(kay,square);
                for (size_t i2 = 0; i2 < q; i2++)
                {
                    for (size_t i3 = 0; i3 < q; i3++)
                    {
                        row = i3 + q * i2 + q * q * i1 + q * q*q;
                        col = 0;
                        if (col < static_cast<size_t>(ncol))
                        {
                            A(row, col++) = static_cast<int>(i2); /*     y        */
                        }
                        for (size_t m1 = 1; m1 < q && col < static_cast<size_t>(ncol); m1++)
                        { /* x + my + b(m)      */
                            A(row,col) = gf.plus(i1,gf.times(m1,i2));
                            A(row,col) = gf.plus(A(row,col),b[m1]);
                            col++;
                        }
                        if (col < static_cast<size_t>(ncol))
                        {
                            A(row,col++) = static_cast<int>(i3); /*           z  */
                        }

                        for (size_t m2 = 1; m2 < q && col < static_cast<size_t>(ncol); m2++)
                        { /* x      + mz + b(m) */
                            A(row,col) = gf.plus(i1,gf.times(m2,i3));
                            A(row,col) = gf.plus(A(row,col),b[m2]);
                            col++;
                        }
                        for (size_t m2 = 1; m2 < q && col < static_cast<size_t>(ncol); m2++) /*      y + mz  */
                        {
                            A(row,col++) = gf.plus(i2,gf.times(m2,i3));
                        }

                        for (size_t m1 = 1; m1 < q && col < static_cast<size_t>(ncol); m1++) /* x + my + nz + b(m) */
                        {
                            for (size_t m2 = 1; m2 < q && col < static_cast<size_t>(ncol); m2++)
                            {
                                A(row,col) =
                                        gf.plus(i1,gf.plus(gf.times(m1,i2),gf.times(m2,i3)));
                                A(row,col) = gf.plus(A(row,col),b[m1]);
                                col++;
                            }
                        }

                        for (size_t m1 = 0; m1 < q && col < static_cast<size_t>(ncol); m1++)
                        { /* kx^2 + k(m)x + y + c(m)*/
                            A(row,col) = gf.plus(ksquare,
                                    gf.plus(i2,
                                    gf.times(k[m1],i1)));
                            A(row,col) = gf.plus(A(row,col),c[m1]);
                            col++;
                        }

                        for (size_t m1 = 0; m1 < q && col < static_cast<size_t>(ncol); m1++)
                        { /* kx^2 + k(m)x + z + c(m)*/
                            A(row,col) = gf.plus(ksquare,
                                    gf.plus(i3,
                                    gf.times(k[m1],i1)));
                            A(row,col) = gf.plus(A(row,col),c[m1]);
                            col++;
                        }

                        for (size_t m1 = 0; m1 < q && col < static_cast<size_t>(ncol); m1++) /* kx^2 + k(m)x + y + nz +c(m) */
                        {
                            for (size_t m2 = 1; m2 < q && col < static_cast<size_t>(ncol); m2++)
                            {
                                A(row,col)
                                        = gf.plus(ksquare,
                                        gf.plus(i2,
                                        gf.plus( gf.times(m2,i3) ,
                                        gf.times(k[m1],i1)
                                        )
                                        )
                                        );
                                A(row,col) = gf.plus( A(row,col) , c[m1] );
                                col++;
                            }
                        }
                        if (col < static_cast<size_t>(ncol))
                        {
                            A(row, col++) = static_cast<int>(i1); /* x            */
                        }
                    }
                }
            }
            return 1;
        }
    } // end namespace
} // end namespace
