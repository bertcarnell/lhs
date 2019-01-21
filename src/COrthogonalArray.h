/**
 * @file COrthogonalArray.h
 * @author Robert Carnell
 * @copyright Copyright (c) 2013, Robert Carnell
 * 
 * @license <a href="http://www.gnu.org/licenses/lgpl.html">GNU Lesser General Public License (LGPL v3)</a>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * Reference:
 * <ul><li><a href="http://lib.stat.cmu.edu/designs/">Statlib Designs</a></li>
 * <li><a href="http://lib.stat.cmu.edu/designs/oa.c">Owen's Orthogonal Array Algorithms</a></li></ul>
 */

#ifndef CORTHOGONALARRAY_H
#define CORTHOGONALARRAY_H

#include "OACommonDefines.h"
#include "galdef.h"
#include "galois.h"
#include "construct.h"
#include "runif.h"
#include "rutils.h"
#include "oa.h"
#include "primes.h"

/** The number of rows of the oa to check and print */
#define ROWCHECK 50
/** no debug messages */
#define NOMESSAGES 0
/** some debug messages */
#define SOMEMESSAGES 1
/** all debug messages should be shown */
#define ALLMESSAGES 2

/**
 * Orthogonal Array Namespace
 */
namespace oacpp {
    /**
     * Orthogonal Array Class
     * 
     * A collection of functions used as an API for Art Owen's oa library.
     */
	class COrthogonalArray
	{
	public:
        /**
         * Default Constructor
         */
		COrthogonalArray();
        /**
         * Default Destructor
         */
		~COrthogonalArray(){}; 
		
        /**
         * Construct an orthogonal array using the Addelman Kempthorne algorithm
         * 
         * From the original documentation:
         * <blockquote>
         * The addelkemp program produces <code>OA( 2q^2, k, q, 2 ),  k <= 2q+1</code>,
         * for odd prime powers <code>q</code>.  Even prime powers may be produced using
         * bosebush above.  This construction is based on:
         * 
         * <b>S. Addelman and O. Kempthorne (1961) Annals of Mathematical Statistics,
         * Vol 32 pp 1167-1176.</b>
         * 
         * using <code>n=2</code> in their notation.
         * 
         * <code>2q</code> columns can be
         * constructed without a coincidence defect.  Setting <code>k=2q+1</code>
         * leads to an array with the coincidence defect.  Some
         * triples of columns contain duplicate rows.  (The lack of
         * a coincidence defect has been verified for 
         * <code>q = 2,3,4,5,7,9,11,13,17,19,23,25</code> and <code>k = 2q</code>.)
         * 
         * This construction should work for all prime powers
         * <code>q</code>, but it failed to do so for even powers greater
         * than 4.  This may have been a programming error, or
         * it may have stemmed from misunderstanding of the description
         * of the algorithm.  The program rejects requests with
         * <code>q = 2^r</code> for <code>r > 2</code>.  The Bose Bush construction handles these
         * cases.
         * 
         * The description of the construction for odd prime powers
         * calls for some arithmetic involving the number 4.  In
         * Galois fields with <code>3^r</code> elements, there is no 4.  Replacing 4
         * by 1 for these fields works when <code>q = 3,9,27</code> (brute force
         * verification).
         * </blockquote>
         * 
         * @param q the number of symbols <code>(0,...,q-1)</code>
         * @param k the number of columns in the array.  <code>k <= q+1</code>
         * @param [out] n the number of rows in the array, <code>n = 2q^2</code>
         * @throws std::runtime_error
         */
		void addelkemp(int q, int k, int* n);
        
