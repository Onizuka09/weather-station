################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../DHT22Lib/DHT22.c 

OBJS += \
./DHT22Lib/DHT22.o 

C_DEPS += \
./DHT22Lib/DHT22.d 


# Each subdirectory must supply rules for building sources it contributes
DHT22Lib/%.o DHT22Lib/%.su: ../DHT22Lib/%.c DHT22Lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F401xE -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I/home/moktar/STM32CubeIDE/workspace_1.10.1/STM32F4_DHT22/DHT22Lib -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-DHT22Lib

clean-DHT22Lib:
	-$(RM) ./DHT22Lib/DHT22.d ./DHT22Lib/DHT22.o ./DHT22Lib/DHT22.su

.PHONY: clean-DHT22Lib

