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

    // Main DFT computation loop
    for(freq_idx = 0; freq_idx < SIZE; ++freq_idx) {
        freq_real[freq_idx] = 0;
        freq_imag[freq_idx] = 0;

        // Calculate angular frequency
        omega = (2.0 * 3.141592653589 / SIZE) * (DType_)freq_idx;

        // Process each time domain sample
        for(time_idx = 0; time_idx < SIZE; ++time_idx) {
            // Compute twiddle factors
            cos_val = cos(time_idx * omega);
            sin_val = -sin(time_idx * omega);

            // Accumulate DFT sum
            freq_real[freq_idx] += (real_input[time_idx] * cos_val -  imag_input[time_idx] * sin_val);
            freq_imag[freq_idx] += (real_input[time_idx] * sin_val +  imag_input[time_idx] * cos_val);
        }
    }

    // Copy results back to input arrays
    for(freq_idx = 0; freq_idx < SIZE; ++freq_idx) {
        real_input[freq_idx] = freq_real[freq_idx];
        imag_input[freq_idx] = freq_imag[freq_idx];
    }
}