        /**
         * Construct an orthogonal array using the Addelman Kempthorne algorithm
         * 
         * From the original documentation:
         * <blockquote>
         * The addelkemp3 program produces <code>OA( 2*q^3, k, q, 2 ),
         * k <= 2q^2+2q+1</code>, for prime powers <code>q</code>.  <code>q</code> 
         * may be an odd prime power, or <code>q</code> may be 2 or 4.
         * 
         * This construction is based on:
         *
         * <b>S. Addelman and O. Kempthorne (1961) Annals of Mathematical Statistics,
         * Vol 32 pp 1167-1176.</b>
         *
         * using <code>n=3</code> in their notation.
         *
         * Coincidences are much harder to understand with these designs.
         * For example <code>addelkemp3 3 9</code> does lead to a number of triple
         * coincidences, that is pairs of rows in which 3 columns agree,
         * but no quadruple coincidences.  <code>addelkemp3 9 28</code> produces
         * an extra column that figures in some quadruple coincidences.
         * 
         * As for addelkemp above, 4 is replaced by 1 in fields that
         * do not have an element 4.  Also powers of 2 larger than 4
         * are not allowed, as described above for addelkemp.
         * 
         * The article is quite vague on this.  Page 1173 states
         * "When n>2 the same procedure will yield the desired plans
         * if Lemma 5a is used in place of Lemma 5."  Page 1175
         * provides the example n=3,q=3 which is OA( 54,25,3,2 ).
         * Based on this example it is possible to make an educated
         * guess as to how the construction generalizes to n=3.
         * The resulting OA's are seen, by brute force to be of
         * strength 2 for q=2,3,4,5,7,11.  These OAs are:
         * - OA(   16,  13,  2, 2 )   
         * - OA(   54,  25,  3, 2 )
         * - OA(  128,  41,  4, 2 )   
         * - OA(  250,  61,  5, 2 )
         * - OA(  686, 113,  7, 2 )
         * - OA( 1458, 181,  9, 2 )
         * - OA( 2662, 265, 11, 2 )
         * 
         * The one with q=7 required 212709392 comparisons to determine
         * that it really is of strength 2.  This took roughly 11.5 minutes
         * on a DEC 5000/240 workstation (real and elapsed in this case).
         * The array with q=11 took 1.12671e+10 comparisons to verify its strength.
         * This took roughly 10 1/2 hours.  
         * 
         * For even q, only q= 2 or 4 are available.  The prescription
         * given in Addelman and Kempthorne (1961) does not appear to work.
         * Commented out code below attempts to implement that prescription.
         * It seemed to be impossible to find a constant b[1],c[1] pair.
         * </blockquote>
         * 
         * @param q the number of symbols <code>(0,...,q-1)</code>
         * @param k the number of columns in the array.  <code>k <= 2q^2+2q+1</code>
         * @param [out] n the number of rows in the array, <code>n = 2q^3</code>
         * @throws std::runtime_error
         */
		void addelkemp3(int q, int k, int* n);
        
        /**
         * Construct an orthogonal array using the Addelman Kempthorne algorithm
         * 
         * @deprecated This method is not included by default in Art Owens's
         * project.  The method is in the code, but it is not compiled in
         * the makefile.  Adding it as a target to the makefile creates a successful build,
         * but running addelkempn 3 3 (which should be equivalent to addelkemp3 3)
         * does not function in the MinGW64 build.
         * 
         * From the original documentation:
         * <blockquote>
         * The article is quite vague on this.  Page 1173 states
         * "When n>2 the same procedure will yield the desired plans
         * if Lemma 5a is used in place of Lemma 5."  Page 1175
         * provides the example n=3,q=3 which is OA( 54,25,3,2 ).
         * Based on this example it is possible to make an educated
         * guess as to how the construction generalizes.
         * 
         * @param akn the exponent on <code>q</code> for the number of rows <code>n = 2q^akn</code>
         * @param q the number of symbols <code>(0,...,q-1)</code>
         * @param k the number of columns in the array.  <code>k <= 2(q^akn-1)/(q-1) - 1</code>
         * @param [out] n the number of rows in the array, <code>n = 2q^akn</code>
         * @throws std::runtime_error
         */
		void addelkempn(int akn, int q, int k, int* n);
        
        /**
         * Construct an orthogonal array using the Bose algorithm
         * 
         * From the original documentation:
         * <blockquote>
         * The bose program produces <code>OA( q^2, k, q, 2 ),  k <= q+1 </code>
         * for prime powers <code>q</code>.  This is based on:
         * 
         * <b>R.C. Bose (1938) Sankhya Vol 3 pp 323-338</b>
         * </blockquote>
         * 
         * @param q the number of symbols <code>(0,...,q-1)</code>
         * @param k the number of columns in the array.  <code>k <= q+1</code>
         * @param [out] n the number of rows in the array, <code>n = q^2</code>
         * @throws std::runtime_error
         */
		void bose(int q, int k, int* n);
        
