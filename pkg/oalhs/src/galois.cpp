/**
 * @file galois.cpp
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

#include "galois.h"

/*     Manipulation of generic Galois fields.  See gfields.c
   for construction of specific Galois fields.  */

namespace oacpp
{
    namespace galoisfield
    {

        // TODO:  I am copying the entire object here, there may be a better way to do with with
        //  a row or column iterator in the matrix object since these are read only on p1 and p2
        // TODO: evaluate const for functions better
        void GF_poly_sum(int p, int n, std::vector<int> p1, std::vector<int> p2, std::vector<int> & sum)
        {
            for (size_t i = 0; i < static_cast<size_t>(n); i++)
            {
                sum[i] = (p1[i] + p2[i]) % p;
            }
        }

        // TODO:  I am copying the entire object here, there may be a better way to do with with
        //  a row or column iterator in the matrix object since these are read only on p1 and p2
        void GF_poly_prod(int p, int n, std::vector<int> & xton, std::vector<int> p1, std::vector<int> p2, std::vector<int> & prod)
        /*
          Set prod = p1*p2 with coefficients modulo p, and x^n replaced
        by polynomial xton.
         */
        {
            size_t nu = static_cast<size_t>(n);
            std::vector<int> longprod(2*nu-1);

            longprod.assign(2*nu-1, 0);
            for (size_t i = 0; i < nu; i++)
            {
                for (size_t j = 0; j < nu; j++)
                {
                    longprod[i + j] += p1[i] * p2[j];
                }
            }
            for (int i = 2 * n - 2; i > n - 1; i--) // has to be an int to decrement less than zero
            {
                size_t ui = static_cast<size_t>(i);
                for (size_t j = 0; j < nu; j++)
                {
                    longprod[ui - nu + j] += xton[j] * longprod[ui];
                }
            }
            for (size_t i = 0; i < nu; i++)
            {
                prod[i] = longprod[i] % p;
            }
        }

        int GF_poly2int(int p, int n, std::vector<int> & poly)
        {
            int ans = 0;

            for (int i = n - 1; i > 0; i--) // has to be an int to decrement less than zero
            {
                size_t ui = static_cast<size_t>(i);
                ans = (ans + poly[ui]) * p;
            }
            ans += poly[0];

            return ans;
        }

        /* 
           Make ready the Galois Field
         */
        int GF_ready(GF & gf, int p, int n, std::vector<int> & xton)
        {
            size_t q;
            std::ostringstream msg;

            std::vector<int> poly(n);

            gf.n = n;
            gf.p = p;
            q = 1;
            for (int i = 0; i < n; i++)
            {
                q *= p;
            }
            gf.q = q;
            gf.xton = std::vector<int>(n);
            for (size_t i = 0; i < static_cast<size_t>(n); i++)
            {
                gf.xton[i] = xton[i];
            }
            gf.plus = matrix<int>(q,q);
            gf.times = matrix<int>(q,q);
            gf.inv = std::vector<int>(q);
            gf.neg = std::vector<int>(q);
            gf.root = std::vector<int>(q);
            gf.poly = matrix<int>(q, n);

            for (size_t i = 0; i < static_cast<size_t>(n); i++)
            {
                gf.poly(0,i) = 0;
            }

            for (size_t i = 1; i < q; i++)
            {
                size_t click;
                for (click = 0; gf.poly(i - 1,click) == (p - 1); click++)
                {
                    gf.poly(i,click) = 0;
                }
                gf.poly(i,click) = gf.poly(i - 1,click) + 1;
                for (size_t j = click + 1; j < static_cast<size_t>(n); j++)
                {
                    gf.poly(i,j) = gf.poly(i - 1,j);
                }
            }

            for (size_t i = 0; i < q; i++)
            {
                for (size_t j = 0; j < q; j++)
                {
                    //GF_poly_sum(p, n, gf.poly[i], gf.poly[j], poly);
                    GF_poly_sum(p, n, gf.poly.getrow(i), gf.poly.getrow(j), poly);
                    gf.plus(i,j) = GF_poly2int(p, n, poly);
                    GF_poly_prod(p, n, xton, gf.poly.getrow(i), gf.poly.getrow(j), poly);
                    gf.times(i,j) = GF_poly2int(p, n, poly);
                }
            }

            for (size_t i = 0; i < q; i++)
            {
                gf.inv[i] = -1;
                for (size_t j = 0; j < q; j++)
                {
                    if (gf.times(i,j) == 1)
                    {
                        gf.inv[i] = j;
                    }
                }
                if (i > 0 && gf.inv[i] <= 0)
                {
                    msg << "There is something wrong with the Galois field\n";
                    msg << "used for q=" << q << ".  Element " << i << "has no reciprocal.\n";
                    throw std::runtime_error(msg.str().c_str());
                }
            }

            for (size_t i = 0; i < q; i++)
            {
                gf.neg[i] = -1;
                for (size_t j = 0; j < q; j++)
                    if (gf.plus(i,j) == 0)
                        gf.neg[i] = j;
                if (i > 0 && gf.neg[i] <= 0)
                {
                    msg << "There is something wrong with the Galois field\n";
                    msg << "used for q=" << q << ".  Element " << i << " has no negative.\n";
                    throw std::runtime_error(msg.str().c_str());
                }
            }

            for (size_t i = 0; i < q; i++)
            {
                gf.root[i] = -1;
                for (size_t j = 0; j < q; j++)
                {
                    if (gf.times(j,j) == static_cast<int>(i))
                    {
                        gf.root[i] = j;
                    }
                }
            }
            return 1;
        }

