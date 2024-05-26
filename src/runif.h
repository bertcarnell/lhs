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

#include "OACommonDefines.h"
/**
 * Macro to define a seed is within range
 */
#define SEEDOK 1
/**
 * Macro to define a seed is not within range
 */
#define SEEDBAD 0
/**
 * Macro to set the length of the seed vector (97 + 1 since max location is 97 (ip))
 */
#define SEED_VECTOR_LENGTH 98

namespace oacpp
{
	/**
	*  A set of seed variables for the random number generator
	*/
    struct SeedSet
    {
        /** Default Constructor */
        SeedSet() {};
        /** Constructor */
        SeedSet(int one, int two, int three, int four) { is = one; js = two; ks = three; ls = four; };
		/** seed i */
        int is;
		/** seed j */
		int js;
		/** seed k */
		int ks;
		/** seed l */
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
		/** Constructor */
        RUnif();
		/** Constructor with individual seeds */
        RUnif(int is, int js, int ks, int ls);

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
         * Set the seeds to equal the numbers in the seedSet
         * @param seedSet a set of four seeds
         */
        void seed(SeedSet & seedSet);

		/**
		 * Get the seed set
		 * @return the SeedSet struct containing the seeds
		 */
        SeedSet getSeedSet();

        /**
         * random uniform number generator
         * @param x a double vector to contain the random numbers
         * @param n the length of the vector
         */
		void runif(std::vector<double> & x, int n);

		/**
		 * a mod b
		 * @param a base
		 * @param b modulus
		 * @return an integer result
		 */
		static int mod(int a, int b);

	private:
        /**
         * is the seed ok?
         * @param is seed
         * @param js seed
         * @param ks seed
         * @param ls seed
         * @return 1 if seeds ok, 0 otherwise
         */
		static int seedok(int is, int js, int ks, int ls );

        /**
         * sets z[0] through z[n-1] to the next n random uniforms between 0 and 1
         * @param x double vector
         * @param n length of the vector
         */
		void ranums(std::vector<double> & x, int n);

		int m_jent, m_i, m_j, m_k, m_l, ip, jp;
        std::array<double, SEED_VECTOR_LENGTH> u;
		double c, cd, cm;
	};
}

#endif
