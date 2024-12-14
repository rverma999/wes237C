#ifndef CORDICCART2POL_H
#define CORDICCART2POL_H

#include <iostream>
#include <cmath>
#include "ap_fixed.h"

#define NO_ITER 16

typedef int   coef_t;
//typedef float data_t;
//typedef ap_fixed<20,3> data_t;
typedef float data_t;
typedef float acc_t;

void cordiccart2pol(data_t x, data_t y, data_t * r,  data_t * theta);
//void cordiccart2pol(ap_fixed<16,2> x, ap_fixed<16,2> y, ap_fixed<16,2> * r,  ap_fixed<20,3> * theta);

#endif