        void GF_print(GF & gf)
        {
            int n, p, q;

            n = gf.n;
            p = gf.p;
            q = gf.q;

            if (q > 999)
            {
                PRINT_OUTPUT("Warning q=%d will overflow print field.\n", q);
            }

            PRINT_OUTPUT("\nFor GF(%d) p=%d n=%d\n", q, p, n);
            PRINT_OUTPUT("x**n = (");
            for (int i = 0; i < n - 1; i++)
            {
                PRINT_OUTPUT("%d,", gf.xton[i]);
            }
            PRINT_OUTPUT("%d)\n", gf.xton[n - 1]);
            PRINT_OUTPUT("\n\nGF(%d) Polynomial coefficients:\n", q);
            for (int i = 0; i < q; i++)
            {
                PRINT_OUTPUT("  %3d  ", i);
                for (int j = 0; j < n; j++)
                {
                    PRINT_OUTPUT("%3d ", gf.poly(i,j));
                }
                PRINT_OUTPUT("\n");
            }
            PRINT_OUTPUT("\n\nGF(%d) Addition Table\n", q);
            for (int i = 0; i < q; i++)
            {
                PRINT_OUTPUT("  ");
                for (int j = 0; j < q; j++)
                {
                    PRINT_OUTPUT(" %3d", gf.plus(i,j));
                }
                PRINT_OUTPUT("\n");
            }
            PRINT_OUTPUT("\n\nGF(%d) Multiplication table\n", q);
            for (int i = 0; i < q; i++)
            {
                PRINT_OUTPUT("  ");
                for (int j = 0; j < q; j++)
                {
                    PRINT_OUTPUT(" %3d", gf.times(i,j));
                }
                PRINT_OUTPUT("\n");
            }
            PRINT_OUTPUT("\n\nGF(%d) Reciprocals\n", q);
            for (int i = 1; i < q; i++)
            {
                PRINT_OUTPUT(" %3d %3d\n", i, gf.inv[i]);
            }

            PRINT_OUTPUT("\n\nGF(%d) Negatives\n", q);
            for (int i = 0; i < q; i++)
            {
                PRINT_OUTPUT(" %3d %3d\n", i, gf.neg[i]);
            }

            PRINT_OUTPUT("\n\nGF(%d) Square roots\n", q);
            for (int i = 0; i < q; i++)
            {
                PRINT_OUTPUT(" %3d %3d\n", i, gf.root[i]);
            }
        }
    } // end namespace
} // end namespace
