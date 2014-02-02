/* 
 * File:   CRandom.h
 * Author: carnellr
 *
 * Created on November 22, 2013, 6:38 PM
 */

/*** from sunif.c ****/
/*
 *  Mathlib : A C Library of Special Functions
 *  Copyright (C) 2000, 2003  The R Core Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, a copy is available at
 *  http://www.r-project.org/Licenses/
 *
 */

#ifndef CRANDOM_H
#define	CRANDOM_H

namespace lhslib
{
    template <class T>
    class CRandom
    {
    public:
        virtual T getNextRandom() = 0;
    };
    
    class CRandomStandardUniform : public CRandom<double>
    {
    public:
        CRandomStandardUniform(){m_i1 = 1234; m_i2 = 5678;};
        double getNextRandom();
        void setSeed(unsigned int i1, unsigned int i2);
        void getSeed(unsigned int *i1, unsigned int *i2);
    private:
        unsigned int m_i1;
        unsigned int m_i2;
    };
}

#endif	/* CRANDOM_H */

