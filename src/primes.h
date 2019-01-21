/**
 * @file primes.h
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

#ifndef PRIMES_H
#define PRIMES_H

#include "OACommonDefines.h"

/**
 * Macro to indicate that a number is prime
 */
#define ISPRIMETRUE 1
/**
 * Macro to indicate that a number is not prime
 */
#define ISPRIMEFALSE 0

namespace oacpp {
    /**
     * Utilities related to prime numbers
     */
	namespace primes
	{
        /**
         * returns 1 for prime argument
         * @param n number to test
         * @return 1 if <code>p</code> is prime
         */
		int isprime(unsigned int n);

        /**
         * Is the number prime
         * @deprecated due to slowness
         * @param p number
         * @return 1 if prime, 0 otherwise
         */
        int isprime_old(int p);
        
        /**
         * find q=p^n if q is a prime power with n>0
         * @param q integer that is a prime power
         * @param p the prime base
         * @param n the integer power
         * @param isit an indicator of completion
         */
		void primepow(int q, int* p, int* n, int* isit);
        
        /**
         * returns 1 for prime power argument
         * @param q
         * @return 
         */
		int isprimepow(int q );
        
        /**
         * pow() with integer arguments and value
         * @param a
         * @param b
         * @return 
         */
		int ipow( int a, int b );
	} // end namespace
}// end namespace

#endif
