################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/FreeRTOS/Src/portable/port/subdir.mk
-include Middlewares/FreeRTOS/Src/portable/MemMang/subdir.mk
-include Middlewares/FreeRTOS/Src/subdir.mk
-include Middlewares/FreeRTOS-TCP/Src/portable/BufferManagement/subdir.mk
-include Middlewares/FreeRTOS-TCP/Src/subdir.mk
-include Drivers/STM32F7xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

BUILD_ARTIFACT_NAME := freertos-ethernet-edf
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX := 
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME).$(BUILD_ARTIFACT_EXTENSION)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
freertos-ethernet-edf.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
freertos-ethernet-edf.list \

OBJCOPY_BIN += \
freertos-ethernet-edf.bin \


# All Target
all: main-build

# Main-build Target
main-build: freertos-ethernet-edf.elf secondary-outputs

# Tool invocations
freertos-ethernet-edf.elf: $(OBJS) $(USER_OBJS) C:\Users\fabia\STM32CubeIDE\workspace_1.5.0\freertos-ethernet-edf\STM32F769NIHX_FLASH.ld
	arm-none-eabi-gcc -o "freertos-ethernet-edf.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m7 -T"C:\Users\fabia\STM32CubeIDE\workspace_1.5.0\freertos-ethernet-edf\STM32F769NIHX_FLASH.ld" --specs=nosys.specs -Wl,-Map="freertos-ethernet-edf.map" -Wl,--gc-sections -static -L../Middlewares/CMSIS-DSP/libs --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

freertos-ethernet-edf.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "freertos-ethernet-edf.list"
	@echo 'Finished building: $@'
	@echo ' '

freertos-ethernet-edf.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "freertos-ethernet-edf.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents fail-specified-linker-script-missing warn-no-linker-script-specified
.SECONDARY:

-include ../makefile.targets
