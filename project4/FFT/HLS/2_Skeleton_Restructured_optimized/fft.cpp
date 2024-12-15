/*
This is traditional 2-radix DIT FFT algorithm implementation.
INPUT:
	In_R, In_I[]: Real and Imag parts of Complex signal

OUTPUT:
	Out_R, Out_I[]: Real and Imag parts of Complex signal
*/

#include "fft.h"

void bit_reverse(DTYPE X_R[SIZE], DTYPE X_I[SIZE]);
void fft_stage_first(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);
void fft_stages(DTYPE X_R[SIZE], DTYPE X_I[SIZE], int STAGES, DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);
void fft_stage_last(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]);


void fft(DTYPE X_R[SIZE], DTYPE X_I[SIZE], DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE])
{
	bit_reverse(X_R, X_I);

	//Call fft
	DTYPE Stage1_R[SIZE], Stage1_I[SIZE];
	DTYPE Stage2_R[SIZE], Stage2_I[SIZE];
	DTYPE Stage3_R[SIZE], Stage3_I[SIZE];
	DTYPE Stage4_R[SIZE], Stage4_I[SIZE];
	DTYPE Stage5_R[SIZE], Stage5_I[SIZE];
	DTYPE Stage6_R[SIZE], Stage6_I[SIZE];
	DTYPE Stage7_R[SIZE], Stage7_I[SIZE];
	DTYPE Stage8_R[SIZE], Stage8_I[SIZE];
	DTYPE Stage9_R[SIZE], Stage9_I[SIZE];

	fft_stage_first(X_R, X_I, Stage1_R, Stage1_I);
	fft_stages(Stage1_R, Stage1_I, 2, Stage2_R, Stage2_I);
	fft_stages(Stage2_R, Stage2_I, 3, Stage3_R, Stage3_I);
	fft_stages(Stage3_R, Stage3_I, 4, Stage4_R, Stage4_I);
	fft_stages(Stage4_R, Stage4_I, 5, Stage5_R, Stage5_I);
	fft_stages(Stage5_R, Stage5_I, 6, Stage6_R, Stage6_I);
	fft_stages(Stage6_R, Stage6_I, 7, Stage7_R, Stage7_I);
	fft_stages(Stage7_R, Stage7_I, 8, Stage8_R, Stage8_I);
	fft_stages(Stage8_R, Stage8_I, 9, Stage9_R, Stage9_I);
	fft_stage_last(Stage9_R, Stage9_I, OUT_R, OUT_I);

}

void bit_reverse(DTYPE X_R[SIZE], DTYPE X_I[SIZE]) {
    // Bit reversal implementation
    INTTYPE i, j, k;
    DTYPE temp_R, temp_I;

    #pragma HLS PIPELINE II=1
    for (i = 0; i < SIZE; i++) {
        j = 0;
        for (k = 0; k < M; k++) {
            #pragma HLS UNROLL
            if ((i >> k) & 1) {
                j |= 1 << (M - 1 - k);
            }
        }
        if (i < j) {
            // Swap real parts
            temp_R = X_R[i];
            X_R[i] = X_R[j];
            X_R[j] = temp_R;

            // Swap imaginary parts
            temp_I = X_I[i];
            X_I[i] = X_I[j];
            X_I[j] = temp_I;
        }
    }
}

/*=======================BEGIN: FFT=========================*/

// Stage 1
void fft_stage_first(DTYPE X_R[SIZE], DTYPE X_I[SIZE],
                     DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {
    // Stage 1 implementation
    INTTYPE i;
    #pragma HLS PIPELINE II=1
    for (i = 0; i < SIZE; i += 2) {
        #pragma HLS UNROLL
        DTYPE Xt0_R = X_R[i];
        DTYPE Xt0_I = X_I[i];
        DTYPE Xt1_R = X_R[i + 1];
        DTYPE Xt1_I = X_I[i + 1];

        // Twiddle factors for stage 1 are unity (1 + 0j)
        DTYPE twiddle_R = 1.0;
        DTYPE twiddle_I = 0.0;

        // Butterfly computations
        DTYPE temp_R = twiddle_R * Xt1_R - twiddle_I * Xt1_I;
        DTYPE temp_I = twiddle_R * Xt1_I + twiddle_I * Xt1_R;

        OUT_R[i] = Xt0_R + temp_R;
        OUT_I[i] = Xt0_I + temp_I;

        OUT_R[i + 1] = Xt0_R - temp_R;
        OUT_I[i + 1] = Xt0_I - temp_I;
    }
}

// Intermediate stages
void fft_stages(DTYPE X_R[SIZE], DTYPE X_I[SIZE],
                int stage, DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {
    // Intermediate stages implementation
    INTTYPE DFTpts = 1 << stage;      // Points in sub DFT (2^stage)
    INTTYPE numBF = DFTpts / 2;     // Number of butterflies per DFT
    INTTYPE step = SIZE / DFTpts;
    INTTYPE i, j, k;

    #pragma HLS PIPELINE II=1
    for (k = 0; k < SIZE; k += DFTpts) {
        for (j = 0; j < numBF; j++) {
        #pragma HLS UNROLL
            // Index calculations
            INTTYPE pos = j * step;
            DTYPE twiddle_R = W_real[pos];
            DTYPE twiddle_I = W_imag[pos];

            for (i = k + j; i < k + j + 1; i++) {
        //#pragma HLS UNROLL
                INTTYPE i_lower = i + numBF;

                DTYPE temp_R = twiddle_R * X_R[i_lower] - twiddle_I * X_I[i_lower];
                DTYPE temp_I = twiddle_R * X_I[i_lower] + twiddle_I * X_R[i_lower];

                OUT_R[i] = X_R[i] + temp_R;
                OUT_I[i] = X_I[i] + temp_I;

                OUT_R[i_lower] = X_R[i] - temp_R;
                OUT_I[i_lower] = X_I[i] - temp_I;
            }
        }
    }
}

// Last stage
void fft_stage_last(DTYPE X_R[SIZE], DTYPE X_I[SIZE],
                    DTYPE OUT_R[SIZE], DTYPE OUT_I[SIZE]) {
    // Last stage implementation
    INTTYPE DFTpts = SIZE;
    INTTYPE numBF = DFTpts / 2;
    INTTYPE step = 1;
    INTTYPE i, j, k;

    #pragma HLS PIPELINE II=1
    for (k = 0; k < SIZE; k += DFTpts) {
        for (j = 0; j < numBF; j++) {
        #pragma HLS UNROLL
            // Index calculations
            INTTYPE pos = j * step;
            DTYPE twiddle_R = W_real[pos];
            DTYPE twiddle_I = W_imag[pos];

            for (i = k + j; i < k + j + 1; i++) {
        //#pragma HLS UNROLL
                INTTYPE i_lower = i + numBF;

                DTYPE temp_R = twiddle_R * X_R[i_lower] - twiddle_I * X_I[i_lower];
                DTYPE temp_I = twiddle_R * X_I[i_lower] + twiddle_I * X_R[i_lower];

                OUT_R[i] = X_R[i] + temp_R;
                OUT_I[i] = X_I[i] + temp_I;

                OUT_R[i_lower] = X_R[i] - temp_R;
                OUT_I[i_lower] = X_I[i] - temp_I;
            }
        }
    }
}



