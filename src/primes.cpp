/**
 * @file primes.cpp
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

#include "primes.h"

namespace oacpp
{
    namespace primes
    {
        int isprime_old(int p) // LCOV_EXCL_START
        {
            if (p < 2)
            {
                return ISPRIMEFALSE;
            }

            /*  This is not the fastest, but it is likely to
            take negligible time compared to that used in constructing
            the Galois field or the experimental design
             */
            double maxDivisor = sqrt(static_cast<double>(p + 1));
            for (int k = 2; static_cast<double>(k) < maxDivisor; k++)
            {
                if ((p / k) * k == p)
                {
                    return ISPRIMEFALSE;
                }
            }
            return ISPRIMETRUE;
        } // LCOV_EXCL_STOP
        
        int isprime(unsigned int n)
        {
            // 0, 1
            if (n < 2) 
            {
                return ISPRIMEFALSE;
            }
            // 2, 3
            if (n < 4)
            {
                return ISPRIMETRUE;
            }
            // if n is divisible by 2, it is not prime // 4,6,8,10,...
            if (n % 2 == 0)
            {
                return ISPRIMEFALSE;
            }
            // 5 => sqrt(5)=2.1 => iMax=3 => i=3 => 5%3!=0 => prime
            // 7 => sqrt(7)=2.5 => iMax=3 => i=3 => 7%3!=0 => prime
            // 9 => sqrt(9)=3 => iMax=3 => i=3 => 9%3=0 => not prime
            size_t iMax = static_cast<size_t>(sqrt(static_cast<double>(n))) + 1;
            for (size_t i = 3; i <= iMax; i += 2)
            {
                if (n % i == 0)
                {
                    return ISPRIMEFALSE;
                }
            }

            return ISPRIMETRUE;
        }


        void primepow(int q, int* p, int* n, int* isit)
        {
            int firstfactor = 1; // maybe uninitialized otherwise

            *p = *n = *isit = 0;
            if (q <= 1)
            {
                return;
            }

            if (isprime(q) != 0)
            {
                *p = q;
                *n = 1;
                *isit = 1;
                return;
            }

            for (int k = 2; k < sqrt(static_cast<double>(q) + 1.0); k++)
            {
                if ((q % k) == 0)
                {
                    firstfactor = k;
                    break;
                }
            }
            if (isprime(firstfactor) == 0) // LCOV_EXCL_START
            {
                return;
            } // LCOV_EXCL_STOP

            while (true)
            {
                if (q == 1)
                {
                    *isit = 1;
                    *p = firstfactor;
                    return;
                }
                if (q % firstfactor == 0)
                {
                    *n += 1;
                    q /= firstfactor;
                }
                else
                {
                    return;
                }
            }
        }

        int isprimepow(int q)
        {
            int p, n, ispp;
            primepow(q, &p, &n, &ispp);
            return ispp;
        }

        int ipow(int a, int b)
        {
            return (int) pow((double) a, (double) b);
        }
    } // end namespace
} // end namespace
