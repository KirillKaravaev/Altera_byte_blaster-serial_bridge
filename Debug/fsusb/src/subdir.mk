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
../fsusb/src/usb_sil.c \
../fsusb/src/usbd_core.c \
../fsusb/src/usbd_int.c \
../fsusb/src/usbd_std.c \
../fsusb/src/usbh_core.c \
../fsusb/src/usbh_ctrl.c \
../fsusb/src/usbh_hcs.c \
../fsusb/src/usbh_int.c \
../fsusb/src/usbh_std.c 

OBJS += \
./fsusb/src/usb_core.o \
./fsusb/src/usb_init.o \
./fsusb/src/usb_int.o \
./fsusb/src/usb_mem.o \
./fsusb/src/usb_regs.o \
./fsusb/src/usb_sil.o \
./fsusb/src/usbd_core.o \
./fsusb/src/usbd_int.o \
./fsusb/src/usbd_std.o \
./fsusb/src/usbh_core.o \
./fsusb/src/usbh_ctrl.o \
./fsusb/src/usbh_hcs.o \
./fsusb/src/usbh_int.o \
./fsusb/src/usbh_std.o 

C_DEPS += \
./fsusb/src/usb_core.d \
./fsusb/src/usb_init.d \
./fsusb/src/usb_int.d \
./fsusb/src/usb_mem.d \
./fsusb/src/usb_regs.d \
./fsusb/src/usb_sil.d \
./fsusb/src/usbd_core.d \
./fsusb/src/usbd_int.d \
./fsusb/src/usbd_std.d \
./fsusb/src/usbh_core.d \
./fsusb/src/usbh_ctrl.d \
./fsusb/src/usbh_hcs.d \
./fsusb/src/usbh_int.d \
./fsusb/src/usbh_std.d 


# Each subdirectory must supply rules for building sources it contributes
fsusb/src/%.o fsusb/src/%.su fsusb/src/%.cyclo: ../fsusb/src/%.c fsusb/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis/stm32" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis/stm32/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/drv" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/fsusb/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/fsusb/src" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/fsusb" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/src" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/stdperiph" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/stdperiph/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/stdperiph/src" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/sys" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-fsusb-2f-src

clean-fsusb-2f-src:
	-$(RM) ./fsusb/src/usb_core.cyclo ./fsusb/src/usb_core.d ./fsusb/src/usb_core.o ./fsusb/src/usb_core.su ./fsusb/src/usb_init.cyclo ./fsusb/src/usb_init.d ./fsusb/src/usb_init.o ./fsusb/src/usb_init.su ./fsusb/src/usb_int.cyclo ./fsusb/src/usb_int.d ./fsusb/src/usb_int.o ./fsusb/src/usb_int.su ./fsusb/src/usb_mem.cyclo ./fsusb/src/usb_mem.d ./fsusb/src/usb_mem.o ./fsusb/src/usb_mem.su ./fsusb/src/usb_regs.cyclo ./fsusb/src/usb_regs.d ./fsusb/src/usb_regs.o ./fsusb/src/usb_regs.su ./fsusb/src/usb_sil.cyclo ./fsusb/src/usb_sil.d ./fsusb/src/usb_sil.o ./fsusb/src/usb_sil.su ./fsusb/src/usbd_core.cyclo ./fsusb/src/usbd_core.d ./fsusb/src/usbd_core.o ./fsusb/src/usbd_core.su ./fsusb/src/usbd_int.cyclo ./fsusb/src/usbd_int.d ./fsusb/src/usbd_int.o ./fsusb/src/usbd_int.su ./fsusb/src/usbd_std.cyclo ./fsusb/src/usbd_std.d ./fsusb/src/usbd_std.o ./fsusb/src/usbd_std.su ./fsusb/src/usbh_core.cyclo ./fsusb/src/usbh_core.d ./fsusb/src/usbh_core.o ./fsusb/src/usbh_core.su ./fsusb/src/usbh_ctrl.cyclo ./fsusb/src/usbh_ctrl.d ./fsusb/src/usbh_ctrl.o ./fsusb/src/usbh_ctrl.su ./fsusb/src/usbh_hcs.cyclo ./fsusb/src/usbh_hcs.d ./fsusb/src/usbh_hcs.o ./fsusb/src/usbh_hcs.su ./fsusb/src/usbh_int.cyclo ./fsusb/src/usbh_int.d ./fsusb/src/usbh_int.o ./fsusb/src/usbh_int.su ./fsusb/src/usbh_std.cyclo ./fsusb/src/usbh_std.d ./fsusb/src/usbh_std.o ./fsusb/src/usbh_std.su

.PHONY: clean-fsusb-2f-src

