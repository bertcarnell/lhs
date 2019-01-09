/**
 * @file RStandardUniform.h
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

#ifndef RSTANDARDUNIFORM_H
#define	RSTANDARDUNIFORM_H

#include <Rcpp.h>
#include "CRandom.h"

namespace lhs_r
{
    /**
     * Standard Uniform random number generator using R
     */
    class RStandardUniform : public bclib::CRandom<double>
    {
    public:
        /**
         * get the next random number
         * @return the random deviate
         */
        double getNextRandom() 
        {
            return Rcpp::as<double>(Rcpp::runif(1));
        };
    };
}

#endif	/* RSTANDARDUNIFORM_H */

