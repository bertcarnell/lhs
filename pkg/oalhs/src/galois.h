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

#include "CommonDefines.h"
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
         * @param p
         * @param n
         * @param xton
         * @param p1
         * @param p2
         * @param prod
         */
		void GF_poly_prod(int p, int n, std::vector<int> & xton, std::vector<int> p1, std::vector<int> p2, std::vector<int> & prod );
        
        /**
         * Addition in polynomial representation
         * 
         * @param p
         * @param n
         * @param p1
         * @param p2
         * @param sum
         */
		void GF_poly_sum(int p, int n, std::vector<int> p1, std::vector<int> p2, std::vector<int> & sum );
        
        /**
         * Convert polynomial to integer in <code>0..q-1</code>
         * 
         * @param p
         * @param n
         * @param poly
         * @return 
         */
		int GF_poly2int( int p, int n, std::vector<int> & poly );
        
        /**
         * Print a Galois field
         * @param gf
         */
		void GF_print(GF & gf);
        
        /**
         * Prepare (+,*,^-1) lookup tables
         * 
         * @param gf
         * @param p
         * @param n
         * @param xton
         * @return 
         */
		int GF_ready(GF & gf, int p, int n, std::vector<int> & xton );
        
        /**
         * 
         * @param q
         * @param gf
         * @return 
         */
		int GF_getfield(int q, GF & gf);
        
        /**
         * 
         */
		void GF_set_fields();
	}
}

#endif
