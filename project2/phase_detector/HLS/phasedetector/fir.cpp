/*
	Filename: fir.cpp
		Complex FIR or Match filter
		firI1 and firI2 share coef_t c[N]
		firQ1 and firQ2 share coef_t c[N]
		
	INPUT:
		I: signal for I sample
		I: signal for Q sample

	OUTPUT:
		X: filtered output
		Y: filtered output

*/

#include "fir.h"

void firI1 (
  data_t *y,
  data_t x
  ) {

	coef_t c[N] = {1,    -1,    1,    -1,    -1,    -1,    1,    1,    -1,    -1,    -1,    1,    1,    -1,    1,    -1,    -1,    -1,    -1,    1,    1,    1,    1,    1,    -1,    -1,    1,    1,    1,    -1,    -1,    -1};

	// Write your code here
	 static ap_int<16> shift_reg[N];
	 //acc_t acc;
	 data_t acc;
	 //int i;
	 acc = 0;
	 //Shift_Accum_Loop:
         #pragma HLS ARRAY_PARTITION variable=c complete
         #pragma HLS ARRAY_PARTITION variable=shift_reg complete
         #pragma HLS PIPELINE II=1
         #pragma HLS INLINE off
         #pragma HLS LATENCY min=1 max=1
         
         acc = x * c[0];
         
         SHIFT_MAC: for(int i = N-1; i > 0; i--) {
         #pragma HLS UNROLL
         shift_reg[i] = shift_reg[i-1];
         acc += shift_reg[i] * c[i];
}
         shift_reg[0] = x;
         *y=acc;
	
}


void firI2 (
  data_t *y,
  data_t x
  ) {

	coef_t c[N] = {1,    -1,    1,    -1,    -1,    -1,    1,    1,    -1,    -1,    -1,    1,    1,    -1,    1,    -1,    -1,    -1,    -1,    1,    1,    1,    1,    1,    -1,    -1,    1,    1,    1,    -1,    -1,    -1};

	// Write your code here
	 static ap_int<16> shift_reg[N];
	 //acc_t acc;
	 data_t acc;
	 //int i;
	 acc = 0;
	 //Shift_Accum_Loop:
         #pragma HLS ARRAY_PARTITION variable=c complete
         #pragma HLS ARRAY_PARTITION variable=shift_reg complete
         #pragma HLS PIPELINE II=1
         #pragma HLS INLINE off
         #pragma HLS LATENCY min=1 max=1
         
         acc = x * c[0];
         
         SHIFT_MAC: for(int i = N-1; i > 0; i--) {
         #pragma HLS UNROLL
         shift_reg[i] = shift_reg[i-1];
         acc += shift_reg[i] * c[i];
}
         shift_reg[0] = x;
         *y=acc;
	
}




void firQ1 (
  data_t *y,
  data_t x
  ) {

	coef_t c[N] = {-1,    -1,    1,    -1,    1,    -1,    1,    -1,    -1,    -1,    -1,    1,    -1,    1,    -1,    1,    1,    -1,    1,    -1,    -1,    1,    -1,    1,    1,    1,    1,    -1,    1,    -1,    1,    1};


	// Write your code here
	 static ap_int<16> shift_reg[N];
	 //acc_t acc;
	 data_t acc;
	 //int i;
	 acc = 0;
	 //Shift_Accum_Loop:
         #pragma HLS ARRAY_PARTITION variable=c complete
         #pragma HLS ARRAY_PARTITION variable=shift_reg complete
         #pragma HLS PIPELINE II=1
         #pragma HLS INLINE off
         #pragma HLS LATENCY min=1 max=1
         
         acc = x * c[0];
         
         SHIFT_MAC: for(int i = N-1; i > 0; i--) {
         #pragma HLS UNROLL
         shift_reg[i] = shift_reg[i-1];
         acc += shift_reg[i] * c[i];
}
         shift_reg[0] = x;
         *y=acc;
	
}

void firQ2 (
  data_t *y,
  data_t x
  ) {

	coef_t c[N] = {-1,    -1,    1,    -1,    1,    -1,    1,    -1,    -1,    -1,    -1,    1,    -1,    1,    -1,    1,    1,    -1,    1,    -1,    -1,    1,    -1,    1,    1,    1,    1,    -1,    1,    -1,    1,    1};


	// Write your code here
	 static ap_int<16> shift_reg[N];
	 //acc_t acc;
	 data_t acc;
	 //int i;
	 acc = 0;
	 //Shift_Accum_Loop:
         #pragma HLS ARRAY_PARTITION variable=c complete
         #pragma HLS ARRAY_PARTITION variable=shift_reg complete
         #pragma HLS PIPELINE II=1
         #pragma HLS INLINE off
         #pragma HLS LATENCY min=1 max=1
         
         acc = x * c[0];
         
         SHIFT_MAC: for(int i = N-1; i > 0; i--) {
         #pragma HLS UNROLL
         shift_reg[i] = shift_reg[i-1];
         acc += shift_reg[i] * c[i];
}
         shift_reg[0] = x;
         *y=acc;
	
}


void fir (  data_t I,  data_t Q,  data_t *X,  data_t *Y  ){

	// Write your code here
	
	//Calculate X

	//Calculate Y


    #pragma HLS PIPELINE II=1
    
    //int i1_out, i2_out, q1_out, q2_out;
    data_t i1_out, i2_out, q1_out, q2_out;
    
    // Process through individual FIR filters
    firI1(&i1_out, I);
    firI2(&i2_out, I);
    firQ1(&q1_out, Q);
    firQ2(&q2_out, Q);
    
    // Complex matched filter combination
    // X = I1 - Q2
    // Y = I2 + Q1
    *X = (data_t)(i1_out - q2_out);
    *Y = (data_t)(i2_out + q1_out);
}


