################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/edf_scheduler.c \
../Core/Src/edf_tasks.c \
../Core/Src/eth.c \
../Core/Src/fft.c \
../Core/Src/gpio.c \
../Core/Src/helper_functions.c \
../Core/Src/hooks.c \
../Core/Src/main.c \
../Core/Src/rng.c \
../Core/Src/stm32f7xx_hal_msp.c \
../Core/Src/stm32f7xx_hal_timebase_tim.c \
../Core/Src/stm32f7xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f7xx.c \
../Core/Src/udp_communication.c \
../Core/Src/usart.c 

OBJS += \
./Core/Src/edf_scheduler.o \
./Core/Src/edf_tasks.o \
./Core/Src/eth.o \
./Core/Src/fft.o \
./Core/Src/gpio.o \
./Core/Src/helper_functions.o \
./Core/Src/hooks.o \
./Core/Src/main.o \
./Core/Src/rng.o \
./Core/Src/stm32f7xx_hal_msp.o \
./Core/Src/stm32f7xx_hal_timebase_tim.o \
./Core/Src/stm32f7xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f7xx.o \
./Core/Src/udp_communication.o \
./Core/Src/usart.o 

C_DEPS += \
./Core/Src/edf_scheduler.d \
./Core/Src/edf_tasks.d \
./Core/Src/eth.d \
./Core/Src/fft.d \
./Core/Src/gpio.d \
./Core/Src/helper_functions.d \
./Core/Src/hooks.d \
./Core/Src/main.d \
./Core/Src/rng.d \
./Core/Src/stm32f7xx_hal_msp.d \
./Core/Src/stm32f7xx_hal_timebase_tim.d \
./Core/Src/stm32f7xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f7xx.d \
./Core/Src/udp_communication.d \
./Core/Src/usart.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/edf_scheduler.o: ../Core/Src/edf_scheduler.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/edf_scheduler.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/edf_tasks.o: ../Core/Src/edf_tasks.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/edf_tasks.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/eth.o: ../Core/Src/eth.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/eth.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/fft.o: ../Core/Src/fft.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/fft.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/gpio.o: ../Core/Src/gpio.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/gpio.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/helper_functions.o: ../Core/Src/helper_functions.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/helper_functions.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/hooks.o: ../Core/Src/hooks.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/hooks.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/main.o: ../Core/Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/rng.o: ../Core/Src/rng.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/rng.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f7xx_hal_msp.o: ../Core/Src/stm32f7xx_hal_msp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f7xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f7xx_hal_timebase_tim.o: ../Core/Src/stm32f7xx_hal_timebase_tim.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f7xx_hal_timebase_tim.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f7xx_it.o: ../Core/Src/stm32f7xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f7xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/system_stm32f7xx.o: ../Core/Src/system_stm32f7xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32f7xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/udp_communication.o: ../Core/Src/udp_communication.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/udp_communication.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/usart.o: ../Core/Src/usart.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/usart.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

