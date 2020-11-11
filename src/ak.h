/**
 * @file ak.h
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

#ifndef AK_H
#define AK_H

#include "OACommonDefines.h"
#include "GaloisField.h"
#include "primes.h"
#include "matrix.h"

namespace oacpp {
    /**
     * Addelkemp class
     */
	namespace oaaddelkemp 
	{
        /**
         * Check that the parameters of the addelkemp3 algorithm are consistent
		 * (<code>ncol <= 2q^2+2q+1</code>
         * 
         * @param q the order of the Galois field or the number of symbols
         * @param p the prime basis of the Galois field
         * @param ncol the number of columns
         * @return an indicator of success
         */
		int addelkemp3check(int q, int p, int ncol);
        
        /**
         * Addelkemp algorithm for even <code>p</code>
         * 
         * @param gf a Galois field
         * @param kay the number of columns
         * @param b original Addelkemp variable
         * @param c original Addelkemp variable
         * @param k original Addelkemp variable
         * @return an indicator of success
         */
		int akeven(GaloisField & gf, int* kay, std::vector<int> & b, std::vector<int> & c, std::vector<int> & k);
        
        /**
         * Addelkemp algorithm for odd <code>p</code>
         * 
         * @param gf a Galois field object
         * @param kay the number of columns
         * @param b original Addelkemp variable
         * @param c original Addelkemp variable
         * @param k original Addelkemp variable
         * @return an indicator of success
         */
		int akodd(GaloisField & gf, int* kay, std::vector<int> & b, std::vector<int> & c, std::vector<int> & k);
        
        /**
         * Check that the parameters are consistent for the addelkempn algorithm
         * 
         * @param q the order of Galois field or the number of symbols
         * @param p the prime basis of the Galois field
         * @param akn the <code>akn</code> algorithm produces OA(2q^n,ncol,q,2)
         * @param ncol the number of columns
         * @return an indicator of success
         * @throws runtime_exception
         */
		void addelkempncheck(int q, int p, int akn, int ncol);
        
        /**
         * The addelkemp algorithm for general n to produce OA(2q^n,ncol,q,2)
         * 
         * @param gf a Galois Field
         * @param akn the <code>akn</code> algorithm produces OA(2q^n,ncol,q,2)
         * @param A the orthogonal array
         * @param ncol the number of columns
         * @return an indicator of success
         */
		int addelkempn(GaloisField & gf, int akn, bclib::matrix<int> & A, int ncol);
        
        /**
         * The addelkemp algorithm for n=3
         * 
         * @param gf galois field
         * @param A the orthogonal array
         * @param ncol the number of columns
         * @return an indicator of success
         */
		int addelkemp3(GaloisField & gf, bclib::matrix<int> & A, int ncol );
	}
}

#endif
