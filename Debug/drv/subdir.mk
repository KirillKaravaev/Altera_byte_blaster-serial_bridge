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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/cmsis" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/cmsis/inc" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/cmsis/stm32" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/cmsis/stm32/inc" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/drv" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/fsusb/inc" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/fsusb/src" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/fsusb" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/src" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/stdperiph" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/stdperiph/inc" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/stdperiph/src" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/sys" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-drv

clean-drv:
	-$(RM) ./drv/led.cyclo ./drv/led.d ./drv/led.o ./drv/led.su ./drv/timebase.cyclo ./drv/timebase.d ./drv/timebase.o ./drv/timebase.su

.PHONY: clean-drv

