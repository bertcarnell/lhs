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
        int addelkempncheck(int q, int p, int akn, int ncol) // LCOV_EXCL_START
        {
            std::ostringstream msg;
            if (akn < 2)
            {
                msg << "This Addelman-Kempthorne OA(2q^n,ncol,q,2) is only available for n >= 2.  n = " << akn << " was requested.\n";
				const std::string ss = msg.str();
				throw std::runtime_error(ss.c_str());
            }

            if (p == 2 && q > 4)
            {
                msg << "This Addelman-Kempthorne OA(2q^n,ncol,q,2) is only available for odd prime powers q and for even prime \n powers q<=4. \n";
				const std::string smsg = msg.str();
				throw std::runtime_error(smsg.c_str());
            }

            if (ncol > 2 * (primes::ipow(q, akn) - 1) / (q - 1) - 1)
            {
                msg << "The Addelman-Kempthorne construction needs ncol <= 2(q^n-1)(q-1) -1. Can't have ncol = " << ncol << " with n=" << akn << " and q = " << q << "\n";
				const std::string smsg = msg.str();
				throw std::runtime_error(smsg.c_str());
            }

            return SUCCESS_CHECK;
        }

        /* Implement Addelman and Kempthorne's 1961 A.M.S. method with n=3 */
        int addelkempn(GF & gf, int akn, bclib::matrix<int> & A, int ncol)
        {
            int p, q;
            int kay; /* A&K notation */
            int col, square, ksquare;
            int monic, elt;
            size_t numin;
            size_t aknu = static_cast<size_t> (akn);

            p = gf.p;
            q = gf.q;

            int test = addelkempncheck(q, p, akn, ncol);

            if (test != SUCCESS_CHECK)
            {
                return FAILURE_CHECK;
            }

            std::vector<int> b(q);
            std::vector<int> c(q);
            std::vector<int> k(q);
            std::vector<int> x(aknu);
            std::vector<int> s(aknu);
            std::vector<int> coef(aknu);
            std::vector<int> indx(aknu);

            for (size_t i = 0; i < aknu; i++)
            {
                x[i] = 0;
            }
            for (size_t row = 0; row < static_cast<size_t>(primes::ipow(q, akn)); row++)
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
                        if (s[i])
                        {
                            if (monic == -1)
                            {
                                monic = static_cast<int>(i);
                            }
                            // TODO: this might be an else on the if(s[i])
                            /*else
                            {
                                indx[numin++] = i;
                            }*/
                        }
                        else
                        {
                            indx[numin++] = static_cast<int>(i);
                        }
                    }
                    for (size_t i = 0; i < numin; i++)
                    {
                        coef[i] = 1;
                    }
                    for (size_t poly = 0; poly < static_cast<size_t>(primes::ipow(q - 1, static_cast<int>(numin))) && col < ncol; poly++)
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
                            coef[ui] = (coef[ui] + 1) % q;
                            if (coef[ui])
                            {
                                break;
                            }
                            else
                            {
                                coef[ui] = 1;
                            }
                        }
                    }
                    for (size_t i = 0; i < aknu; i++)
                    {
                        s[i] = (s[i] + 1) % 2;
                        if (s[i])
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
                        if (s[i])
                        {
                            if (monic == -1)
                            {
                                monic = static_cast<int>(i);
                            }
                            // this might be an else on the if(s[i])
                            /*else
                            {
                                indx[numin++] = i;
                            }*/
                        }
                        else
                        {
                            indx[numin++] = static_cast<int>(i);
                        }
                    }
                    coef[0] = 0;
                    for (size_t i = 1; i < numin + 1; i++)
                    {
                        coef[i] = 1;
                    }
					int polymax = q * primes::ipow(q - 1, static_cast<int>(numin));
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
                            coef[ui] = (coef[ui] + 1) % q;
                            if (coef[ui])
                            {
                                break;
                            }
                            else
                            {
                                if (i > 0)
                                {
                                    coef[ui] = 1;
                                }
                            }
                        }
                    }
                    for (size_t i = 1; i < aknu; i++)
                    {
                        s[i] = (s[i] + 1) % 2;
                        if (s[i])
                        {
                            break;
                        }
                    }
                }

                for (int i = akn - 1; i >= 0; i--) // has to be an int to decrement
                {
                    size_t ui = static_cast<size_t>(i);
                    x[ui] = (x[ui] + 1) % q;
                    if (x[ui])
                    {
                        break;
                    }
                }
            }

            if (p != 2) /* Constants kay,b,c,k for odd p */
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
			int rowmax = 2 * primes::ipow(q, akn);
            for (size_t row = static_cast<size_t>(primes::ipow(q, akn)); row < static_cast<size_t>(rowmax); row++) /* Second q^akn rows */
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
                        if (s[i])
                        {
                            if (monic == -1)
                            {
                                monic = static_cast<int>(i);
                            }
                            // this might be an else on the if(s[i])
                            /*else
                            {
                                indx[numin++] = i;
                            }*/
                        }
                        else
                        {
                            indx[numin++] = static_cast<int>(i);
                        }
                    }
                    for (size_t i = 0; i < numin; i++)
                    {
                        coef[i] = 1;
                    }
                    for (size_t poly = 0; poly < static_cast<size_t>(primes::ipow(q - 1, static_cast<int>(numin))) && col < ncol; poly++)
                    {
                        elt = x[monic];
                        if (numin && s[0])
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
                            coef[ui] = (coef[ui] + 1) % q;
                            if (coef[ui])
                            {
                                break;
                            }
                            else
                            {
                                coef[ui] = 1;
                            }
                        }
                    }
                    for (size_t i = 0; i < aknu; i++)
                    {
                        s[i] = (s[i] + 1) % 2;
                        if (s[i])
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
                        if (s[i])
                        {
                            if (monic == -1)
                            {
                                monic = static_cast<int>(i);
                            }
                            // this might be an else on the if(s[i])
                            /*else
                            {
                                indx[numin++] = i;
                            }*/
                        }
                        else
                        {
                            indx[numin++] = static_cast<int>(i);
                        }
                    }
                    coef[0] = 0;
                    for (size_t i = 1; i < numin + 1; i++)
                    {
                        coef[i] = 1;
                    }
					int polymax = q * primes::ipow(q - 1, static_cast<int>(numin));
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
                            coef[ui] = (coef[ui] + 1) % q;
                            if (coef[ui])
                            {
                                break;
                            }
                            else
                            {
                                coef[ui] = i > 0 ? 1 : 0;
                            }
                        }
                    }
                    for (size_t i = 1; i < aknu; i++)
                    {
                        s[i] = (s[i] + 1) % 2;
                        if (s[i])
                        {
                            break;
                        }
                    }
                }

                for (int i = static_cast<int>(aknu) - 1; i >= 0; i--) // has to be an int to decrement
                {
                    size_t ui = static_cast<size_t>(i);
                    x[ui] = (x[ui] + 1) % q;
                    if (x[ui])
                    {
                        break;
                    }
                }
            }

            return SUCCESS_CHECK;
        } // LCOV_EXCL_STOP
    } // end namespace
} // end namespace
