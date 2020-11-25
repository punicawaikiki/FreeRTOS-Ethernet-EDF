/* Functions for communicate with the UDP Interface*/

#ifndef __USER_STRUCTS_H
#define __USER_STRUCTS_H


// define structs
typedef struct{
    double x;
	double y;
}single_sample_struct;

// TODO: why only low array sizes working?
typedef struct{
	   double x[64];
	   double y[64];
}samples_struct;


#endif /* __USER_STRUCTS_H */
