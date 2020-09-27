/**
 * @file oaLHSUtility.cpp
 * @author Robert Carnell
 * @copyright Copyright (c) 2019, Robert Carnell
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
 */

#ifndef OALHSUTILITY_H
#define	OALHSUTILITY_H

#include <vector>

namespace oalhslib
{
    /*template <class T>
    void findUnique(typename std::iterator<std::forward_iterator_tag, T> & begin, 
            typename std::iterator<std::forward_iterator_tag, T> & end, 
            typename std::vector<T> & output)
    {
        for (std::iterator<std::forward_iterator_tag, T> it = begin; it != end; ++it)
        {
            typename std::vector<T>::iterator tempit = std::find(output.begin(), output.end(), *it);
            if (tempit ==  output.end())
            {
                output.push_back(*it);
            }
        }
    }*/

    template <class T>
    void findUniqueColumnElements(const bclib::matrix<T> & A, std::vector<std::vector<T> > & U)
    {
        if (U.size() != A.colsize())
        {
            U = std::vector<std::vector<T> >(A.colsize());
        }
        for (typename bclib::matrix<T>::size_type i = 0; i < A.colsize(); i++)
        {
            U[i] = std::vector<T>();
            for (typename bclib::matrix<T>::const_columnwise_iterator it = A.columnwisebegin(i); it != A.columnwiseend(i); ++it)
            {
                typename std::vector<T>::iterator tempit = std::find(U[i].begin(), U[i].end(), *it);
                if (tempit ==  U[i].end())
                {
                    U[i].push_back(*it);
                }
            }
        }
    }
    
}

#endif	/* OALHSUTILITY_H */

