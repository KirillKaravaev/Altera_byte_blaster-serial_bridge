################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../stdperiph/src/misc.c \
../stdperiph/src/stm32f10x_adc.c \
../stdperiph/src/stm32f10x_bkp.c \
../stdperiph/src/stm32f10x_can.c \
../stdperiph/src/stm32f10x_cec.c \
../stdperiph/src/stm32f10x_crc.c \
../stdperiph/src/stm32f10x_dac.c \
../stdperiph/src/stm32f10x_dbgmcu.c \
../stdperiph/src/stm32f10x_dma.c \
../stdperiph/src/stm32f10x_exti.c \
../stdperiph/src/stm32f10x_flash.c \
../stdperiph/src/stm32f10x_fsmc.c \
../stdperiph/src/stm32f10x_gpio.c \
../stdperiph/src/stm32f10x_i2c.c \
../stdperiph/src/stm32f10x_iwdg.c \
../stdperiph/src/stm32f10x_pwr.c \
../stdperiph/src/stm32f10x_rcc.c \
../stdperiph/src/stm32f10x_rtc.c \
../stdperiph/src/stm32f10x_sdio.c \
../stdperiph/src/stm32f10x_spi.c \
../stdperiph/src/stm32f10x_tim.c \
../stdperiph/src/stm32f10x_usart.c \
../stdperiph/src/stm32f10x_wwdg.c 

OBJS += \
./stdperiph/src/misc.o \
./stdperiph/src/stm32f10x_adc.o \
./stdperiph/src/stm32f10x_bkp.o \
./stdperiph/src/stm32f10x_can.o \
./stdperiph/src/stm32f10x_cec.o \
./stdperiph/src/stm32f10x_crc.o \
./stdperiph/src/stm32f10x_dac.o \
./stdperiph/src/stm32f10x_dbgmcu.o \
./stdperiph/src/stm32f10x_dma.o \
./stdperiph/src/stm32f10x_exti.o \
./stdperiph/src/stm32f10x_flash.o \
./stdperiph/src/stm32f10x_fsmc.o \
./stdperiph/src/stm32f10x_gpio.o \
./stdperiph/src/stm32f10x_i2c.o \
./stdperiph/src/stm32f10x_iwdg.o \
./stdperiph/src/stm32f10x_pwr.o \
./stdperiph/src/stm32f10x_rcc.o \
./stdperiph/src/stm32f10x_rtc.o \
./stdperiph/src/stm32f10x_sdio.o \
./stdperiph/src/stm32f10x_spi.o \
./stdperiph/src/stm32f10x_tim.o \
./stdperiph/src/stm32f10x_usart.o \
./stdperiph/src/stm32f10x_wwdg.o 

C_DEPS += \
./stdperiph/src/misc.d \
./stdperiph/src/stm32f10x_adc.d \
./stdperiph/src/stm32f10x_bkp.d \
./stdperiph/src/stm32f10x_can.d \
./stdperiph/src/stm32f10x_cec.d \
./stdperiph/src/stm32f10x_crc.d \
./stdperiph/src/stm32f10x_dac.d \
./stdperiph/src/stm32f10x_dbgmcu.d \
./stdperiph/src/stm32f10x_dma.d \
./stdperiph/src/stm32f10x_exti.d \
./stdperiph/src/stm32f10x_flash.d \
./stdperiph/src/stm32f10x_fsmc.d \
./stdperiph/src/stm32f10x_gpio.d \
./stdperiph/src/stm32f10x_i2c.d \
./stdperiph/src/stm32f10x_iwdg.d \
./stdperiph/src/stm32f10x_pwr.d \
./stdperiph/src/stm32f10x_rcc.d \
./stdperiph/src/stm32f10x_rtc.d \
./stdperiph/src/stm32f10x_sdio.d \
./stdperiph/src/stm32f10x_spi.d \
./stdperiph/src/stm32f10x_tim.d \
./stdperiph/src/stm32f10x_usart.d \
./stdperiph/src/stm32f10x_wwdg.d 


# Each subdirectory must supply rules for building sources it contributes
stdperiph/src/%.o stdperiph/src/%.su stdperiph/src/%.cyclo: ../stdperiph/src/%.c stdperiph/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis/stm32" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/cmsis/stm32/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/drv" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/fsusb/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/fsusb/src" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/fsusb" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/src" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/stdperiph" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/stdperiph/inc" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/stdperiph/src" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/sys" -I"D:/Program/STM32/Altera blaster + COM - port/Altera_byte_blaster-serial_bridge/usb" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-stdperiph-2f-src

