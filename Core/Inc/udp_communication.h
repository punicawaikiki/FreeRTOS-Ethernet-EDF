/* Functions for communicate with the UDP Interface*/

#ifndef __UDP_COMMUNICATION_H
#define __UDP_COMMUNICATION_H


// define structs
typedef struct{
	int number;
    double x;
	double y;
}single_sample_struct;

// TODO: why only low array sizes working?
typedef struct{
	   int number[10];
	   double x[10];
	   double y[10];
}samples_struct;

// Return Type: void
// Name: udpReceivingTask
// Parameters: void *pvParameters
// Declaration
void udpReceivingTask(void *pvParameters);

// Return Type: void
// Name: udpSendingTask
// Parameters: void *pvParameters
// Declaration
void udpSendingTask(void *pvParameters);



#endif /* __UDP_COMMUNICATION_H */
