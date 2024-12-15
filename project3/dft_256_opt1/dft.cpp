#include<math.h>
#include "dft.h"
#include"coefficients256.h"


typedef double DType_;

void dft(DTYPE real_input[SIZE], DTYPE imag_input[SIZE])
{
    int freq_idx, time_idx;
    //FloatType omega;
    //FloatType cos_val, sin_val;
   DType_  omega;
   DType_  cos_val, sin_val;

    // Arrays for storing frequency domain results
    DType_ freq_real[SIZE];
    DType_ freq_imag[SIZE];

   for(freq_idx = 0; freq_idx < SIZE; ++freq_idx) {
     // Initialize accumulators for this frequency bin
     freq_real[freq_idx] = 0;
     freq_imag[freq_idx] = 0;
     // Process all time domain samples
      for (time_idx = 0; time_idx < SIZE; ++time_idx) {
          // Get precomputed twiddle factors from lookup table
          int table_idx = (freq_idx * time_idx) % SIZE;
          cos_val = cos_coefficients_table[table_idx];
          sin_val = sin_coefficients_table[table_idx];

          // Perform complex mac 
          freq_real[freq_idx] += (real_input[time_idx] * cos_val - 
                                imag_input[time_idx] * sin_val);
          freq_imag[freq_idx] += (real_input[time_idx] * sin_val + 
                                imag_input[time_idx] * cos_val);
      }
    }
    // Copy results back 
    for(freq_idx = 0; freq_idx < SIZE; ++freq_idx) {
        real_input[freq_idx] = freq_real[freq_idx];
        imag_input[freq_idx] = freq_imag[freq_idx];
    }
}

