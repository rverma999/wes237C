#include<math.h>
#include "dft.h"
#include"coefficients256.h"


typedef double DType_;
// Modified interface with separate input/output arrays
void dft(DTYPE real_in[SIZE], DTYPE imag_in[SIZE], 
         DTYPE real_out[SIZE], DTYPE imag_out[SIZE])
{
    //#pragma HLS INTERFACE axis port=real_in
    //#pragma HLS INTERFACE axis port=imag_in
    //#pragma HLS INTERFACE axis port=real_out
    //#pragma HLS INTERFACE axis port=imag_out
    //#pragma HLS INTERFACE s_axilite port=return

    // Partition coefficient tables for parallel access
    #pragma HLS ARRAY_PARTITION variable=cos_coefficients_table complete dim=1
    #pragma HLS ARRAY_PARTITION variable=sin_coefficients_table complete dim=1
    
    // Initialize output arrays
    Init_Loop:
    for(int i = 0; i < SIZE; i++) {
        #pragma HLS PIPELINE II=1
        real_out[i] = 0;
        imag_out[i] = 0;
    }

    // Main computation loops
    Freq_Loop:
    for(int freq_idx = 0; freq_idx < SIZE; ++freq_idx) {
       // #pragma HLS LOOP_TRIPCOUNT min=256 max=256
        #pragma HLS PIPELINE II=1
        
        DType_ temp_real = 0;
        DType_ temp_imag = 0;

        Time_Loop:
        for (int time_idx = 0; time_idx < SIZE; ++time_idx) {
            #pragma HLS PIPELINE II=1
            //#pragma HLS LOOP_TRIPCOUNT min=256 max=256
            
            int table_idx = (freq_idx * time_idx) % SIZE;
            DType_ cos_val = cos_coefficients_table[table_idx];
            DType_ sin_val = sin_coefficients_table[table_idx];
            
            DType_ real_sample = real_in[time_idx];
            DType_ imag_sample = imag_in[time_idx];

            temp_real += (real_sample * cos_val - imag_sample * sin_val);
            temp_imag += (real_sample * sin_val + imag_sample * cos_val);
        }
        
        real_out[freq_idx] = temp_real;
        imag_out[freq_idx] = temp_imag;
    }
}
