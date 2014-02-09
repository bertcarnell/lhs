/**
 * @file runif.h
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

#ifndef RUNIF_H
#define RUNIF_H

#include "CommonDefines.h"
#define SEEDOK 1
#define SEEDBAD 0

namespace oacpp 
{
    struct SeedSet
    {
        int is;
        int js;
        int ks;
        int ls;
    };

    /**
     * Marsaglia - Zaman universal random number generator.
     * 
     * reinitialization: call seed(is,js,ks,ls), with integer arguments
     * from 1 to 168, not all 1.  
     * generate n uniform random numbers and store in x(n): call ranums(x,n).
     * 
     * Transliterated from FORTRAN to C by Art Owen, 4 March 1993.
     */
	class RUnif
	{
	public:
        RUnif() {};
        RUnif(int is, int js, int ks, int ls);
        RUnif(SeedSet seedSet);
        
        ~RUnif() {};
        
        /**
         * sets seed integers, rejects invalid input
         * @param is seed
         * @param js seed
         * @param ks seed
         * @param ls seed
         */
		void seed(int is, int js, int ks, int ls );
        
        /**
         * 
         * @param seedset
         */
        void seed(SeedSet seedSet);
        
        SeedSet getSeedSet();

        /**
         * 
         * @param x
         * @param n
         */
		void runif(std::vector<double> & x, int n);

	private:
        /**
         * a mod b
         * @param a
         * @param b
         * @return 
         */
		static int mod( int a, int b );
        
        /**
         * 1 if seeds ok, 0 otherwise
         * @param is seed
         * @param js seed
         * @param ks seed
         * @param ls seed
         * @return 1 if seeds ok, 0 otherwise
         */
		static int seedok(int is, int js, int ks, int ls );
        
        /**
         * sets z[0] through z[n-1] to the next n random uniforms between 0 and 1
         * @param x
         * @param n
         */
		void ranums(std::vector<double> & x, int n);

		int m_jent, m_i, m_j, m_k, m_l, ip, jp;
		double u[97+1];
		double c, cd, cm;
	};
}

#endif
