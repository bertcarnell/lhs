/**
 * @file akn.cpp
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
        void addelkempncheck(int q, int p, int akn, int ncol)
        {
            std::ostringstream msg;
            if (akn < 2)
            {
                msg << "This Addelman-Kempthorne OA(2q^n,ncol,q,2) is only available for n >= 2.  n = " << akn << " was requested.\n";
                ostringstream_runtime_error(msg);
            }

            if (p == 2 && q > 4)
            {
                msg << "This Addelman-Kempthorne OA(2q^n,ncol,q,2) is only available for odd prime powers q and for even prime \n powers q<=4. \n";
                ostringstream_runtime_error(msg);
            }

            if (ncol > 2 * (primes::ipow(q, akn) - 1) / (q - 1) - 1)
            {
                msg << "The Addelman-Kempthorne construction needs ncol <= 2(q^n-1)(q-1) -1. Can't have ncol = " << ncol << " with n=" << akn << " and q = " << q << "\n";
                ostringstream_runtime_error(msg);
            }
        }

        /* Implement Addelman and Kempthorne's 1961 A.M.S. method with n=3 */
        int addelkempn(GaloisField & gf, int akn, bclib::matrix<int> & A, int ncol)
        {
            int kay; /* A&K notation */
            int col, square, ksquare;
            int monic, elt;
            size_t numin;
            size_t aknu = static_cast<size_t>(akn);

            addelkempncheck(gf.q, gf.p, akn, ncol);

            std::vector<int> b(gf.u_q);
            std::vector<int> c(gf.u_q);
            std::vector<int> k(gf.u_q);
            std::vector<int> x(aknu);
            std::vector<int> s(aknu);
            std::vector<int> coef(aknu);
            std::vector<int> indx(aknu);

            for (size_t i = 0; i < aknu; i++)
            {
                x[i] = 0;
            }
            for (size_t row = 0; row < static_cast<size_t>(primes::ipow(gf.q, akn)); row++)
            { /* First q^akn rows */
                col = 0;
                s[0] = 1;
                for (size_t i = 1; i < aknu; i++) /* first subset */
                {
                    s[i] = 0; /* nonempty subsets of x indices */
                }

                for (size_t sub = 1; sub < static_cast<size_t>(primes::ipow(2, akn)) && col < ncol; sub++)
                {
                    monic = -1;
                    numin = 0;
                    for (size_t i = 0; i < aknu; i++)
                    {
                        if (s[i] != 0)
                        {
                            if (monic == -1)
                            {
                                monic = static_cast<int>(i);
                            }
                            else
                            {
                                indx[numin++] = static_cast<int>(i);
                            }
                        }
                    }
                    for (size_t i = 0; i < numin; i++)
                    {
                        coef[i] = 1;
                    }
                    for (size_t poly = 0; poly < static_cast<size_t>(primes::ipow(gf.q - 1, static_cast<int>(numin))) && col < ncol; poly++)
                    {
                        elt = x[monic];
                        for (size_t i = 0; i < numin; i++)
                        {
                            elt = gf.plus(elt, gf.times(coef[i],x[indx[i]]));
                        }
                        A(row,col++) = elt;
                        for (int i = static_cast<int>(numin) - 1; i >= 0; i--) // has to be an int to decrement
                        {
                            size_t ui = static_cast<size_t>(i);
                            coef[ui] = (coef[ui] + 1) % gf.q;
                            if (coef[ui] != 0)
                            {
                                break;
                            }
                            coef[ui] = 1;
                        }
                    }
                    for (size_t i = 0; i < aknu; i++)
                    {
                        s[i] = (s[i] + 1) % 2;
                        if (s[i] != 0)
                        {
                            break;
                        }
                    }
                }

                square = gf.times(x[0], x[0]);

                s[1] = 1;
                for (size_t i = 2; i < aknu; i++) /* first subset */
                {
                    s[i] = 0; /* nonempty subsets of x indices */
                }
                for (size_t sub = 1; sub < static_cast<size_t>(primes::ipow(2, akn - 1)) && col < ncol; sub++)
                {
                    monic = -1;
                    numin = 0;
                    for (size_t i = 1; i < aknu; i++)
                    {
                        if (s[i] != 0)
                        {
                            if (monic == -1)
                            {
                                monic = static_cast<int>(i);
                            }
                            else
                            {
								indx[numin++] = static_cast<int>(i);
                            }
                        }
                    }
                    coef[0] = 0;
                    for (size_t i = 1; i < numin + 1; i++)
                    {
                        coef[i] = 1;
                    }
					int polymax = gf.q * primes::ipow(gf.q - 1, static_cast<int>(numin));
                    for (size_t poly = 0; poly < static_cast<size_t>(polymax) && col < ncol; poly++)
                    {
                        elt = gf.plus(square,gf.times(x[0],coef[0]));
                        elt = gf.plus(elt,x[monic]);
                        for (size_t i = 1; i < numin + 1; i++)
                        {
                            elt = gf.plus(elt,gf.times(coef[i],x[indx[i - 1]]));
                        }
                        A(row,col++) = elt;
                        for (int i = static_cast<int>(numin) + 1 - 1; i >= 0; i--) // has to be an int
                        {
                            size_t ui = static_cast<size_t>(i);
                            coef[ui] = (coef[ui] + 1) % gf.q;
                            if (coef[ui] != 0)
                            {
                                break;
                            }
                            if (i > 0)
                            {
                                coef[ui] = 1;
                            }
                        }
                    }
                    for (size_t i = 1; i < aknu; i++)
                    {
                        s[i] = (s[i] + 1) % 2;
                        if (s[i] != 0)
                        {
                            break;
                        }
                    }
                }

                for (int i = akn - 1; i >= 0; i--) // has to be an int to decrement
                {
                    size_t ui = static_cast<size_t>(i);
                    x[ui] = (x[ui] + 1) % gf.q;
                    if (x[ui] != 0)
                    {
                        break;
                    }
                }
            }

            if (gf.p != 2) /* Constants kay,b,c,k for odd p */
            {
                akodd(gf, &kay, b, c, k);
            }
            else /* Constants kay,b,c,k for even p */
            {
                akeven(gf, &kay, b, c, k);
            }

            for (size_t i = 0; i < aknu; i++)
            {
                x[i] = 0;
            }
			int rowmax = 2 * primes::ipow(gf.q, akn);
            for (size_t row = static_cast<size_t>(primes::ipow(gf.q, akn)); row < static_cast<size_t>(rowmax); row++) /* Second q^akn rows */
            {
                col = 0;
                s[0] = 1;
                for (size_t i = 1; i < aknu; i++) /* first subset */
                {
                    s[i] = 0; /* nonempty subsets of x indices */
                }
                for (size_t sub = 1; sub < static_cast<size_t>(primes::ipow(2, akn)) && col < ncol; sub++)
                {
                    monic = -1;
                    numin = 0;
                    for (size_t i = 0; i < aknu; i++)
                    {
                        if (s[i] != 0)
                        {
                            if (monic == -1)
                            {
                                monic = static_cast<int>(i);
                            }
                            else
                            {
								indx[numin++] = static_cast<int>(i);
                            }
                        }
                    }
                    for (size_t i = 0; i < numin; i++)
                    {
                        coef[i] = 1;
                    }
                    for (size_t poly = 0; poly < static_cast<size_t>(primes::ipow(gf.q - 1, static_cast<int>(numin))) && col < ncol; poly++)
                    {
                        elt = x[monic];
                        if (numin != 0 && s[0] != 0)
                        {
                            elt = gf.plus(elt,b[coef[0]]);
                        }
                        for (size_t i = 0; i < numin; i++)
                        {
                            elt = gf.plus(elt,gf.times(coef[i],x[indx[i]]));
                        }
                        A(row,col++) = elt;
                        for (int i = static_cast<int>(numin) - 1; i >= 0; i--) // has to be an int to decrement
                        {
                            size_t ui = static_cast<size_t>(i);
                            coef[ui] = (coef[ui] + 1) % gf.q;
                            if (coef[ui] != 0)
                            {
                                break;
                            }
                            coef[ui] = 1;
                        }
                    }
                    for (size_t i = 0; i < aknu; i++)
                    {
                        s[i] = (s[i] + 1) % 2;
                        if (s[i] != 0)
                        {
                            break;
                        }
                    }
                }

                ksquare = gf.times(kay,gf.times(x[0],x[0]));

                s[1] = 1;
                for (size_t i = 2; i < aknu; i++) /* first subset */
                {
                    s[i] = 0; /* nonempty subsets of x indices */
                }
                for (size_t sub = 1; sub < static_cast<size_t>(primes::ipow(2, akn - 1)) && col < ncol; sub++)
                {
                    monic = -1;
                    numin = 0;
                    for (size_t i = 1; i < aknu; i++)
                    {
                        if (s[i] != 0)
                        {
                            if (monic == -1)
                            {
                                monic = static_cast<int>(i);
                            }
                            else
                            {
								indx[numin++] = static_cast<int>(i);
                            }
                        }
                    }
                    coef[0] = 0;
                    for (size_t i = 1; i < numin + 1; i++)
                    {
                        coef[i] = 1;
                    }
					int polymax = gf.q * primes::ipow(gf.q - 1, static_cast<int>(numin));
                    for (size_t poly = 0; poly < static_cast<size_t>(polymax) && col < ncol; poly++)
                    {
                        elt = gf.plus(ksquare,gf.times(x[0],k[coef[0]]));
                        elt = gf.plus(elt,x[monic]);
                        elt = gf.plus(elt,c[coef[0]]);
                        for (size_t i = 1; i < numin + 1; i++)
                        {
                            elt = gf.plus(elt,gf.times(coef[i],x[indx[i - 1]]));
                        }
                        A(row,col++) = elt;
                        for (int i = static_cast<int>(numin) + 1 - 1; i >= 0; i--) // has to be an int to decrement // don't understand + 1 - 1
                        {
                            size_t ui = static_cast<size_t>(i);
                            coef[ui] = (coef[ui] + 1) % gf.q;
                            if (coef[ui] != 0)
                            {
                                break;
                            }
                            coef[ui] = i > 0 ? 1 : 0;
                        }
                    }
                    for (size_t i = 1; i < aknu; i++)
                    {
                        s[i] = (s[i] + 1) % 2;
                        if (s[i] != 0)
                        {
                            break;
                        }
                    }
                }

                for (int i = static_cast<int>(aknu) - 1; i >= 0; i--) // has to be an int to decrement
                {
                    size_t ui = static_cast<size_t>(i);
                    x[ui] = (x[ui] + 1) % gf.q;
                    if (x[ui] != 0)
                    {
                        break;
                    }
                }
            }

            return SUCCESS_CHECK;
        }
    } // end namespace
} // end namespace
