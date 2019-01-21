/**
 * @file oa.h
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

#ifndef OA_H
#define OA_H

#include "OACommonDefines.h"
#include "primes.h"
#include "matrix.h"

/**
 *   If more than BIGWORK comparisons are required in
 * an oacheck routine, then a warning is printed that
 * a large job is underway.  If more than MEDWORK comparisons
 * are required then intermediate results are printed.
 * No strength checking beyond strength MAXSTR is done.
 * Only change it if you implement the higher strength
 * checks!
 */
#define BIGWORK 100000000
/**
 * One tenth of the comparisons of BIGWORK
 */
#define MEDWORK BIGWORK/10

namespace oacpp {
    /**
     * Algorithms to check the strength of an orthogonal array
     */
	namespace oastrength
    {
        /**
         * warn about large work loads in strength checking programs
         * 
         * @param work
         * @param str
         */
		void OA_strworkcheck(double work, int str);
        
        /**
         * Calculate and return the strength of the array A.
         * 
         * Verbose:
         * - verbose = 0   =>   No printed output
         * - verbose = 1   =>   Only stderr output
         * - verbose = 2   =>   Output to both stdout and stderr
         * 
         * @param q
         * @param A
         * @param str
         * @param verbose
         */
		void OA_strength(int q, bclib::matrix<int> & A, int* str, int verbose);
        
        /**
         * Check strength 0
         * @param q
         * @param A
         * @param verbose
         * @return 
         */
		int OA_str0(int q, bclib::matrix<int> & A, int verbose);
        
        /**
         * Check strength 1
         * @param q
         * @param A
         * @param verbose
         * @return 
         */
		int OA_str1(int q, bclib::matrix<int> & A, int verbose);
        
        /**
         * Check strength 2
         * @param q
         * @param A
         * @param verbose
         * @return 
         */
		int OA_str2(int q, bclib::matrix<int> & A, int verbose);
        
        /**
         * Check strength 3
         * @param q
         * @param A
         * @param verbose
         * @return 
         */
		int OA_str3(int q, bclib::matrix<int> & A, int verbose);
        
        /**
         * Check strength 4
         * @param q
         * @param A
         * @param verbose
         * @return 
         */
		int OA_str4(int q, bclib::matrix<int> & A, int verbose);
        
        /**
         * Check an arbitrary strength
         * @param q
         * @param A
         * @param t
         * @param verbose
         * @return 
         */
		int OA_strt(int q, bclib::matrix<int> & A, int t, int verbose);
	}
}// end namespace

#endif
