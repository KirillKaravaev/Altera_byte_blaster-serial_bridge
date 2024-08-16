################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../usb/hw_config.c \
../usb/usb_desc.c \
../usb/usb_endp.c \
../usb/usb_istr.c \
../usb/usb_prop.c \
../usb/usb_pwr.c 

OBJS += \
./usb/hw_config.o \
./usb/usb_desc.o \
./usb/usb_endp.o \
./usb/usb_istr.o \
./usb/usb_prop.o \
./usb/usb_pwr.o 

C_DEPS += \
./usb/hw_config.d \
./usb/usb_desc.d \
./usb/usb_endp.d \
./usb/usb_istr.d \
./usb/usb_prop.d \
./usb/usb_pwr.d 


# Each subdirectory must supply rules for building sources it contributes
usb/%.o usb/%.su usb/%.cyclo: ../usb/%.c usb/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/cmsis" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/cmsis/inc" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/cmsis/stm32" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/cmsis/stm32/inc" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/drv" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/fsusb/inc" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/fsusb/src" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/fsusb" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/src" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/stdperiph" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/stdperiph/inc" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/stdperiph/src" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/sys" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-usb

clean-usb:
	-$(RM) ./usb/hw_config.cyclo ./usb/hw_config.d ./usb/hw_config.o ./usb/hw_config.su ./usb/usb_desc.cyclo ./usb/usb_desc.d ./usb/usb_desc.o ./usb/usb_desc.su ./usb/usb_endp.cyclo ./usb/usb_endp.d ./usb/usb_endp.o ./usb/usb_endp.su ./usb/usb_istr.cyclo ./usb/usb_istr.d ./usb/usb_istr.o ./usb/usb_istr.su ./usb/usb_prop.cyclo ./usb/usb_prop.d ./usb/usb_prop.o ./usb/usb_prop.su ./usb/usb_pwr.cyclo ./usb/usb_pwr.d ./usb/usb_pwr.o ./usb/usb_pwr.su

.PHONY: clean-usb

