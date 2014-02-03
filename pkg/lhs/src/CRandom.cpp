/**
 * @file CRandom.cpp
 * @author Robert Carnell
 * @copyright Copyright (c) 2014, Robert Carnell
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
 */

#include "CRandom.h"

namespace lhslib
{
    double CRandomStandardUniform::getNextRandom()
    {
        m_i1 = 36969*(m_i1 & 0177777) + (m_i1>>16);
        m_i2= 18000*(m_i2 & 0177777) + (m_i2>>16);
        return ((m_i1 << 16)^(m_i2 & 0177777)) * 2.328306437080797e-10; /* in [0,1) */
    }
    
    void CRandomStandardUniform::setSeed(unsigned int i1, unsigned int i2)
    {
        m_i1 = i1; m_i2 = i2;
    }
    
    void CRandomStandardUniform::getSeed(unsigned int* i1, unsigned int* i2)
    {
        *i1 = m_i1; *i2 = m_i2;
    }
} //  end namespace
