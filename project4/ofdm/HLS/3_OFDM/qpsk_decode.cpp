#include "fft.h"
#include <stdio.h>

void qpsk_decode(DTYPE R[SIZE], DTYPE I[SIZE], int D[SIZE]) {

    int symbol_value, sample_index;
    DTYPE real_component, imag_component;
    
    for(sample_index = 0; sample_index < SIZE; sample_index++) {
        real_component = R[sample_index];
        imag_component = I[sample_index];
        
        // Determine quadrant and assign corresponding symbol
        if(real_component >= 0 && imag_component >= 0) { symbol_value = 0; }  // Quadrant 1
        if(real_component > 0 && imag_component < 0) { symbol_value = 2; }    // Quadrant 4
        if(real_component < 0 && imag_component > 0) { symbol_value = 1; }    // Quadrant 2
        if(real_component < 0 && imag_component < 0) { symbol_value = 3; }    // Quadrant 3
        
        D[sample_index] = symbol_value;
    }
}

