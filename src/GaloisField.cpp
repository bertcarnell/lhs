/**
 * @file GaloisField.cpp
 * @author Robert Carnell
 * @copyright Copyright (c) 2020, Robert Carnell
 *
 * License:  MIT
 * 
 * This class is based on the code by Art Owen in galdef.h, galois.h, xtnset.h, xtndispatch.h, xtndeclare.h
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

#include "GaloisField.h"

namespace oacpp
{
    std::vector<int> GaloisField::initializePowerCycle(int q)
    {
        std::vector<int> xtn;

#include "xtn.h"

        return xtn;
    }

    void GaloisField::fillAllPolynomials()
    {
        assert(u_q > 0 && u_n > 0); // NOLINT
        poly = bclib::matrix<int>(u_q, u_n);
        size_t click = 0;

        for (size_t i = 0; i < u_n; i++)
        {
            poly(0, i) = 0;
        }

        for (size_t i = 1; i < u_q; i++)
        {
            for (click = 0; poly(i - 1, click) == (p - 1); click++)
            {
                poly(i, click) = 0;
            }
            poly(i, click) = poly(i - 1, click) + 1;
            for (size_t j = click + 1; j < u_n; j++)
            {
                poly(i, j) = poly(i - 1, j);
            }
        }
    }

    void GaloisField::computeSumsAndProducts()
    {
        assert(u_n > 0 && u_q > 0); // NOLINT
        assert(poly.rowsize() == u_q && xton.size() == u_n && poly.colsize() == u_n); // NOLINT
        
        std::vector<int> temppoly(u_n);
        plus = bclib::matrix<int>(u_q, u_q);
        times = bclib::matrix<int>(u_q, u_q);

        for (size_t i = 0; i < u_q; i++)
        {
            for (size_t j = 0; j < u_q; j++)
            {
                GaloisField::polySum(p, u_n, poly.getrow(i), poly.getrow(j), temppoly);
                plus(i, j) = GaloisField::poly2int(p, n, temppoly);
                GaloisField::polyProd(p, u_n, xton, poly.getrow(i), poly.getrow(j), temppoly);
                times(i, j) = GaloisField::poly2int(p, n, temppoly);
            }
        }
    }

    void GaloisField::computeMultiplicativeInverse()
    {
        assert(u_q > 0 && !times.isEmpty());  // NOLINT
        inv = std::vector<int>(u_q);
        std::ostringstream msg;

        for (size_t i = 0; i < u_q; i++)
        {
            inv[i] = -1;
            for (size_t j = 0; j < u_q; j++)
            {
                if (times(i, j) == 1)
                {
                    inv[i] = static_cast<int>(j);
                }
            }
            if (i > 0 && inv[i] <= 0)
            { // LCOV_EXCL_START
                msg << "There is something wrong with the Galois field\n";
                msg << "used for q=" << q << ".  Element " << i << "has no reciprocal.\n";
                ostringstream_runtime_error(msg);
            } // LCOV_EXCL_STOP
        }
    }

    void GaloisField::computeNegative()
    {
        assert(u_q > 0 && !plus.isEmpty()); // NOLINT
        neg = std::vector<int>(u_q);
        std::ostringstream msg;

        for (size_t i = 0; i < u_q; i++)
        {
            neg[i] = -1;
            for (size_t j = 0; j < u_q; j++)
            {
                if (plus(i, j) == 0)
                {
                    neg[i] = static_cast<int>(j);
                }
            }
            if (i > 0 && neg[i] <= 0)
            { // LCOV_EXCL_START
                msg << "There is something wrong with the Galois field\n";
                msg << "used for q=" << q << ".  Element " << i << " has no negative.\n";
                ostringstream_runtime_error(msg);
            } // LCOV_EXCL_STOP
        }
    }

    void GaloisField::computeRoots()
    {
        assert(u_q > 0 && !times.isEmpty()); // NOLINT
        root = std::vector<int>(u_q);
        for (size_t i = 0; i < u_q; i++)
        {
            root[i] = -1;
            for (size_t j = 0; j < u_q; j++)
            {
                if (times(j, j) == static_cast<int>(i))
                {
                    root[i] = static_cast<int>(j);
                }
            }
        }
    }

    GaloisField::GaloisField(int q)
    {
        this->q = q;
        this->p = 0;
        this->n = 0;
        int ispp = 0;
        std::ostringstream msg;
        u_q = static_cast<size_t>(q);

        if (q < 1)
        { /* Impossible argument */
            msg << "Field must have positive number of elements.\n";
            ostringstream_runtime_error(msg);
        }
        if (q == 1)
        { /* Pointless  argument */
            msg << "Field with 1 element was requested. \n";
            ostringstream_runtime_error(msg);
        }

        primes::primepow(q, &p, &n, &ispp);
        u_n = static_cast<size_t>(n);

        if (ispp == 0)
        {
            msg << "q=" << q << " is not a prime power.\n";
            ostringstream_runtime_error(msg);
        }

        if (primes::isprime(q) != 0)
        {
            xton = { 0 }; /* Could have tested p=q, or n=1 */
        }
        else
        {
            xton = GaloisField::initializePowerCycle(q);
        }

        if (xton.empty())
        {
            msg << "GF(" << q << ") = GF(" << p << "^" << n << ") is not\n";
            msg << "included in this program. To add it, consider modifying gfields.c.\n";
            ostringstream_runtime_error(msg);
        }

        // create a matrix containing all polynomials in the Galois Field
        fillAllPolynomials();
        // fill sum and product tables of the Galois Field
        computeSumsAndProducts();
        // compute multiplicative inverse polynomial index
        computeMultiplicativeInverse();
        // compute negative index
        computeNegative();
        // compute roots of polynomials
        computeRoots();
    }

    GaloisField::GaloisField()
    {
        q = 0;
        p = 0;
        n = 0;
        u_n = 0;
        u_q = 0;
    }

    void GaloisField::polySum(int p, size_t u_n, const std::vector<int> & p1, const std::vector<int> & p2, std::vector<int> & sum)
    {
        assert(p > 0 && u_n > 0); // NOLINT
        assert(p1.size() == u_n && p2.size() == u_n && sum.size() == u_n); // NOLINT

        for (size_t i = 0; i < u_n; i++)
        {
            sum[i] = (p1[i] + p2[i]) % p;
        }
    }

    void GaloisField::polyProd(int p, size_t u_n, const std::vector<int> & xton, const std::vector<int> & p1, 
        const std::vector<int> & p2, std::vector<int> & prod)
    {
        assert(p > 0 && u_n > 0); // NOLINT
        assert(xton.size() == u_n && p1.size() == u_n && p2.size() == u_n && prod.size() == u_n); // NOLINT
        int n = static_cast<int>(u_n);
        std::vector<int> longprod(2 * u_n - 1);

        longprod.assign(2 * u_n - 1, 0);
        for (size_t i = 0; i < u_n; i++)
        {
            for (size_t j = 0; j < u_n; j++)
            {
                longprod[i + j] += p1[i] * p2[j];
            }
        }
        for (int i = 2 * n - 2; i > n - 1; i--) // has to be an int to decrement less than zero
        {
            size_t ui = static_cast<size_t>(i);
            for (size_t j = 0; j < u_n; j++)
            {
                longprod[ui - u_n + j] += xton[j] * longprod[ui];
            }
        }
        for (size_t i = 0; i < u_n; i++)
        {
            prod[i] = longprod[i] % p;
        }
    }

    int GaloisField::poly2int(int p, int n, const std::vector<int> & poly)
    {
        assert(p > 0 && n > 0); // NOLINT
        assert(poly.size() == static_cast<size_t>(n)); // NOLINT
        int ans = 0;

        for (int i = n - 1; i > 0; i--) // has to be an int to decrement less than zero
        {
            size_t ui = static_cast<size_t>(i);
            ans = (ans + poly[ui]) * p;
        }
        ans += poly[0];

        return ans;
    }

    void GaloisField::print() // LCOV_EXCL_START
    {
        if (q > 999)
        {
            PRINT_OUTPUT << "Warning q=" << q << " will overflow print field.\n";
        }

        PRINT_OUTPUT << "\nFor GF(" << q << ") p=" << p << " n=" << n << "\n";
        PRINT_OUTPUT << "x**n = (";
        for (size_t i = 0; i < u_n - 1; i++)
        {
            PRINT_OUTPUT << xton[i] << ",";
        }
        PRINT_OUTPUT << xton[u_n - 1] << ")\n";
        PRINT_OUTPUT << "\n\nGF(" << q << ") Polynomial coefficients:\n";
        for (size_t i = 0; i < u_q; i++)
        {
            PRINT_OUTPUT << "  " << i << "  ";
            for (size_t j = 0; j < u_n; j++)
            {
                PRINT_OUTPUT << poly(i, j) << " ";
            }
            PRINT_OUTPUT << "\n";
        }
        PRINT_OUTPUT << "\n\nGF(" << q << ") Addition Table\n";
        for (size_t i = 0; i < u_q; i++)
        {
            PRINT_OUTPUT << "  ";
            for (size_t j = 0; j < u_q; j++)
            {
                PRINT_OUTPUT << " " << plus(i, j);
            }
            PRINT_OUTPUT << "\n";
        }
        PRINT_OUTPUT << "\n\nGF(" << q << ") Multiplication table\n";
        for (size_t i = 0; i < u_q; i++)
        {
            PRINT_OUTPUT << "  ";
            for (size_t j = 0; j < u_q; j++)
            {
                PRINT_OUTPUT << " " << times(i, j);
            }
            PRINT_OUTPUT << "\n";
        }
        PRINT_OUTPUT << "\n\nGF(" << q << ") Reciprocals\n";
        for (size_t i = 1; i < u_q; i++)
        {
            PRINT_OUTPUT << " " << i << " " << inv[i] << "\n";
        }

        PRINT_OUTPUT << "\n\nGF(" << q << ") Negatives\n";
        for (size_t i = 0; i < u_q; i++)
        {
            PRINT_OUTPUT << " " << i << " " << neg[i] << "\n";
        }

        PRINT_OUTPUT << "\n\nGF(" << q << ") Square roots\n";
        for (size_t i = 0; i < u_q; i++)
        {
            PRINT_OUTPUT << " " << i << " " << root[i] << "\n";
        }
    } // LCOV_EXCL_STOP
}
