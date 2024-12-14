/*
	Filename: phasedetector.cpp
		Phase detector

	INPUT:
		I: signal for I sample
		Q: signal for Q sample
		length: array size

	OUTPUT:
		R: Radius
		Theta: Angle

*/

#include "phasedetector.h"

void phasedetector (
  data_t *I,
  data_t *Q,

  data_t *R,
  data_t *Theta,

  int length
  ){

    // Buffers for matched filter outputs
    data_t X_out, Y_out;
	// Write your code here
   // Buffers for FIR filter outputs
    //data_t I_matched_real, I_matched_imag;
    //data_t Q_matched_real, Q_matched_imag;
    // Add null pointer checks
    if (!I || !Q || !R || !Theta || length <= 0) {
        return;
    }    
    // Process each sample
    for (int i = 0; i < length; i++) {
        #pragma HLS PIPELINE II=1
        
        // Complex Matched Filter Implementation
        // Process I channel
        //fir(&I_matched_real, I[i]);  // Real part of I channel
        //fir(&I_matched_imag, I[i]);  // Imaginary part of I channel
        //
        //// Process Q channel
        //fir(&Q_matched_real, Q[i]);  // Real part of Q channel
        //fir(&Q_matched_imag, Q[i]);  // Imaginary part of Q channel
        //
        //// Combine matched filter outputs
        //// Complex multiplication result
        //data_t real_part = I_matched_real - Q_matched_imag;
        //data_t imag_part = I_matched_imag + Q_matched_real;
      
        
        // Apply complex matched filter
        // fir function takes I and Q inputs and produces X and Y outputs
        fir(I[i], Q[i], &X_out, &Y_out);
 
        // Convert to polar coordinates using CORDIC
        cordiccart2pol(X_out,Y_out, &R[i], &Theta[i]);
    }
}




