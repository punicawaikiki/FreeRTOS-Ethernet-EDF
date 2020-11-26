################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_ARP.c \
../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_DHCP.c \
../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_DNS.c \
../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_IP.c \
../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_Sockets.c \
../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_Stream_Buffer.c \
../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_TCP_IP.c \
../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_TCP_WIN.c \
../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_UDP_IP.c \
../Middlewares/FreeRTOS-TCP/Src/NetworkInterface.c \
../Middlewares/FreeRTOS-TCP/Src/phyHandling.c 

OBJS += \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_ARP.o \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_DHCP.o \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_DNS.o \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_IP.o \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_Sockets.o \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_Stream_Buffer.o \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_TCP_IP.o \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_TCP_WIN.o \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_UDP_IP.o \
./Middlewares/FreeRTOS-TCP/Src/NetworkInterface.o \
./Middlewares/FreeRTOS-TCP/Src/phyHandling.o 

C_DEPS += \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_ARP.d \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_DHCP.d \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_DNS.d \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_IP.d \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_Sockets.d \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_Stream_Buffer.d \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_TCP_IP.d \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_TCP_WIN.d \
./Middlewares/FreeRTOS-TCP/Src/FreeRTOS_UDP_IP.d \
./Middlewares/FreeRTOS-TCP/Src/NetworkInterface.d \
./Middlewares/FreeRTOS-TCP/Src/phyHandling.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FreeRTOS-TCP/Src/FreeRTOS_ARP.o: ../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_ARP.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS-TCP/Src/FreeRTOS_ARP.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS-TCP/Src/FreeRTOS_DHCP.o: ../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_DHCP.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS-TCP/Src/FreeRTOS_DHCP.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS-TCP/Src/FreeRTOS_DNS.o: ../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_DNS.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS-TCP/Src/FreeRTOS_DNS.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS-TCP/Src/FreeRTOS_IP.o: ../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_IP.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS-TCP/Src/FreeRTOS_IP.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS-TCP/Src/FreeRTOS_Sockets.o: ../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_Sockets.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS-TCP/Src/FreeRTOS_Sockets.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS-TCP/Src/FreeRTOS_Stream_Buffer.o: ../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_Stream_Buffer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS-TCP/Src/FreeRTOS_Stream_Buffer.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS-TCP/Src/FreeRTOS_TCP_IP.o: ../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_TCP_IP.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS-TCP/Src/FreeRTOS_TCP_IP.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS-TCP/Src/FreeRTOS_TCP_WIN.o: ../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_TCP_WIN.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS-TCP/Src/FreeRTOS_TCP_WIN.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS-TCP/Src/FreeRTOS_UDP_IP.o: ../Middlewares/FreeRTOS-TCP/Src/FreeRTOS_UDP_IP.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS-TCP/Src/FreeRTOS_UDP_IP.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS-TCP/Src/NetworkInterface.o: ../Middlewares/FreeRTOS-TCP/Src/NetworkInterface.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS-TCP/Src/NetworkInterface.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS-TCP/Src/phyHandling.o: ../Middlewares/FreeRTOS-TCP/Src/phyHandling.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS-TCP/Src/phyHandling.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