clean-stdperiph-2f-src:
	-$(RM) ./stdperiph/src/misc.cyclo ./stdperiph/src/misc.d ./stdperiph/src/misc.o ./stdperiph/src/misc.su ./stdperiph/src/stm32f10x_adc.cyclo ./stdperiph/src/stm32f10x_adc.d ./stdperiph/src/stm32f10x_adc.o ./stdperiph/src/stm32f10x_adc.su ./stdperiph/src/stm32f10x_bkp.cyclo ./stdperiph/src/stm32f10x_bkp.d ./stdperiph/src/stm32f10x_bkp.o ./stdperiph/src/stm32f10x_bkp.su ./stdperiph/src/stm32f10x_can.cyclo ./stdperiph/src/stm32f10x_can.d ./stdperiph/src/stm32f10x_can.o ./stdperiph/src/stm32f10x_can.su ./stdperiph/src/stm32f10x_cec.cyclo ./stdperiph/src/stm32f10x_cec.d ./stdperiph/src/stm32f10x_cec.o ./stdperiph/src/stm32f10x_cec.su ./stdperiph/src/stm32f10x_crc.cyclo ./stdperiph/src/stm32f10x_crc.d ./stdperiph/src/stm32f10x_crc.o ./stdperiph/src/stm32f10x_crc.su ./stdperiph/src/stm32f10x_dac.cyclo ./stdperiph/src/stm32f10x_dac.d ./stdperiph/src/stm32f10x_dac.o ./stdperiph/src/stm32f10x_dac.su ./stdperiph/src/stm32f10x_dbgmcu.cyclo ./stdperiph/src/stm32f10x_dbgmcu.d ./stdperiph/src/stm32f10x_dbgmcu.o ./stdperiph/src/stm32f10x_dbgmcu.su ./stdperiph/src/stm32f10x_dma.cyclo ./stdperiph/src/stm32f10x_dma.d ./stdperiph/src/stm32f10x_dma.o ./stdperiph/src/stm32f10x_dma.su ./stdperiph/src/stm32f10x_exti.cyclo ./stdperiph/src/stm32f10x_exti.d ./stdperiph/src/stm32f10x_exti.o ./stdperiph/src/stm32f10x_exti.su ./stdperiph/src/stm32f10x_flash.cyclo ./stdperiph/src/stm32f10x_flash.d ./stdperiph/src/stm32f10x_flash.o ./stdperiph/src/stm32f10x_flash.su ./stdperiph/src/stm32f10x_fsmc.cyclo ./stdperiph/src/stm32f10x_fsmc.d ./stdperiph/src/stm32f10x_fsmc.o ./stdperiph/src/stm32f10x_fsmc.su ./stdperiph/src/stm32f10x_gpio.cyclo ./stdperiph/src/stm32f10x_gpio.d ./stdperiph/src/stm32f10x_gpio.o ./stdperiph/src/stm32f10x_gpio.su ./stdperiph/src/stm32f10x_i2c.cyclo ./stdperiph/src/stm32f10x_i2c.d ./stdperiph/src/stm32f10x_i2c.o ./stdperiph/src/stm32f10x_i2c.su ./stdperiph/src/stm32f10x_iwdg.cyclo ./stdperiph/src/stm32f10x_iwdg.d ./stdperiph/src/stm32f10x_iwdg.o ./stdperiph/src/stm32f10x_iwdg.su ./stdperiph/src/stm32f10x_pwr.cyclo ./stdperiph/src/stm32f10x_pwr.d ./stdperiph/src/stm32f10x_pwr.o ./stdperiph/src/stm32f10x_pwr.su ./stdperiph/src/stm32f10x_rcc.cyclo ./stdperiph/src/stm32f10x_rcc.d ./stdperiph/src/stm32f10x_rcc.o ./stdperiph/src/stm32f10x_rcc.su ./stdperiph/src/stm32f10x_rtc.cyclo ./stdperiph/src/stm32f10x_rtc.d ./stdperiph/src/stm32f10x_rtc.o ./stdperiph/src/stm32f10x_rtc.su ./stdperiph/src/stm32f10x_sdio.cyclo ./stdperiph/src/stm32f10x_sdio.d ./stdperiph/src/stm32f10x_sdio.o ./stdperiph/src/stm32f10x_sdio.su ./stdperiph/src/stm32f10x_spi.cyclo ./stdperiph/src/stm32f10x_spi.d ./stdperiph/src/stm32f10x_spi.o ./stdperiph/src/stm32f10x_spi.su ./stdperiph/src/stm32f10x_tim.cyclo ./stdperiph/src/stm32f10x_tim.d ./stdperiph/src/stm32f10x_tim.o ./stdperiph/src/stm32f10x_tim.su ./stdperiph/src/stm32f10x_usart.cyclo ./stdperiph/src/stm32f10x_usart.d ./stdperiph/src/stm32f10x_usart.o ./stdperiph/src/stm32f10x_usart.su ./stdperiph/src/stm32f10x_wwdg.cyclo ./stdperiph/src/stm32f10x_wwdg.d ./stdperiph/src/stm32f10x_wwdg.o ./stdperiph/src/stm32f10x_wwdg.su

.PHONY: clean-stdperiph-2f-src

