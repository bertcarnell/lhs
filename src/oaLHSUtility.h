/* 
 * File:   oaLHSUtility.h
 * Author: carnellr
 *
 * Created on March 4, 2014, 10:31 PM
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

