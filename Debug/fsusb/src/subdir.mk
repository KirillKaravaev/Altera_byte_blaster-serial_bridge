################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../fsusb/src/usb_core.c \
../fsusb/src/usb_init.c \
../fsusb/src/usb_int.c \
../fsusb/src/usb_mem.c \
../fsusb/src/usb_regs.c \
../fsusb/src/usb_sil.c 

OBJS += \
./fsusb/src/usb_core.o \
./fsusb/src/usb_init.o \
./fsusb/src/usb_int.o \
./fsusb/src/usb_mem.o \
./fsusb/src/usb_regs.o \
./fsusb/src/usb_sil.o 

C_DEPS += \
./fsusb/src/usb_core.d \
./fsusb/src/usb_init.d \
./fsusb/src/usb_int.d \
./fsusb/src/usb_mem.d \
./fsusb/src/usb_regs.d \
./fsusb/src/usb_sil.d 


# Each subdirectory must supply rules for building sources it contributes
fsusb/src/%.o fsusb/src/%.su fsusb/src/%.cyclo: ../fsusb/src/%.c fsusb/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/cmsis" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/cmsis/inc" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/cmsis/stm32" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/cmsis/stm32/inc" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/drv" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/fsusb/inc" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/fsusb/src" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/fsusb" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/src" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/stdperiph" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/stdperiph/inc" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/stdperiph/src" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/sys" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-fsusb-2f-src

clean-fsusb-2f-src:
	-$(RM) ./fsusb/src/usb_core.cyclo ./fsusb/src/usb_core.d ./fsusb/src/usb_core.o ./fsusb/src/usb_core.su ./fsusb/src/usb_init.cyclo ./fsusb/src/usb_init.d ./fsusb/src/usb_init.o ./fsusb/src/usb_init.su ./fsusb/src/usb_int.cyclo ./fsusb/src/usb_int.d ./fsusb/src/usb_int.o ./fsusb/src/usb_int.su ./fsusb/src/usb_mem.cyclo ./fsusb/src/usb_mem.d ./fsusb/src/usb_mem.o ./fsusb/src/usb_mem.su ./fsusb/src/usb_regs.cyclo ./fsusb/src/usb_regs.d ./fsusb/src/usb_regs.o ./fsusb/src/usb_regs.su ./fsusb/src/usb_sil.cyclo ./fsusb/src/usb_sil.d ./fsusb/src/usb_sil.o ./fsusb/src/usb_sil.su

.PHONY: clean-fsusb-2f-src

