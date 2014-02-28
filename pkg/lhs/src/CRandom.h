/**
 * @file CRandom.h
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
    /**
     * Pseudorandom number abstract class
     * @tparam the type that the random number generator will generate
     */
    template <class T>
    class CRandom
    {
    public:
        /**
         * get the next random value from
         * @return the random value
         */
        virtual T getNextRandom() = 0;
    };
    
    /**
     * random numbers from a standard uniform distribution
     */
    class CRandomStandardUniform : public CRandom<double>
    {
    public:
        /**
         * default constructor
         */
        CRandomStandardUniform(){m_i1 = 1234; m_i2 = 5678;};
        /**
         * get the next random number from the stream
         * @return random deviate
         */
        double getNextRandom();
        /**
         * set the random seed
         * @param i1 seed1
         * @param i2 seed2
         */
        void setSeed(unsigned int i1, unsigned int i2);
        /**
         * get the random seeds
         * @param i1 pointer to seed1
         * @param i2 pointer to seed2
         */
        void getSeed(unsigned int *i1, unsigned int *i2);
    private:
        unsigned int m_i1;
        unsigned int m_i2;
    };
}

#endif	/* CRANDOM_H */

