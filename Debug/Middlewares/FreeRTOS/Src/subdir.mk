################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/FreeRTOS/Src/croutine.c \
../Middlewares/FreeRTOS/Src/event_groups.c \
../Middlewares/FreeRTOS/Src/list.c \
../Middlewares/FreeRTOS/Src/queue.c \
../Middlewares/FreeRTOS/Src/stream_buffer.c \
../Middlewares/FreeRTOS/Src/tasks.c \
../Middlewares/FreeRTOS/Src/timers.c 

OBJS += \
./Middlewares/FreeRTOS/Src/croutine.o \
./Middlewares/FreeRTOS/Src/event_groups.o \
./Middlewares/FreeRTOS/Src/list.o \
./Middlewares/FreeRTOS/Src/queue.o \
./Middlewares/FreeRTOS/Src/stream_buffer.o \
./Middlewares/FreeRTOS/Src/tasks.o \
./Middlewares/FreeRTOS/Src/timers.o 

C_DEPS += \
./Middlewares/FreeRTOS/Src/croutine.d \
./Middlewares/FreeRTOS/Src/event_groups.d \
./Middlewares/FreeRTOS/Src/list.d \
./Middlewares/FreeRTOS/Src/queue.d \
./Middlewares/FreeRTOS/Src/stream_buffer.d \
./Middlewares/FreeRTOS/Src/tasks.d \
./Middlewares/FreeRTOS/Src/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FreeRTOS/Src/croutine.o: ../Middlewares/FreeRTOS/Src/croutine.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS/Src/croutine.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS/Src/event_groups.o: ../Middlewares/FreeRTOS/Src/event_groups.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS/Src/event_groups.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS/Src/list.o: ../Middlewares/FreeRTOS/Src/list.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS/Src/list.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS/Src/queue.o: ../Middlewares/FreeRTOS/Src/queue.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS/Src/queue.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS/Src/stream_buffer.o: ../Middlewares/FreeRTOS/Src/stream_buffer.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS/Src/stream_buffer.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS/Src/tasks.o: ../Middlewares/FreeRTOS/Src/tasks.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS/Src/tasks.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Middlewares/FreeRTOS/Src/timers.o: ../Middlewares/FreeRTOS/Src/timers.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DARM_MATH_CM7 -DSTM32F769xx -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS/Src/timers.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

