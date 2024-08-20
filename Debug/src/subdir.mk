################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/blaster.c \
../src/blaster_port.c \
../src/ft245rom.c \
../src/main.c \
../src/memop.c \
../src/ringbuf.c 

OBJS += \
./src/blaster.o \
./src/blaster_port.o \
./src/ft245rom.o \
./src/main.o \
./src/memop.o \
./src/ringbuf.o 

C_DEPS += \
./src/blaster.d \
./src/blaster_port.d \
./src/ft245rom.d \
./src/main.d \
./src/memop.d \
./src/ringbuf.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o src/%.su src/%.cyclo: ../src/%.c src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis/stm32" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis/stm32/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/drv" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/fsusb/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/fsusb/src" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/fsusb" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/src" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/stdperiph" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/stdperiph/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/stdperiph/src" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/sys" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-src

clean-src:
	-$(RM) ./src/blaster.cyclo ./src/blaster.d ./src/blaster.o ./src/blaster.su ./src/blaster_port.cyclo ./src/blaster_port.d ./src/blaster_port.o ./src/blaster_port.su ./src/ft245rom.cyclo ./src/ft245rom.d ./src/ft245rom.o ./src/ft245rom.su ./src/main.cyclo ./src/main.d ./src/main.o ./src/main.su ./src/memop.cyclo ./src/memop.d ./src/memop.o ./src/memop.su ./src/ringbuf.cyclo ./src/ringbuf.d ./src/ringbuf.o ./src/ringbuf.su

.PHONY: clean-src

