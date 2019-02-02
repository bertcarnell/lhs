/**
 * @file gfields.cpp
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

namespace oacpp
{
    // include declarations of xtndeclare
#include "xtndeclare.h"
	/**
	 * p^1
	 */
    std::vector<int> xtnpt1;

	/**
	 * Indicator of whether the Galois fields are set-up
	 */
    int GF_fields_are_set = 0;

    void galoisfield::GF_set_fields()
    {
        /* Brute force set up of defining vectors, from Carmichael */

        /* Declare x-to-the-power-n vectors, for GFs p-to-the-n */

        if (GF_fields_are_set)
        {
            PRINT_OUTPUT << "Warning: Fields being re-initialized.  Possible memory waste.\n"; // LCOV_EXCL_LINE
        }

        // set variables
#include "xtnset.h"

        xtnpt1 = std::vector<int>(1);
        xtnpt1[0] = 0;
        GF_fields_are_set = 1;
    }

    int galoisfield::GF_getfield(int q, GF & gf)
    {
        std::vector<int> xtn;
        int p, n, ispp;
        std::ostringstream msg;

        if (!GF_fields_are_set)
        {
            GF_set_fields();
        }

        if (q < 1)
        { /* Impossible argument */
            msg << "Field must have positive number of elements.\n";
			const std::string smsg = msg.str();
			throw std::runtime_error(smsg.c_str());
        }
        if (q == 1)
        { /* Pointless  argument */
            msg << "Field with 1 element was requested. \n";
			const std::string smsg = msg.str();
			throw std::runtime_error(smsg.c_str());
        }

        primes::primepow(q, &p, &n, &ispp);
        if (!ispp)
        {
            msg << "q=" << q << " is not a prime power.\n";
			const std::string smsg = msg.str();
			throw std::runtime_error(smsg.c_str());
        }

        // include generated code
#include "xtndispatch.h"

        if (primes::isprime(q))
        {
            xtn = xtnpt1; /* Could have tested p=q, or n=1 */
        }

        if (!(xtn.empty()))
        {
            if (GF_ready(gf, p, n, xtn))
            {
                return 1;
            }
            else // LCOV_EXCL_START
            {
                msg << "Construction failed for GF(" << q << ").\n";
				const std::string smsg = msg.str();
				throw std::runtime_error(smsg.c_str());
            } // LCOV_EXCL_STOP
        }
        else
        {
            msg << "GF(" << q << ") = GF(" << p << "^" << n << ") is not\n";
            msg << "included in this program. To add it, consider modifying gfields.c.\n";
			const std::string smsg = msg.str();
			throw std::runtime_error(smsg.c_str());
        }
        return SUCCESS_CHECK;
    }

} // end namespace