        /**
         * Construct an orthogonal array using the Bose-Bush algorithm
         * 
         * From the original documentation:
         * <blockquote>
         * The bosebush program produces <code>OA( 2q^2, k, q, 2 ),  k <= 2q+1</code>,
         * for powers of 2, <code>q = 2^r</code>.  This construction is based on:
         * 
         * <b>R.C. Bose and K.A. Bush (1952) Annals of Mathematical Statistics,
         * Vol 23 pp 508-524.</b>
         * 
         * <code>2q</code> columns can be constructed without a coincidence defect.  Setting 
         * <code>k = 2q+1</code> leads to an array with the coincidence defect.  Some
         * triples of columns contain duplicate rows.  (The lack of
         * a coincidence defect has been verified for <code>q = 2,4,8,16,32</code>
         * and <code>k = 2q</code>.)
         * </blockquote>
         * 
         * @param q the number of symbols <code>(0,...,q-1)</code>
         * @param k the number of columns in the array.  <code>k <= q+1</code>
         * @param [out] n the number of rows in the array, <code>n = q^2</code>
         * @throws std::runtime_error
         */
		void bosebush(int q, int k, int *n);

        /**
         * Construct an orthogonal array using the Bose-Bush algorithm
         * 
         * From the original documentation:
         * <blockquote>
         * The bosebushl program produces <code>OA( lambda*q^2, k, q, 2 ),  
         * k <= lambda*q+1</code>, for prime powers <code>q</code> and <code>lambda > 1</code>.  Both <code>q</code> and 
         * <code>lambda</code> must be powers of the same prime.  This construction is based on:
         * 
         * <b>R.C. Bose and K.A. Bush (1952) Annals of Mathematical Statistics, Vol 23 pp 508-524.</b>
         * 
         * Coincidences are harder to understand with these designs.
         * For example <code>bosebushl 3 9</code> does lead to a number of triple
         * coincidences, that is pairs of rows in which 3 columns agree,
         * but no quadruple coincidences.  <code>bosebush 3 9 28</code> produces
         * an extra column that figures in some quadruple coincidences.
         * 
         * The arrays produced by this program are not always the
         * largest possible.  The article by Bose and Bush cited
         * above describes ways of adjoining some extra columns.
         * 
         * When <code>k <= lambda*q</code>, the program produces an array that
         * is "completely resolvable".  What this means is that 
         * the rows of the array may be split into lambda*q consecutive
         * nonoverlapping sets of rows each of which is <code>OA( q,k,q,1 )</code>.
         * </blockquote>
         *  
         * @param lambda
         * @param q
         * @param k
         * @param n
         * @throws std::runtime_error
         */
		void bosebushl(int lambda, int q, int k, int* n);

        /**
         * Construct an orthogonal array using the Bush algorithm
         * 
         * From the original documentation:
         * <blockquote>
         * The bush program produces <code>OA( q^3, k, q, 3 ),  k <= q+1</code>
         * for prime powers <code>q</code>.  This strength 3 construction is based on:
         * 
         * <b>K.A. Bush (1952) Annals of Mathematical Statistics, Vol 23 pp 426-434</b>
         * 
         * This construction is the most commonly used special case
         * of busht given below.
         * </blockquote>
         * 
         * @param q the number of symbols <code>(0,...,q-1)</code>
         * @param k the number of columns in the array.  <code>k <= q+1</code>
         * @param [out] n the number of rows in the array, <code>n = q^3</code>
         * @throws std::runtime_error
         */
		void bush(int q, int k, int* n);

        /**
         * Construct an orthogonal array using the Bush algorithm
         * 
         * From the original documentation:
         * <blockquote>
         * The bush program produces <code>OA( q^t, k, q, t ),  k <= q+1, t>=3</code>,
         * for prime powers <code>q</code>.  This strength <code>t</code> construction is based on:
         * 
         * <b>K.A. Bush (1952) Annals of Mathematical Statistics, Vol 23 pp 426-434</b>
         * </blockquote>
         * 
         * @param str
         * @param q
         * @param k
         * @param n
         * @throws std::runtime_error
         */
		void busht(int str, int q, int k, int* n);

