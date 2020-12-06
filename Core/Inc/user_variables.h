/* Functions for communicate with the UDP Interface*/

#ifndef __USER_STRUCTS_H
#define __USER_STRUCTS_H


//#include "arm_math.h"

#define SAMPLE_ARRAY_SIZE 64
#define EPOCHES 16
#define FFT_SIZE (SAMPLE_ARRAY_SIZE * EPOCHES) / 2
#define TOTAL_SAMPLE_SIZE SAMPLE_ARRAY_SIZE * EPOCHES


// define structs
typedef struct{
	int messageNumber;
    double x;
	double y;
}single_sample_struct;

typedef struct{
	int messageCounter;
	double x[SAMPLE_ARRAY_SIZE];
	double y[SAMPLE_ARRAY_SIZE];
}samples_input_struct;

typedef struct{
	double y[TOTAL_SAMPLE_SIZE];
}fft_input_samples;

typedef struct{
	double y[FFT_SIZE];
}fft_output_samples;


typedef struct{
	double messageCounter;
	double results[SAMPLE_ARRAY_SIZE];
}samples_output_struct;

#endif /* __USER_STRUCTS_H */
