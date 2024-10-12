################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../sys/startup_gd32f10x_md.s 

C_SRCS += \
../sys/stm32_it.c \
../sys/system_gd32f10x.c \
../sys/system_stm32f10x.c 

S_UPPER_SRCS += \
../sys/startup_stm32f10x_md.S 

OBJS += \
./sys/startup_gd32f10x_md.o \
./sys/startup_stm32f10x_md.o \
./sys/stm32_it.o \
./sys/system_gd32f10x.o \
./sys/system_stm32f10x.o 

S_DEPS += \
./sys/startup_gd32f10x_md.d 

S_UPPER_DEPS += \
./sys/startup_stm32f10x_md.d 

C_DEPS += \
./sys/stm32_it.d \
./sys/system_gd32f10x.d \
./sys/system_stm32f10x.d 


# Each subdirectory must supply rules for building sources it contributes
sys/%.o: ../sys/%.s sys/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
sys/%.o: ../sys/%.S sys/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
sys/%.o sys/%.su sys/%.cyclo: ../sys/%.c sys/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis/stm32" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis/stm32/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/drv" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/fsusb/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/fsusb/src" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/fsusb" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/src" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/stdperiph" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/stdperiph/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/stdperiph/src" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/sys" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-sys

clean-sys:
	-$(RM) ./sys/startup_gd32f10x_md.d ./sys/startup_gd32f10x_md.o ./sys/startup_stm32f10x_md.d ./sys/startup_stm32f10x_md.o ./sys/stm32_it.cyclo ./sys/stm32_it.d ./sys/stm32_it.o ./sys/stm32_it.su ./sys/system_gd32f10x.cyclo ./sys/system_gd32f10x.d ./sys/system_gd32f10x.o ./sys/system_gd32f10x.su ./sys/system_stm32f10x.cyclo ./sys/system_stm32f10x.d ./sys/system_stm32f10x.o ./sys/system_stm32f10x.su

.PHONY: clean-sys

