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
     #pragma HLS unroll factor=4
     #pragma HLS pipeline II=1
     //#pragma HLS ARRAY_PARTITION variable=shift_reg cyclic factor=4
     //#pragma HLS ARRAY_PARTITION variable=c cyclic factor=4
     //pragma HLS ARRAY_PARTITION variable=shift_reg block factor=4
     //#pragma HLS ARRAY_PARTITION variable=c block factor=4
     #pragma HLS ARRAY_PARTITION variable=shift_reg complete dim=1
     #pragma HLS ARRAY_PARTITION variable=c block complete dim=1
    for(int i =N - 1; i >= 0; i--) {
	   //if (i == 0) {
	   //  acc += x*c[0];
	   //  shift_reg[0] = x;
	   //} else {
	   shift_reg[i] = shift_reg[i - 1];
	   //acc += shift_reg[i] * c[i];

	 }
     shift_reg[0] = x;

     for(int i =N - 1; i >= 0; i--) {
     //for(int i =0; i <N; i++) {
    	 //ap_int<16> temp;
    	 //if(i==0) {temp = x*c[0] ; }
    	 //else { 	 temp = shift_reg[i] * c[i]; }
    	 //acc+=temp;
    	 if(i==0) {acc += x*c[0] ; }
    	 else { 	 acc += shift_reg[i] * c[i]; }
     }

	 /*
	 for(i =N - 1; i > 0; i--) {
	 //for(i=10; i >= 0; i−−){
       //#pragma HLS unroll factor=4
       //#pragma HLS pipeline II=3


	   shift_reg[i] = shift_reg[i - 1];
	   acc += shift_reg[i] * c[i];

	 }
 	 acc += x*c[0];
     shift_reg[0] = x;
*/
	   //printf("fir_128 : i=%0d acc shift_reg[i]*c[i]='d%0d 'h%X shift_reg='h%X\n",i,acc,acc,shift_reg);

	 *y = acc;
}


