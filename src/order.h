/**
 * @file order.h
 * @author Robert Carnell
 * @copyright Copyright (c) 2013, Robert Carnell
 * 
 * @license <a href="http://www.gnu.org/licenses/gpl.html">GNU General Public License (GPL v3)</a>
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
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
     * @param v the vector to be ordered
     * @param order the order of the elements
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
                vi != v.end() && pi != p.end(); ++vi, ++pi)
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
                oi != order.end() && pi != p.end(); ++oi, ++pi)
        {
            *oi = pi->second;
            //order[i] = p[i].second;
        }
    }
    
    /**
     * Find the order of each vector element (one based)
     * @tparam T numeric argument that can be ordered
     * @param v the vector to be ranked
     * @param order the order of the elements
     */
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