        /**
         * Count the number of columns for which each pair of rows agree
         * 
         * From the original documentation:
         * <blockquote>
         * This program counts the number of columns in which
         * each pair of distinct rows agree.
         * 
         * Input is described above under OA input conventions.
         * </blockquote>
         * 
         * Examples:
         * <blockquote>
         * <code>COrthogonalArray coa; int n;
         * coa.addelkemp3(3, 25, &n);
         * coa.oagree(true);</code>
         * </blockquote>
         * 
         * This example finds that in OA( 54, 25, 3, 2 )
         * produced by addelkemp3 there exist pairs of rows
         * agreeing in 9 columns.  The first rows to attain
         * this are rows 0 and 9, the 1st and 10th rows.
         * 
         * <blockquote>
         * <code>COrthogonalArray coa; int n;
         * coa.addelkemp3(3, 24, &n);
         * coa.agree(true);</code>
         * </blockquote>
         * 
         * The second example finds that in OA( 54, 24, 3, 2 )
         * produced by addelkemp3 there exist pairs of rows
         * agreeing in 8 columns.   No pairs of rows agree in
         * 9 columns.
         * 
         * @param verbose Should messages be printed about the findings?
         * @return the maximum number of agreeing columns
         */
		int oaagree(bool verbose);
        /**
         * Count the number of columns for which each three rows agree
         * 
         * From the original documentation:
         * <blockquote>
         * This program reports on triple coincidences.  For all
         * triples of distinct columns, it counts the number of
         * distinct pairs of rows in which the triple of columns
         * agree.
         * 
         * Input is described above under OA input conventions.
         * 
         * Examples:
         * 
         * <code>COrthogonalArray coa; int n;
         * coa.bosebush(8, 16, &n);
         * coa.agree(true);</code>
         * 
         * There are 0 distinct triples of columns that agree
         * in at least two distinct rows.
         * 
         * <code>COrthogonalArray coa; int n;
         * coa.bosebush(8, 17, &n);
         * coa.agree(true);</code>
         * 
         * Warning: The Bose-Bush construction with ncol = 2q+1
         * has a defect.  While it is still an OA(2q^2,2q+1,q,2),
         * there exist some pairs of rows that agree in three columns.
         * 
         * There are 8 distinct triples of columns that agree in at least two distinct rows.
         * 
         * The warning above is generated by bosebush.
         * The rest shows that there are triple coincidences.
         * Notice that they all involve the 17th column
         * (which is column 16, since the first one is column 0).
         * The other 16 columns can be organized into 8 pairs
         * with each pair forming a triple with column 16 and
         * no other triples agreeing in any row.
         * </blockquote>
         * 
         * @param verbose Should messages be printed about the findings?
         * @return the maximum number of agreeing columns
         */
		int oatriple(bool verbose);

        /**
         * Print the dimension of the orthogonal array
         */
		void oadimen();
        
        /**
         * Randomize an orthogonal array
         * 
         * From the original documentation
         * <blockquote>
         * This program permutes the symbols in each column.  The permutations are
         * uniformly distributed (all <code>q!</code> permutations have the same
         * probability) and all columns are permuted independently.
         * 
         * Input is described above under OA input conventions,
         * with exceptions noted below to allow passing a random
         * seed.  If oarand is called twice with the same input array,
         * the same permuted output will result both times, unless
         * different seeds are given.
         * 
         * The random number generator is a version of the
         * Marsaglia-Zaman random number generator, transliterated
         * into C from  FORTRAN.  The seed must be four integers
         * between 1 and 168 inclusive, with not all values equal
         * to 1.
         * </blockquote>
         * 
         * @param is seed
         * @param js seed
         * @param ks seed
         * @param ls seed
         */
		void oarand(int is, int js, int ks, int ls);

        /**
         * Find the strength of an orthogonal array
         * 
         * This program reads an orthogonal array strength by brute force computation.
         * In addition to the strength <code>t</code> described above under
         * the heading orthogonal arrays, strength 0 is taken to 
         * mean that the array indeed has all its elements in the
         * range 0..q-1.
         * 
         * An array of strength <code>t \> 0</code> is also of strength <code>s</code> for
         * all <code>0 \<= s \< t</code>.  The program starts testing <code>t = 0</code> and
         * increases <code>t</code> until it finds <code>t</code> for which the array is
         * not strength <code>t</code>.
         * 
         * Finding the strength of an array by brute force is
         * lightning fast for small arrays but very slow for larger
         * arrays.  When the job is large enough, intermediate
         * results are printed so the user can decide whether or
         * not to kill the job, based on how much progress is
         * being made.
         * 
         * The function that calculates strength has an argument
         * verbose.  In oastr the array strength function is
         * called with verbose=2.  This prints to standard output
         * a description of progress as the strength check proceeds.
         * If one wants to use this function in other settings,
         * calling it with verbose=1 shuts off standard output
         * but leaves the warnings to standard error, and verbose=0
         * shuts off all output.
         * 
         * @param verbose should diagnostic message be printed?
         * @return the strength of the array
         */
		int oastr(bool verbose);
        
