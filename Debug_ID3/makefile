################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Drivers/STM32U5xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
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

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := POC_FP_NB6510
BUILD_ARTIFACT_EXTENSION := elf
BUILD_ARTIFACT_PREFIX :=
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
POC_FP_NB6510.elf \

MAP_FILES += \
POC_FP_NB6510.map \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
POC_FP_NB6510.list \


# All Target
all: main-build

# Main-build Target
main-build: POC_FP_NB6510.elf secondary-outputs

# Tool invocations
POC_FP_NB6510.elf POC_FP_NB6510.map: $(OBJS) $(USER_OBJS) C:\Users\benjamin.chalant\STM32CubeIDE\workspace_1.7.0\POC_FP_NB6510\STM32U585AIIXQ_FLASH.ld makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-gcc -o "POC_FP_NB6510.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m33 -T"C:\Users\benjamin.chalant\STM32CubeIDE\workspace_1.7.0\POC_FP_NB6510\STM32U585AIIXQ_FLASH.ld" --specs=nosys.specs -Wl,-Map="POC_FP_NB6510.map" -Wl,--gc-sections -static -L"C:\Users\benjamin.chalant\STM32CubeIDE\workspace_1.7.0\POC_FP_NB6510\NB6510" -L"C:\Users\benjamin.chalant\STM32CubeIDE\workspace_1.7.0\POC_FP_NB6510\ID3" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

POC_FP_NB6510.list: $(EXECUTABLES) makefile objects.list $(OPTIONAL_TOOL_DEPS)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "POC_FP_NB6510.list"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) POC_FP_NB6510.elf POC_FP_NB6510.list POC_FP_NB6510.map default.size.stdout
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST)

fail-specified-linker-script-missing:
	@echo 'Error: Cannot find the specified linker script. Check the linker settings in the build configuration.'
	@exit 2

warn-no-linker-script-specified:
	@echo 'Warning: No linker script specified. Check the linker settings in the build configuration.'

.PHONY: all clean dependents main-build fail-specified-linker-script-missing warn-no-linker-script-specified

-include ../makefile.targets
