/* Functions for communicate with the UDP Interface*/

#ifndef __USER_STRUCTS_H
#define __USER_STRUCTS_H


#define SAMPLE_ARRAY_SIZE 64
#define EPOCHES 16
#define FFT_SIZE 512


// define structs
typedef struct{
    double x;
	double y;
}single_sample_struct;

typedef struct{
	   double x[SAMPLE_ARRAY_SIZE];
	   double y[SAMPLE_ARRAY_SIZE];
}samples_struct;

#endif /* __USER_STRUCTS_H */