        /**
         * Similar to oastr, but only checking strength 1
         * 
         * From the original documentation:
         * <blockquote>
         * Check whether the array in standard input is really
         * of strength 1.  Use brute force.  For OA( nrow, ncol, q, ? )
         * it takes work roughly proportional to 
         * ncol * nrow * q
         * to decide if ? >= 1.  The user is warned if this is likely
         * to be too much work.
         * 
         * The program calls exit(0) if the input array has strength
         * 1.  It calls exit(1) if the array is not of strength 1, or if
         * the input is invalid, or if it is impossible to allocate enough
         * memory to find out.
         * 
         * Note that an array of strength larger than 1 is a fortiori
         * of strength 1 and will pass this test.  
         * </blockquote>
         * 
         * @param verbose should diagnostic message be printed?
         * @return true if the array is strength 1
         */
		bool oastr1(bool verbose);
        
        /**
         * Similar to oastr, but only checking strength 2
         * 
         * From the original documentation
         * <blockquote>
         * Check whether the array in standard input is really
         * of strength 2.  Use brute force.  For OA( nrow, ncol, q, ? )
         * it takes work roughly proportional to 
         * ncol^2 * nrow * q^2/2
         * to decide if ? >= 2.  The user is warned if this is likely
         * to be too much work.
         * 
         * The program calls exit(0) if the input array has strength
         * 2.  It calls exit(1) if the array is not of strength 2, or if
         * the input is invalid, or if it is impossible to allocate enough
         * memory to find out.
         * 
         * The program exits at the first sign that the array is
         * not of strength 2.  This can save lots of work if the problem
         * shows up early, but it doesn't give a complete list of the
         * array's shortcomings.  Such a list could be very large.
         * 
         * Note that an array of strength larger than 2 is a fortiori
         * of strength 2 and will pass this test.
         * </blockquote>
         * 
         * @param verbose should diagnostic message be printed?
         * @return true if the array is strength 2
         */
		bool oastr2(bool verbose);
        /**
         * Similar to oastr, but only checking strength 3
         * @param verbose should diagnostic message be printed?
         * @return true if the array is strength 3
         */
		bool oastr3(bool verbose);
        /**
         * Similar to oastr, but only checking strength 4
         * @param verbose should diagnostic message be printed?
         * @return true if the array is strength 4
         */
		bool oastr4(bool verbose);

		/**
		 * Similar to oastr, but only checking for strength t
		 * @param t the strength to check for
		 * @param verbose should diagnostic messages be printed?
		 */
		bool oastrt(int t, bool verbose);

        /**
         * row accessor
         * @return the number of rows in the orthogonal array
         */
		int getnrows();
        /**
         * column accessor
         * @return the number of columns in the orthogonal array
         */
		int getncols();
        /**
         * symbol accessor
         * @return the number of symbols in the orthogonal array
         */
		int getq();
        /**
         * orthogonal array accessor
         * @return the orthogonal array
         */
        const bclib::matrix<int> & getoa();

	private:
		struct GF m_gf; /**< Galois Field */
        bclib::matrix<int> m_A; /**< Orthogonal Array */
		int m_nrow; /**< the number of rows in orthogonal array */
        int m_ncol; /**< the number of columns in the orthogonal array */
        int m_q; /**< the number of symbols in the orthogonal array */
        RUnif m_randomClass;

		/**
         * Create a Galois Field
         * @param q the number of symbols <code>(0,...,q-1)</code>
         * @throws std::runtime_error
        */
        void createGaloisField(int q);
        /**
         * check to see if the memory for the array has been allocated
         * @throws std::runtime_error
         */
		void checkDesignMemory();
        /**
         * Check that the number of columns requested is less than the maximum
         * @param k the columns requested
         * @param maxColumns the maximum columns allowed
         * @return the columns allowed
         * @throws std::runtime_error
         */
		int checkMaxColumns(int k, int maxColumns);
        /**
         * Check that the array was created successfully and assign the number of rows
         * 
         * @param result code indicating if the array was created successful
         * @param nvalue the expected number of rows in the array
         * @param n [out] the number of rows
         * @throws std::runtime_error
         */
		void checkResult(int result, int nvalue, int * n);
	};

	inline
	void COrthogonalArray::oadimen()
	{
		PRINT_OUTPUT("\nThe array has %d rows, %d columns and appears\n", m_nrow, m_ncol);
		PRINT_OUTPUT("to have %d symbols, since the largest symbol is %d.\n", m_q, m_q-1);
	}

	inline 
    int COrthogonalArray::getnrows() 
    {
        return m_nrow;
    }
	inline 
    int COrthogonalArray::getncols() 
    {
        return m_ncol;
    }
	inline 
    int COrthogonalArray::getq() 
    {
        return m_q;
    }
    inline 
    const bclib::matrix<int> & COrthogonalArray::getoa() 
    {
        return m_A;
    }
}

#endif
