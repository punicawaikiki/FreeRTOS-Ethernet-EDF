/* Functions for communicate with the UDP Interface*/

#ifndef __USER_STRUCTS_H
#define __USER_STRUCTS_H


#include "arm_math.h"

#define SAMPLE_ARRAY_SIZE 256
#define EPOCHES 4
#define FFT_SIZE (SAMPLE_ARRAY_SIZE * EPOCHES) / 2
#define TOTAL_SAMPLE_SIZE SAMPLE_ARRAY_SIZE * EPOCHES
#define SIZE_OF_EDF_TASKS_ARRAY 3
#define EDF_DISABLED_PRIORITY configMAX_PRIORITIES - 3
#define EDF_IDLE_PRIORITY configMAX_PRIORITIES - 2
#define EDF_ENABLED_PRIOTIRY configMAX_PRIORITIES - 1

// define structs
typedef struct{
	int messageNumber;
	float32_t sample;
}single_sample_struct;

typedef struct{
	int messageCounter;
	float32_t samples[SAMPLE_ARRAY_SIZE];
}samples_input_struct;

typedef struct{
	float32_t samples[TOTAL_SAMPLE_SIZE];
}fft_input_samples;

typedef struct{
	int messageCounter;
	float32_t results[SAMPLE_ARRAY_SIZE];
}samples_output_struct;

#endif /* __USER_STRUCTS_H */
