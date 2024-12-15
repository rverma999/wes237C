#include<math.h>
#include "dft.h"
#include"coefficients256.h"


typedef double DType_;

void dft(DTYPE real_input[SIZE], DTYPE imag_input[SIZE],DTYPE real_output[SIZE], DTYPE imag_output[SIZE])
{


    #pragma HLS INTERFACE axis port=real_input,imag_input
    #pragma HLS INTERFACE axis port=real_output,imag_output
    
    // Array partitioning
    #pragma HLS ARRAY_PARTITION variable=real_input cyclic factor=4
    #pragma HLS ARRAY_PARTITION variable=imag_input cyclic factor=4
    #pragma HLS ARRAY_PARTITION variable=real_output cyclic factor=4
    #pragma HLS ARRAY_PARTITION variable=imag_output cyclic factor=4
    
    //int freq_idx, time_idx;
    // Arrays for storing frequency domain results
    DType_ freq_real[SIZE];
    DType_ freq_imag[SIZE];
    #pragma HLS ARRAY_PARTITION variable=freq_real cyclic factor=4
    #pragma HLS ARRAY_PARTITION variable=freq_imag cyclic factor=4

    // unrolling
    for(int freq_idx = 0; freq_idx < SIZE; ++freq_idx) {
        #pragma HLS PIPELINE II=1
        freq_real[freq_idx] = 0;
        freq_imag[freq_idx] = 0;
        
        #pragma HLS UNROLL factor=4
        for (int time_idx = 0; time_idx < SIZE; ++time_idx) {
            int table_idx = (freq_idx * time_idx) % SIZE;
            DType_ cos_val = cos_coefficients_table[table_idx];
            DType_ sin_val = sin_coefficients_table[table_idx];
            
            freq_real[freq_idx] += (real_input[time_idx] * cos_val -
                                  imag_input[time_idx] * sin_val);
            freq_imag[freq_idx] += (real_input[time_idx] * sin_val +
                                  imag_input[time_idx] * cos_val);
        }
    }
    
    // Output copying
    #pragma HLS PIPELINE II=1
    for(int i = 0; i < SIZE; ++i) {
        real_output[i] = freq_real[i];
        imag_output[i] = freq_imag[i];
    }
}
