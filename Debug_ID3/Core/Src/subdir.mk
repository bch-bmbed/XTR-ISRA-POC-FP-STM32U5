################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/logger_xtr.c \
../Core/Src/main.c \
../Core/Src/next_bio_biometrics.c \
../Core/Src/next_bio_device.c \
../Core/Src/next_bio_flash.c \
../Core/Src/next_bio_poc.c \
../Core/Src/next_bio_port.c \
../Core/Src/next_id3.c \
../Core/Src/stm32u5xx_hal_msp.c \
../Core/Src/stm32u5xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32u5xx.c \
../Core/Src/util.c 

OBJS += \
./Core/Src/logger_xtr.o \
./Core/Src/main.o \
./Core/Src/next_bio_biometrics.o \
./Core/Src/next_bio_device.o \
./Core/Src/next_bio_flash.o \
./Core/Src/next_bio_poc.o \
./Core/Src/next_bio_port.o \
./Core/Src/next_id3.o \
./Core/Src/stm32u5xx_hal_msp.o \
./Core/Src/stm32u5xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32u5xx.o \
./Core/Src/util.o 

C_DEPS += \
./Core/Src/logger_xtr.d \
./Core/Src/main.d \
./Core/Src/next_bio_biometrics.d \
./Core/Src/next_bio_device.d \
./Core/Src/next_bio_flash.d \
./Core/Src/next_bio_poc.d \
./Core/Src/next_bio_port.d \
./Core/Src/next_id3.d \
./Core/Src/stm32u5xx_hal_msp.d \
./Core/Src/stm32u5xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32u5xx.d \
./Core/Src/util.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m33 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32U585xx -DEMBEDDED -c -I../Core/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc -I../Drivers/STM32U5xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32U5xx/Include -I../Drivers/CMSIS/Include -I../NB6510/Include -I../ID3/includes -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-sp-d16 -mfloat-abi=softfp -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/logger_xtr.cyclo ./Core/Src/logger_xtr.d ./Core/Src/logger_xtr.o ./Core/Src/logger_xtr.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/next_bio_biometrics.cyclo ./Core/Src/next_bio_biometrics.d ./Core/Src/next_bio_biometrics.o ./Core/Src/next_bio_biometrics.su ./Core/Src/next_bio_device.cyclo ./Core/Src/next_bio_device.d ./Core/Src/next_bio_device.o ./Core/Src/next_bio_device.su ./Core/Src/next_bio_flash.cyclo ./Core/Src/next_bio_flash.d ./Core/Src/next_bio_flash.o ./Core/Src/next_bio_flash.su ./Core/Src/next_bio_poc.cyclo ./Core/Src/next_bio_poc.d ./Core/Src/next_bio_poc.o ./Core/Src/next_bio_poc.su ./Core/Src/next_bio_port.cyclo ./Core/Src/next_bio_port.d ./Core/Src/next_bio_port.o ./Core/Src/next_bio_port.su ./Core/Src/next_id3.cyclo ./Core/Src/next_id3.d ./Core/Src/next_id3.o ./Core/Src/next_id3.su ./Core/Src/stm32u5xx_hal_msp.cyclo ./Core/Src/stm32u5xx_hal_msp.d ./Core/Src/stm32u5xx_hal_msp.o ./Core/Src/stm32u5xx_hal_msp.su ./Core/Src/stm32u5xx_it.cyclo ./Core/Src/stm32u5xx_it.d ./Core/Src/stm32u5xx_it.o ./Core/Src/stm32u5xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/sysmem.cyclo ./Core/Src/sysmem.d ./Core/Src/sysmem.o ./Core/Src/sysmem.su ./Core/Src/system_stm32u5xx.cyclo ./Core/Src/system_stm32u5xx.d ./Core/Src/system_stm32u5xx.o ./Core/Src/system_stm32u5xx.su ./Core/Src/util.cyclo ./Core/Src/util.d ./Core/Src/util.o ./Core/Src/util.su

.PHONY: clean-Core-2f-Src

