/* 
 * File:   RStandardUniform.h
 * Author: carnellr
 *
 * Created on November 28, 2013, 10:01 PM
 */

#ifndef RSTANDARDUNIFORM_H
#define	RSTANDARDUNIFORM_H

#include <Rcpp.h>
#include "CRandom.h"

class RStandardUniform : public lhslib::CRandom<double>
{
public:
    double getNextRandom() 
    {
        return Rcpp::as<double>(Rcpp::runif(1));
    };
};

#endif	/* RSTANDARDUNIFORM_H */

