/*
	Filename: fir.h
		Header file
		FIR lab wirtten for 237C class at UCSD.

*/
#ifndef FIR_H_
#define FIR_H_

#include <ap_fixed.h>

const int N = 32;

typedef int	  coef_t;
//typedef float data_t_fir;
typedef float data_t;
typedef float acc_t;

void firI1(data_t *y, data_t x);
void firI2(data_t *y, data_t x);
void firQ1(data_t *y, data_t x);
void firQ2(data_t *y, data_t x);

void fir (  data_t I,  data_t Q,  data_t *X,  data_t *Y  );



#endif
