/**
 * @file galois.h
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
#ifndef GALOIS_H
#define GALOIS_H

#include "OACommonDefines.h"
#include "galdef.h"
#include "primes.h"

namespace oacpp {
    /**
     * Definitions for Galois Fields
     */
	namespace galoisfield
	{
        /**
         * Multiplication in polynomial representation
         * 
         * @param p modulus
         * @param n length of p1 and p2
         * @param xton representation of x^n
         * @param p1 polynomial 1
         * @param p2 polynomial 2
         * @param prod the product of the polynomials
         */
		void GF_poly_prod(int p, int n, std::vector<int> & xton, std::vector<int> p1, std::vector<int> p2, std::vector<int> & prod );
        
        /**
         * Addition in polynomial representation
         * 
         * @param p modulus
         * @param n the length of p1 and p2
         * @param p1 polynomial 1
         * @param p2 polynomial 2
         * @param sum the sum of the polynomials
         */
		void GF_poly_sum(int p, int n, std::vector<int> p1, std::vector<int> p2, std::vector<int> & sum );
        
        /**
         * Convert polynomial to integer in <code>0..q-1</code>
         * 
         * @param p polynomial multiplier
         * @param n the length of poly
         * @param poly the polynomial
         * @return an integer
         */
		int GF_poly2int( int p, int n, std::vector<int> & poly );
        
        /**
         * Print a Galois field
         * @param gf a Galois field struct
         */
		void GF_print(GF & gf);
        
        /**
         * Prepare (+,*,^-1) lookup tables
         * 
         * @param gf the Galois field
         * @param p the modulus
         * @param n the length of xton
         * @param xton the x^n vector
         * @return 1 for success
         */
		int GF_ready(GF & gf, int p, int n, std::vector<int> & xton );
        
        /**
         * Get a Galois field with q arguments
         * @param q the number of arguments
         * @param gf the Galois field
         * @return 1 for success
         */
		int GF_getfield(int q, GF & gf);
        
        /**
         * Set the Galois fields
         */
		void GF_set_fields();
	}
}

#endif
