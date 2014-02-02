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
