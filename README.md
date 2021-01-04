#Earliest Deadline First (EDF) Fast Fourier Transform (FFT) Demo

## Introduction

This repository contains a demo project for an EDF Scheduler which is based on [FreeRTOS](https://www.freertos.org/) and implemented on a [STM32F769I-Disc0](https://www.st.com/en/evaluation-tools/32f769idiscovery.html) board.  
The Demo itselfs consists of three tasks:

1. receiving
2. FFT calculation
3. sending

### Task 1 Receiving
The receiving task waits for data received over UDP port 55556. The FFT supports a 2^11 (2048) calculation, which means the received data must contain 2048 float sample points. The sample data itself is limited to the ethernet paket size of 1518 bytes. Which means, the data must be splitted in 8 UDP pakets and each of these pakets contains a struct of 256 floats and the paket number (1-8). The resulting size are $256 * 4 bytes + 1 * 4 bytes = 1024 bytes$ each UDP paket. When the task has received the 2048 samples, it sends them to a FreeRTOS queue.

### Task 2 FFT
The FFT Calculation task waits for data from the receiving task. When the data are available it will calculate the FFT with the size of 2048, after this the magnitude based on the FFT results will be calculated. Finally the result of the magnitude calculation will be send to another FreeRTOS queue.

### Task 3 Sending
The sending task waits for data from the FFT calculation taks. When the data are available it will split the results of the magnitude calculation (1024 points) to 4 UDP pakets and send it back to the host on UDP port 55555.

The tasks have the following EDF characteristics:

<center>

| Task          | worst execution time | period  | deadline |
|:-------------:|:--------------------:|:-------:|:--------:|
| Receiving     | 2ms                  | 10ms    | 10ms     |
| FFT           | 2ms                  | 10ms    | 10ms     |
| Sending       | 2ms                  | 10ms    | 10ms     |

</center>

The resulting CPU load amounts to 60%, in the free time the modified idle task is executed.  
The tasks characteristics can be modiefied in hooks.c under the following lines:
```C
createEDFTask(udpReceivingTask, "UDPReceive", (unsigned short ) 200, NULL, 2, 10, 10); // create Receiving task (wcet 2ms, period 10ms, deadline 10ms)
createEDFTask(calculateFFT, "FFT", (unsigned short ) 200, NULL, 2, 10, 10); // create FFT task (wcet 2ms, period 10ms, deadline 10ms)
createEDFTask(udpSendingTask, "UDPSend", (unsigned short ) 400, NULL, 2, 10, 10); // create Sending task (wcet 2ms, period 10ms, deadline 10ms)
```
:warning: **Attention!** Modify tasks characteristics can be result to a deadlock or receiving ethernet buffer overflow. Change the values only if you know how the system is working.

## Installation

The binary file can be found under the folder Debug in the repository or directly download it [here](https://gitlab.fa-wi.de/punicawaikiki/freertos-ethernet-edf/-/raw/master/Debug/freertos-ethernet-edf.bin). Download this file and copy it to the STM32F769I-Disc0 board.  
:warning: **This repository contains only the matching driver and properties for the STM32F769I-Disc0 board.** Please only use the binary file for this board.

### Interface
There is also an interface available for cummunication between the host computer and the STM32F769I-Disc0 board, which is located under [Python EDF Interface](https://gitlab.fa-wi.de/punicawaikiki/edf-python-interface).

### Enhanced EDF Scheduler informations

In the "main.h" file a DEBUG_MODE flag is stored, which displays debug messages when activated via the USB port with the help of a USART.  
The Properties of the USART Connection are as follows:

- Port: STM32F769I-Disc0 USB Port 
- Speed: 115200 B/s
- Databits: 8
- Parity: None
- Stop Bits: 1
- Flow Control: None

The USART print out can be disabled/enabled in main.h as under the following line: 
```C
#define DEBUG_MODE ( 1 ) // switch to zero to disable USART print outs
```

## Portability

The whole EDF Scheduler consists of two files (edf_tasks.h and edf_tasks.c) and can easily be ported to other projects and boards.  
:warning: **The minimum Stack size for FreeRTOS task must be adjusted at least to 200 words.**

## Contribution
Pull requests are welcome. For major changes, please open an issue first to discuss what you would like to change.

## License
[MIT](https://choosealicense.com/licenses/mit/)
