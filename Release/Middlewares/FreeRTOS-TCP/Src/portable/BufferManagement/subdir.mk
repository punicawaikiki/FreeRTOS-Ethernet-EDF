################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement/BufferAllocation_2.c 

OBJS += \
./Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement/BufferAllocation_2.o 

C_DEPS += \
./Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement/BufferAllocation_2.d 


# Each subdirectory must supply rules for building sources it contributes
Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement/BufferAllocation_2.o: ../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement/BufferAllocation_2.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -DUSE_HAL_DRIVER -D__FPU_PRESENT -DSTM32F769xx -DSTM32F7xx -DARM_MATH_CM7 -DDEBUG -c -I../Core/Inc -I"C:/Users/fabia/STM32CubeIDE/workspace_1.5.0/freertos-ethernet-edf/Middlewares/FreeRTOS-TCP/Inc/GCC" -I../Drivers/STM32F7xx_HAL_Driver/Inc -I../Drivers/STM32F7xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F7xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/FreeRTOS/Inc -I../Middlewares/FreeRTOS/Inc/portable -I../Middlewares/FreeRTOS/Src -I../Middlewares/FreeRTOS/Src/portable -I../Middlewares/FreeRTOS/Src/portable/port -I../Middlewares/FreeRTOS/Src/portable/MemMang -I../Middlewares/FreeRTOS-TCP/Src/portable -I../Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement -I../Middlewares/FreeRTOS-TCP/Src/portable/GCC -I../Middlewares/FreeRTOS-TCP/Inc -I../Middlewares/CMSIS-DSP -I../Middlewares/CMSIS-DSP/Inc -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement/BufferAllocation_2.d" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

