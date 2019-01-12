/**
 * @file construct.h
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

#ifndef CONSTRUCT_H
#define CONSTRUCT_H

/*  Constructions for designs using Galois fields */

#include "OACommonDefines.h"
#include "galois.h"
#include "ak.h"

/*  Glossary:



*/

namespace oacpp {
    /**
     * Namespace to construct Orthogonal Arrays using various algorithms
     */
	namespace oaconstruct
	{
        /**
         * Construct an orthogonal array using the bose algorithm
         * 
         * OA( q^2, q+1, q, 2  )
         * R.C. Bose (1938) Sankhya Vol 3 pp 323-338
         * 
         * @param gf galois field
         * @param A an orthogonal array
         * @param ncol the number of columns
         * @return an indicator of success
         */
		int bose(GF & gf, bclib::matrix<int> & A, int ncol );
        
        /**
         * Construct an orthogonal array using the bush algorithm
         * @param gf
         * @param A
         * @param str
         * @param ncol
         * @return 
         */
		int bush(GF & gf, bclib::matrix<int> &  A, int str, int ncol  );
        
        /**
         * 
         * Implement Addelman and Kempthorne's 1961 A.M.S. method with n=2
         * 
         * @param gf
         * @param A
         * @param ncol
         * @return 
         */
		int addelkemp(GF & gf, bclib::matrix<int> & A, int ncol );
        
        /**
         * Construct an orthogonal array using the bosebush algorithm
         * 
         * OA( 2q^2, 2q+1, q, 2 ), only implemented for q=2^n
         * Implement Bose and Bush's 1952 A.M.S. method with p=2, u=1
         * 
         * @param gf
         * @param B
         * @param ncol
         * @return 
         */
		int bosebush(GF & gf, bclib::matrix<int> & B, int ncol );
        
        /**
         * Construct an orthogonal array using the bose-bush algorithm
         * 
         * @param gf
         * @param lam
         * @param B
         * @param ncol
         * @return 
         */
		int bosebushl(GF & gf, int lam, bclib::matrix<int> & B, int ncol );

        /**
         * Check the input to the bose algorithm
         * @param q the number of symbols
         * @param ncol the number of columns
         * @return an indicator of success
         */
		int bosecheck(int q, int ncol );
        
        /**
         * 
         * @param n
         * @param q
         * @param d
         * @param coef
         * @return 
         */
		int itopoly(int n, int q, int d, std::vector<int> & coef );
        
        /**
         * Evaluate a polynomial with coefficients, argument and result in a Galois field
         * @param gf a Galois field
         * @param d
         * @param poly
         * @param arg
         * @param value
         * @return 
         */
		int polyeval(GF & gf, int d, std::vector<int> & poly, int arg, int* value );
        
        /**
         * 
         * @param q
         * @param str
         * @param ncol
         * @return 
         */
		int bushcheck(int q, int str, int ncol);
        
        /**
         * 
         * @param q
         * @param p
         * @param ncol
         * @return 
         */
		int bosebushcheck(int q, int p, int ncol  );
        
        /**
         * 
         * @param s
         * @param p
         * @param lam
         * @param ncol
         * @return 
         */
		int bosebushlcheck(int s, int p, int lam, int ncol  );
        
        /**
         * 
         * @param q
         * @param p
         * @param ncol
         * @return 
         */
		int addelkempcheck(int q, int p, int ncol );
	}
}// end namespace

#endif
