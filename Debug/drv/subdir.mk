################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../drv/led.c \
../drv/timebase.c 

OBJS += \
./drv/led.o \
./drv/timebase.o 

C_DEPS += \
./drv/led.d \
./drv/timebase.d 


# Each subdirectory must supply rules for building sources it contributes
drv/%.o drv/%.su drv/%.cyclo: ../drv/%.c drv/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis/stm32" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis/stm32/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/drv" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/fsusb/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/fsusb/src" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/fsusb" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/src" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/stdperiph" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/stdperiph/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/stdperiph/src" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/sys" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-drv

clean-drv:
	-$(RM) ./drv/led.cyclo ./drv/led.d ./drv/led.o ./drv/led.su ./drv/timebase.cyclo ./drv/timebase.d ./drv/timebase.o ./drv/timebase.su

.PHONY: clean-drv

