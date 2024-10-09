# stm32_altera_usb_blaster
Port of https://github.com/Icenowy/USB-Blaster-GCC to Stm32CubeIDE

Чтобы поменять частоту, нужно в папке cmsis/stm32/inc/stm32f10x.h поменять строку #define HSE_VALUE в
соответствии с установленным кварцем, а также в sys/system_stm32f10x.с поменять SYSCLK_FREQ_XXMHz,
добавить elsif и написать свою функцию SetSysClockToXX, поменяв в ней строку
 RCC->CFGR |= (uint32_t)(RCC_CFGR_PLLSRC_HSE | RCC_CFGR_PLLMULL7); , где нужно выбрать свой множитель
RCC_CFGR_PLLMULL7 так, чтобы частота после умножения на него HSE была не более 72 Мгц, иначе USB не заработает,
так как для него максимальная частота 48 Мгц и максимальный делитель от PLLCLK равен 1.5 (он же установлен). 
(Сказанное справедливо для микроконтроллеров stm32f103, у gd32f103 максимальная частота и значения множителей
другие)
