/* Functions for communicate with the UDP Interface*/

#ifndef __UDP_COMMUNICATION_H
#define __UDP_COMMUNICATION_H


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
