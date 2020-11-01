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
#include "GaloisField.h"
#include "ak.h"

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
         * @param gf a Galois field
         * @param A an matrix to return the orthogonal array
         * @param ncol the number of columns
         * @return an indicator of success
         */
		int bose(GaloisField & gf, bclib::matrix<int> & A, int ncol );
        
        /**
         * Construct an orthogonal array using the bush algorithm
         * @param gf a Galois field
         * @param A an matrix to return the orthogonal array
         * @param str the array strength
         * @param ncol the desired number of columns
         * @return an indicator of success
         */
		int bush(GaloisField & gf, bclib::matrix<int> &  A, int str, int ncol  );
        
        /**
         * Implement Addelman and Kempthorne's 1961 A.M.S. method with n=2
         * 
         * @param gf a Galois field
         * @param A an matrix to return the orthogonal array
         * @param ncol the desired number of columns
         * @return an indicator of success
         */
		int addelkemp(GaloisField & gf, bclib::matrix<int> & A, int ncol );
        
        /**
         * Construct an orthogonal array using the bosebush algorithm
         * 
         * OA( 2q^2, 2q+1, q, 2 ), only implemented for q=2^n
         * Implement Bose and Bush's 1952 A.M.S. method with p=2, u=1
         * 
         * @param gf a Galois field
         * @param B an matrix to return the orthogonal array
         * @param ncol the desired number of columns
         * @return an indicator of success
         */
		int bosebush(GaloisField & gf, bclib::matrix<int> & B, int ncol );
        
        /**
         * Construct an orthogonal array using the bose-bush algorithm
         * 
         * @param gf a Galois field
         * @param lam lambda
         * @param B an matrix to return the orthogonal array
         * @param ncol the desired number of columns
         * @return an indicator of success
         */
		int bosebushl(GaloisField & gf, int lam, bclib::matrix<int> & B, int ncol );

        /**
         * Check the input to the bose algorithm
		 * (ncol <= q + 1) where q = p^n
         * @param q the number of symbols
         * @param ncol the number of columns
         * @return an indicator of success
         */
		int bosecheck(int q, int ncol );
        
        /**
         * Integer to polynomial
         * @param n the input integer
         * @param q the order of the Galois field
         * @param d the degree of the polynomial.  A degree 3 polynomial will have 4 coefficients (x^0, x^1, x^2, x^3)
         * @param coef vector of polynomial coefficients
         * @return an indicator of success
         */
		int itopoly(int n, int q, int d, std::vector<int> & coef );
        
        /**
         * Evaluate a polynomial with coefficients, argument and result in a Galois field
         * @param gf a Galois field
         * @param d the polynomial degree.  A degree 3 polynomial will have 4 coefficients (x^0, x^1, x^2, x^3)
         * @param poly the polynomial coefficients
         * @param arg the value of the polynomial independent variable
         * @param value the result
         * @return an indicator of success
         */
		int polyeval(GaloisField & gf, int d, std::vector<int> & poly, int arg, int* value );
        
        /**
         * Test the inputs to the Bush algorithm 
		 * (<code>ncol <= q + 1, str <= ncol, str < q + 1</code>)
         * @param q the order of the Galois Field
         * @param str the orthogonal array strength
         * @param ncol the number of columns in the orthogonal array
         * @return an indicator of success
         */
		int bushcheck(int q, int str, int ncol);
        
        /**
         * Test the inputs to the Bose-Bush algorithm
		 * (<code>p == 2, ncol <= 2q + 1</code>)
         * @param q the order of the Galois Field
         * @param p the prime basis of the Galois Field (<code>q = p^n</code>)
         * @param ncol the number of columns in the orthogonal array
         * @return an indicator of success
         */
		int bosebushcheck(int q, int p, int ncol);
        
        /**
         * Test the inputs to the Bose-Bush algorithm with lambda parameter
		 * (<code>ncol <= lambda*q + 1</code>)
         * @param s <code>s = q / lambda</code>
         * @param p the prime basis of the Galois Field
         * @param lam the lambda parameter
         * @param ncol the number of columns in the orthogonal array
         * @return an indicator of success
         */
		int bosebushlcheck(int s, int p, int lam, int ncol);
        
        /**
         * Test the inputs to the Addel-Kemp algorithm
         * @param q the order of Galois field
         * @param p the prime basis of the Galois field
         * @param ncol the number of columns in the orthogonal array
         * @return an indicator of success
         */
		int addelkempcheck(int q, int p, int ncol);
	}
}// end namespace

#endif
