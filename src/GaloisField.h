/**
 * @file GaloisField.h
 * @author Robert Carnell
 * @copyright Copyright (c) 2020, Robert Carnell
 *
 * This class is based on the code by Art Owen in galdef.h, galois.h, xtnset.h, xtndispatch.h, xtndeclare.h
 *
 * Reference:
 * <ul><li><a href="http://lib.stat.cmu.edu/designs/">Statlib Designs</a></li>
 * <li><a href="http://lib.stat.cmu.edu/designs/oa.c">Owen's Orthogonal Array Algorithms</a></li></ul>
 *
 */

#ifndef GALOISFIELD_H
#define GALOISFIELD_H

#include "OACommonDefines.h"
#include "matrix.h"
#include "primes.h"
#include <assert.h>

namespace oacpp {
    /**
     * Class to define a Galois Field and Methods for operations
     */
    class GaloisField
    {
    private:
        void fillAllPolynomials();
        void computeSumsAndProducts();
        void computeMultiplicativeInverse();
        void computeNegative();
        void computeRoots();
        static std::vector<int> initializePowerCycle(int q);

    public:
        /** prime modulus exponent q = p^n*/
        int n;
        /** polynomial vector length */
        size_t u_n;
        /** prime modulus q=p^n*/
        int p;
        /** the order of the field q = p^n */
        int q;
        /** field element vector lenth */
        size_t u_q;
        /** characteristic polynomial of length u_n */
        std::vector<int> xton;
        /** Indicator of which row of poly is the multiplicative inverse of this row of length u_q */
        std::vector<int> inv;
        /** row number of which row of poly is the negative (additive inverse) of this row of length u_q */
        std::vector<int> neg;
        /** root */
        std::vector<int> root;
        /** sum field of dimension u_q x u_q*/
        bclib::matrix<int> plus;
        /** product field of dimension u_q x u_q*/
        bclib::matrix<int> times;
        /** polynomial field of dimension u_q x u_n */
        bclib::matrix<int> poly;

        /**
         * Construct the Galois Field with order q
         */
        explicit GaloisField(int q);

        /**
         * Default Constructor
         */
        GaloisField();

        /**
         * Multiplication in polynomial representation
         *
         * @param p modulus
         * @param u_n length of p1 and p2
         * @param xton characteristic polynomial
         * @param p1 polynomial 1
         * @param p2 polynomial 2
         * @param prod the product of the polynomials
         */
        static void polyProd(int p, size_t u_n, const std::vector<int> & xton, const std::vector<int> & p1, const std::vector<int> & p2, std::vector<int> & prod);

        /**
         * Addition in polynomial representation
         *
         * @param p modulus
         * @param u_n the length of p1 and p2
         * @param p1 polynomial 1
         * @param p2 polynomial 2
         * @param sum the sum of the polynomials
         */
        static void polySum(int p, size_t u_n, const std::vector<int> & p1, const std::vector<int> & p2, std::vector<int> & sum);
        /**
         * Convert polynomial to integer in <code>0..q-1</code>
         *
         * @param p polynomial multiplier
         * @param n the length of poly
         * @param poly the polynomial
         * @return an integer
         */
        static int poly2int(int p, int n, const std::vector<int> & poly);

        /**
         * Print a Galois field
         */
        void print();
    };
} // end namespace

#endif
