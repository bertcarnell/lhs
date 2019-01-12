/**
 * @file akconst.cpp
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
        /*  Find constants for Addelman Kempthorne designs
          when q is even. */
        int akeven(GF & gf, int* kay, std::vector<int> & b, std::vector<int> & c, std::vector<int> & k)
        {
            size_t q = static_cast<size_t>(gf.q);

            if (q > 4)
            {
                std::string msg = "Addelman Kempthorne designs not yet available for \n even q >4.";
                throw std::runtime_error(msg.c_str());
            }

            *kay = 1;

            if (q == 2)
            {
                b[1] = c[1] = k[1] = 1;
            }
            if (q == 4)
            {
                b[1] = c[1] = 2;
                b[2] = c[2] = 1;
                b[3] = c[3] = 3;
                k[1] = 1;
                k[2] = 2;
                k[3] = 3;
            }

            // TODO: isn't this redundant to the above for q <= 4
            for (size_t i = 1; i < q; i++)
            {
                k[i] = static_cast<int>(i);
            }

            return 0;
        }

        int akodd(GF & gf, int* kay, std::vector<int> & b, std::vector<int> & c, std::vector<int> & k)
        {
            int num, den, four;

            size_t q = static_cast<size_t>(gf.q);
            size_t p = static_cast<size_t>(gf.p);

            if (p != 3)
            {
                four = 4;
            }
            else
            {
                four = 1;
            }

            *kay = 0;
            for (size_t i = 2; i < q; i++)
            {
                if (gf.root[i] == -1)
                {
                    *kay = static_cast<int>(i);
                }
            }
            if (*kay == 0)
            {
                std::ostringstream s;
                s << "Problem: no rootless element in GF(" << gf.n << ").\n";
                throw std::runtime_error(s.str().c_str());
            }

            for (size_t i = 1; i < q; i++)
            {
                num = gf.plus(*kay,p - 1); /* -1 = +(p-1) */
                den = gf.times(*kay,four);
                den = gf.times(den,i);
                b[i] = gf.times(num,gf.inv[den]);
                k[i] = gf.times(*kay,i);
                c[i] = gf.times(i,i);
                c[i] = gf.times(c[i],num);
                c[i] = gf.times(c[i],gf.inv[four]);
            }
            return 0;
        }
    } // end namespace
} // end namespace
