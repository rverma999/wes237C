#include<math.h>
#include "dft.h"
#include"coefficients256.h"


typedef double DType_;

void dft(DTYPE real_input[SIZE], DTYPE imag_input[SIZE])
{
   //#pragma HLS INTERFACE axis port=real_input
   // #pragma HLS INTERFACE axis port=imag_input
   // #pragma HLS INTERFACE s_axilite port=return

    // Partition arrays for parallel access
    #pragma HLS ARRAY_PARTITION variable=cos_coefficients_table complete dim=1
    #pragma HLS ARRAY_PARTITION variable=sin_coefficients_table complete dim=1
    
    // Local arrays with block partitioning
    DType_ freq_real[SIZE];
    DType_ freq_imag[SIZE];
    #pragma HLS ARRAY_PARTITION variable=freq_real block factor=16 dim=1
    #pragma HLS ARRAY_PARTITION variable=freq_imag block factor=16 dim=1

    // Pipeline the initialization
    Init_Loop:
    for(int i = 0; i < SIZE; i++) {
        #pragma HLS PIPELINE II=1
        freq_real[i] = 0;
        freq_imag[i] = 0;
    }

    // Main computation loops
    Freq_Loop:
    for(int freq_idx = 0; freq_idx < SIZE; ++freq_idx) {
        //#pragma HLS LOOP_TRIPCOUNT min=256 max=256
        #pragma HLS PIPELINE II=1
        
        DType_ temp_real = 0;
        DType_ temp_imag = 0;

        Time_Loop:
        for (int time_idx = 0; time_idx < SIZE; ++time_idx) {
            #pragma HLS PIPELINE II=1
            //#pragma HLS LOOP_TRIPCOUNT min=256 max=256
            
            // Compute table index
            int table_idx = (freq_idx * time_idx) % SIZE;
            
            // Load twiddle factors
            DType_ cos_val = cos_coefficients_table[table_idx];
            DType_ sin_val = sin_coefficients_table[table_idx];
            
            // Load input samples
            DType_ real_sample = real_input[time_idx];
            DType_ imag_sample = imag_input[time_idx];

            // Complex MAC operation
            temp_real += (real_sample * cos_val - imag_sample * sin_val);
            temp_imag += (real_sample * sin_val + imag_sample * cos_val);
        }
        
        // Store results
        freq_real[freq_idx] = temp_real;
        freq_imag[freq_idx] = temp_imag;
    }

    // Copy results 
    Output_Loop:
    for(int i = 0; i < SIZE; ++i) {
        #pragma HLS PIPELINE II=1
        real_input[i] = freq_real[i];
        imag_input[i] = freq_imag[i];
    }
}

