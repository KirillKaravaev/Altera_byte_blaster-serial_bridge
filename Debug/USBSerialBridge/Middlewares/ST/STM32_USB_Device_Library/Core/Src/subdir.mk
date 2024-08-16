################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.c \
../USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.c \
../USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.c 

OBJS += \
./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.o \
./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.o \
./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.o 

C_DEPS += \
./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.d \
./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.d \
./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.d 


# Each subdirectory must supply rules for building sources it contributes
USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.o USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.su USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.cyclo: ../USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/%.c USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/cmsis" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/cmsis/inc" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/cmsis/stm32" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/cmsis/stm32/inc" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/drv" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/fsusb/inc" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/fsusb/src" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/fsusb" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/src" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/stdperiph" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/stdperiph/inc" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/stdperiph/src" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/sys" -I"D:/Program/STM32/usb-blaster_files/stm32_altera_usb_blaster-main/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-USBSerialBridge-2f-Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Core-2f-Src

clean-USBSerialBridge-2f-Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Core-2f-Src:
	-$(RM) ./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.cyclo ./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.d ./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.o ./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_core.su ./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.cyclo ./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.d ./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.o ./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ctlreq.su ./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.cyclo ./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.d ./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.o ./USBSerialBridge/Middlewares/ST/STM32_USB_Device_Library/Core/Src/usbd_ioreq.su

.PHONY: clean-USBSerialBridge-2f-Middlewares-2f-ST-2f-STM32_USB_Device_Library-2f-Core-2f-Src

