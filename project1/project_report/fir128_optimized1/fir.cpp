/*
	Filename: fir.cpp
		FIR lab wirtten for WES/CSE237C class at UCSD.
		Match filter
	INPUT:
		x: signal (chirp)

	OUTPUT:
		y: filtered output

*/

#include "fir.h"

void fir (
  data_t *y,
  data_t x
  )
{

	//range -11 to 11
	ap_int<5> c[N] = {10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 11, 11, 8, 3, -3, -8, -11, -11, -10, -10, -10, -10, -10, -10, -10, -10, -11, -11, -8, -3, 3, 8, 11, 11, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10};
	
	// Write your code here
	 static ap_int<8> shift_reg[N];
	 //acc_t acc;
	 ap_int<16> acc;
	 //int i;
	 acc = 0;
	 //Shift_Accum_Loop:
//#pragma HLS ARRAY_PARTITION variable=c complete
//#pragma HLS ARRAY_PARTITION variable=shift_reg complete
//#pragma HLS PIPELINE II=1
//#pragma HLS INLINE off
//#pragma HLS LATENCY min=1 max=1


	    ap_int<8> i;
	    acc = 0;
	    //Shift_Accum_Loop:
	    for(i =N - 1; i >= 0; i--) {
	    //for(i=10; i >= 0; i−−){
	      if (i == 0) {
	        acc += x*c[0];
	        shift_reg[0] = x;
	      } else {
	      shift_reg[i] = shift_reg[i - 1];
	      acc += shift_reg[i] * c[i];
	      }
	    }
	    *y = acc;


	 /*
	    acc = x * c[0];

	SHIFT_MAC: for(int i = N-1; i > 0; i--) {
	    #pragma HLS UNROLL
	    shift_reg[i] = shift_reg[i-1];
	    acc += shift_reg[i] * c[i];
	}
	shift_reg[0] = x;
	*y=acc;
	*y=acc;
	*y=acc;*/
}


