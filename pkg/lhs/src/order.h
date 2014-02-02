/* 
 * File:   order.h
 * Author: carnellr
 *
 * Created on November 26, 2013, 2:59 PM
 */

#ifndef ORDER_H
#define	ORDER_H

#include <vector>
#include <algorithm>

namespace bclib
{
    /**
     * Comparison operator to use in the findranks method
     * @param first the first pair of arguments (value, rank)
     * @param second the second pair of arguments (value, rank)
     * @return true if the value in the first argument is less than the value in the second argument
     */
    template <class T>
    bool findranksCompare(const std::pair<T, int> first, const std::pair<T, int> second)
    {
        return (first.first < second.first);
    }

    /**
     * Find the order of each vector element (zero based)
     * @tparam T numeric argument that can be ordered
     * @param v the vector to be ranked
     * @param indx the ranks of the elements
     */
    template <class T>
    void findorder_zero(const std::vector<T> & v, std::vector<int> & order)
    {
        // create a vector of pairs to hold the value and the integer rank
        std::vector<std::pair<T, int> > p(v.size());
        
        typename std::vector<T>::const_iterator vi;
        typename std::vector<std::pair<T, int> >::iterator pi;
        int position = 0;
        for (vi = v.begin(), pi = p.begin();
                vi != v.end(), pi != p.end(); ++vi, ++pi)
        {
            *pi = std::pair<T, int>(*vi, position);
            position++;
        }

        // if the rank vector is not the right size, resize it (the original values may be lost)
        if (order.size() != v.size())
        {
            order.resize(v.size());
        }

        // sort the pairs of values
        std::sort(p.begin(), p.end(), findranksCompare<double>);

        // take the ranks from the pairs and put them in the rank vector
        std::vector<int>::iterator oi;
        for (oi = order.begin(), pi = p.begin(); 
                oi != order.end(), pi != p.end(); ++oi, ++pi)
        {
            *oi = pi->second;
            //order[i] = p[i].second;
        }
    }
    
    template <class T>
    void findorder(const std::vector<T> & v, std::vector<int> & order)
    {
        findorder_zero<T>(v, order);
        for (std::vector<int>::size_type i = 0; i < order.size(); i++)
        {
            order[i] += 1;
        }
    }
} // end namespace

#endif	/* ORDER_H */

