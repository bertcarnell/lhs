/**
 * @file rutils.h
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

#ifndef RUTILS_H
#define RUTILS_H

#include "OACommonDefines.h"
#include "runif.h"

namespace oacpp
{
	/*
	 Namespace for utilities based on runif
	*/
	namespace rutils
	{
        /**
         * In S one just does rank(runif(q)).  Here we want
         * something like rank(runif(q))-1 since the symbols to
         * be permuted are 0..q-1
         * @param pi a vector of integers to be permuted
         * @param q length of the vector
         * @param randomClass a random number generator class
         */
		void unifperm( std::vector<int> & pi, int q, RUnif & randomClass );

        /**
         * Find the rank of each vector element (zero based)
         * 
         * @deprecated This algorithm is slow, but easier to verify
         * 
         * @tparam T numeric argument that can be ranked
         * @param v the vector to be ranked
         * @param indx the ranks of the elements
         */
        template <class T>
        void findranks_slow_zero(const std::vector<T> & v, std::vector<int> & indx)
        {
            if (indx.size() != v.size())
            {
                indx.resize(v.size());
            }
            for (size_t i = 0; i < v.size(); i++)
            {
                indx[i] = static_cast<int>(i);
            }
            std::vector<T> vsort(v);
            std::sort<typename std::vector<T>::iterator>(vsort.begin(), vsort.end());

            for (size_t i = 0; i < v.size(); i++)
            {
                indx[i] = static_cast<int>(std::find(vsort.begin(), vsort.end(), v[i]) - vsort.begin());
            }
        }

        /**
         * Find the rank of each vector element
         * 
         * @deprecated This algorithm is slow, but easier to verify
         * 
         * @tparam T numeric argument that can be ranked
         * @param v the vector to be ranked
         * @param indx the ranks of the elements
         */
        template <class T>
        void findranks_slow(const std::vector<T> & v, std::vector<int> & indx)
        {
            findranks_slow_zero(v, indx);
            for (size_t i = 0; i < indx.size(); i++)
            {
                indx[i] += 1;
            }
        }

        /**
         * Comparison operator to use in the findranks method
         * @param first the first pair of arguments (value, rank)
         * @param second the second pair of arguments (value, rank)
         * @return true if the value in the first argument is less than the value in the second argument
         */
        template <class T>
        bool findranksCompare(const std::pair<T, int> & first, const std::pair<T, int> & second)
        {
            return (first.first < second.first);
        }

        /**
         * Find the rank of each vector element (zero based)
         * @tparam T numeric argument that can be ranked
         * @param v the vector to be ranked
         * @param rank the ranks of the elements
         */
        template <class T>
        void findranks_zero(const std::vector<T> & v, std::vector<int> & rank)
        {
            // create a vector of pairs to hold the value and the integer rank
            std::vector<std::pair<T, int> > p(v.size());
            std::vector<int> temp(p.size());
            for (size_t i = 0; i < v.size(); i++)
            {
                p[i] = std::pair<T, int>(v[i], static_cast<int>(i));
            }

            // if the rank vector is not the right size, resize it (the original values may be lost)
            if (rank.size() != v.size())
            {
                rank.resize(v.size());
            }

            // sort the pairs of values
            std::sort(p.begin(), p.end(), findranksCompare<double>);

            // take the ranks from the pairs and put them in the rank vector
            for (size_t i = 0; i < v.size(); i++)
            {
                rank[p[i].second] = static_cast<int>(i);
            }
        }

        /**
         * Find the rank of each vector element
         * @tparam T numeric argument that can be ranked
         * @param v the vector to be ranked
         * @param rank the ranks of the elements
         */
        template <class T>
        void findranks(const std::vector<T> & v, std::vector<int> & rank)
        {
            findranks_zero(v, rank);
            for (size_t i = 0; i < rank.size(); i++)
            {
                rank[i] += 1;
            }
        }
    } // end namespace
} // end namespace

#endif
