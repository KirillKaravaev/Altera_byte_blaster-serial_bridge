/**
  ******************************************************************************
  * @file    hw_config.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   Hardware Configuration & Setup
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2013 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "usb_prop.h"
#include "stm32_it.h"

////////////////////////////////////
#include "stm32f10x_rcc.h"
#include "stm32f10x_exti.h"
#include "stm32f10x_gpio.h"
#include "misc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define ID1_ADDR        (0x1FFFF7E8)
#define ID2_ADDR        (0x1FFFF7EC)
#define ID3_ADDR        (0x1FFFF7F0)

/* Private variables ---------------------------------------------------------*/
ErrorStatus HSEStartUpStatus;
USART_InitTypeDef USART_InitStructure;
EXTI_InitTypeDef EXTI_InitStructure;
uint8_t  USART_Rx_Buffer [USART_RX_DATA_SIZE];
uint32_t USART_Rx_ptr_in = 0;
uint32_t USART_Rx_ptr_out = 0;
uint32_t USART_Rx_length  = 0;

uint8_t  USB_Tx_State = 0;
/* Extern variables ----------------------------------------------------------*/
extern LINE_CODING linecoding;
/* Private function prototypes -----------------------------------------------*/
static void IntToUnicode(uint32_t value , uint8_t *pbuf , uint8_t len);
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : USB_HW_Config
* Description    : Configures Main system clocks & power.
* Input          : None.
* Return         : None.
*******************************************************************************/
void USB_HW_Config(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
    this is done through SystemInit() function which is called from startup
    file (startup_stm32xxx.s) before to branch to application main.
    To reconfigure the default setting of SystemInit() function, refer to
    system_stm32xxx.c file
    */

    USB_GPIO_Config();
    USB_Interrupts_Config();
    USB_EXTI_Config();
    USB_Clock_Config();
}

/*******************************************************************************
* Function Name  : USB_Clock_Config
* Description    : Configures USB Clock input (48MHz).
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_Clock_Config(void)
{
    /* Select USBCLK source */
    RCC_USBCLKConfig(RCC_USBCLKSource_PLLCLK_1Div5);

    /* Enable the USB clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USB, ENABLE);
}

/*******************************************************************************
* Function Name  : Enter_LowPowerMode.
* Description    : Power-off system clocks and power while entering suspend mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Enter_LowPowerMode(void)
{
    /* Set the device state to suspend */
    bDeviceState = SUSPENDED;
}

/*******************************************************************************
* Function Name  : Leave_LowPowerMode.
* Description    : Restores system clocks and power while exiting suspend mode.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Leave_LowPowerMode(void)
{
    DEVICE_INFO *pInfo = &Device_Info;

    /* Set the device state to the correct state */
    if (pInfo->Current_Configuration != 0) {
        /* Device configured */
        bDeviceState = CONFIGURED;
    } else {
        bDeviceState = ATTACHED;
    }
    //Enable SystemCoreClock
    SystemInit();
}

/*******************************************************************************
* Function Name  : USB_Interrupts_Config.
* Description    : Configures the USB interrupts.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void USB_Interrupts_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;

    /* 2 bit for pre-emption priority, 2 bits for subpriority */
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    /* Enable the USB interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USB_LP_CAN1_RX0_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable the USB Wake-up interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USBWakeUp_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;   //поменял приоритет с 1 на 0
    //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    /* Enable USART Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel = USART_IRQn;			//прерывания висят на 1 юарте
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    //NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


/*******************************************************************************
* Function Name  : USB_Cable_Ctrl.
* Description    : Software Connection/Disconnection of USB Cable.
* Input          : NewState: new state.
* Output         : None.
* Return         : None
*******************************************************************************/
void USB_Cable_Ctrl(FunctionalState NewState)
{
    if (NewState != DISABLE) {
        GPIO_SetBits(GPIOA, GPIO_Pin_15);
    } else {
        GPIO_ResetBits(GPIOA, GPIO_Pin_15);
    }
}

/*******************************************************************************
* Function Name  : USB_GPIO_Config
* Description    : Configures the different GPIO ports.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void USB_GPIO_Config(void)		//Часть функции Set_System() в примере
{
//    GPIO_InitTypeDef GPIO_InitStructure;
//
//    /* Enable the USB disconnect GPIO clock */
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
//
//    /* PA15 used as USB pull-up */
//    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
//    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name : USB_EXTI_Config.
* Description   : Configure the EXTI lines for Key and Tamper push buttons.
* Input         : None.
* Output        : None.
* Return value  : The direction value.
*******************************************************************************/
void USB_EXTI_Config(void)    	//Часть функции Set_System() в примере
{
    EXTI_InitTypeDef EXTI_InitStructure;

    /* Configure the EXTI line 18 connected internally to the USB IP */
    EXTI_ClearITPendingBit(EXTI_Line18);
    EXTI_InitStructure.EXTI_Line = EXTI_Line18;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);
}

/*******************************************************************************
* Function Name  :  USART_Config_Default.
* Description    :  configure the EVAL_COM1 with default values.
* Input          :  None.
* Return         :  None.
*******************************************************************************/
void USART_Config_Default(void)
{
  /* EVAL_COM1 default configuration */
  /* EVAL_COM1 configured as follow:
        - BaudRate = 9600 baud
        - Word Length = 8 Bits
        - One Stop Bit
        - Parity Odd
        - Hardware flow control disabled
        - Receive and transmit enabled
  */
  USART_InitStructure.USART_BaudRate = 9600;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_Odd;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure and enable the USART -- переписанная STM_EVAL_COMInit */
  STM_USART_Init(&USART_InitStructure);

  /* Enable the USART Receive interrupt */
  USART_ITConfig(USART, USART_IT_RXNE, ENABLE);
}

/*******************************************************************************
* Function Name  :  USART_Config.
* Description    :  Configure the EVAL_COM1 according to the line coding structure.
* Input          :  None.
* Return         :  Configuration status
                    TRUE : configuration done with success
                    FALSE : configuration aborted.
*******************************************************************************/
bool USART_Config(void)
{

  /* set the Stop bit*/
  switch (linecoding.format)
  {
    case 0:
      USART_InitStructure.USART_StopBits = USART_StopBits_1;
      break;
    case 1:
      USART_InitStructure.USART_StopBits = USART_StopBits_1_5;
      break;
    case 2:
      USART_InitStructure.USART_StopBits = USART_StopBits_2;
      break;
    default :
    {
      USART_Config_Default();
      return (FALSE);
    }
  }

  /* set the parity bit*/
  switch (linecoding.paritytype)
  {
    case 0:
      USART_InitStructure.USART_Parity = USART_Parity_No;
      break;
    case 1:
      USART_InitStructure.USART_Parity = USART_Parity_Even;
      break;
    case 2:
      USART_InitStructure.USART_Parity = USART_Parity_Odd;
      break;
    default :
    {
      USART_Config_Default();
      return (FALSE);
    }
  }

  /*set the data type : only 8bits and 9bits is supported */
  switch (linecoding.datatype)
  {
    case 0x07:
      /* With this configuration a parity (Even or Odd) should be set */
      USART_InitStructure.USART_WordLength = USART_WordLength_8b;
      break;
    case 0x08:
      if (USART_InitStructure.USART_Parity == USART_Parity_No)
      {
        USART_InitStructure.USART_WordLength = USART_WordLength_8b;
      }
      else
      {
        USART_InitStructure.USART_WordLength = USART_WordLength_9b;
      }

      break;
    default :
    {
      USART_Config_Default();
      return (FALSE);
    }
  }

  USART_InitStructure.USART_BaudRate = linecoding.bitrate;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

  /* Configure and enable the USART */
  STM_USART_Init(&USART_InitStructure);

  return (TRUE);
}

/*******************************************************************************
* Function Name  : USB_To_USART_Send_Data.
* Description    : send the received data from USB to the UART 0.
* Input          : data_buffer: data address.
                   Nb_bytes: number of bytes to send.
* Return         : none.
*******************************************************************************/
void USB_To_USART_Send_Data(uint8_t* data_buffer, uint8_t Nb_bytes)
{

  uint32_t i;

  for (i = 0; i < Nb_bytes; i++)
  {
    USART_SendData(USART, *(data_buffer + i));
    /* Wait until end of transmit one byte */
    while(USART_GetFlagStatus(USART, USART_FLAG_TXE) == RESET);
    /* After it move to next byte */
  }
}

/*******************************************************************************
* Function Name  : Handle_USBAsynchXfer.
* Description    : send data to USB.
* Input          : None.
* Return         : none.
*******************************************************************************/
void Handle_USBAsynchXfer (void)
{

  uint16_t USB_Tx_ptr;
  uint16_t USB_Tx_length;

  if(USB_Tx_State != 1)
  {
    if (USART_Rx_ptr_out == USART_RX_DATA_SIZE)
    {
      USART_Rx_ptr_out = 0;
    }

    if(USART_Rx_ptr_out == USART_Rx_ptr_in)
    {
      USB_Tx_State = 0;
      return;
    }

    if(USART_Rx_ptr_out > USART_Rx_ptr_in) /* rollback */
    {
      USART_Rx_length = USART_RX_DATA_SIZE - USART_Rx_ptr_out;
    }
    else
    {
      USART_Rx_length = USART_Rx_ptr_in - USART_Rx_ptr_out;
    }

    if (USART_Rx_length > CDC_DATA_SIZE)
    {
      USB_Tx_ptr = USART_Rx_ptr_out;
      USB_Tx_length = CDC_DATA_SIZE;

      USART_Rx_ptr_out += CDC_DATA_SIZE;
      USART_Rx_length -= CDC_DATA_SIZE;
    }
    else
    {
      USB_Tx_ptr = USART_Rx_ptr_out;
      USB_Tx_length = USART_Rx_length;

      USART_Rx_ptr_out += USART_Rx_length;
      USART_Rx_length = 0;
    }
    USB_Tx_State = 1;
    UserToPMABufferCopy(&USART_Rx_Buffer[USB_Tx_ptr], ENDP1_TXADDR, USB_Tx_length);
    SetEPTxCount(ENDP1, USB_Tx_length);
    SetEPTxValid(ENDP1);
  }

}
/*******************************************************************************
* Function Name  : UART_To_USB_Send_Data.
* Description    : send the received data from UART to USB.
* Input          : None.
* Return         : none.
*******************************************************************************/
void USART_To_USB_Send_Data(void)
{

  if (linecoding.datatype == 7)
  {
    USART_Rx_Buffer[USART_Rx_ptr_in] = USART_ReceiveData(USART) & 0x7F;
  }
  else if (linecoding.datatype == 8)
  {
    USART_Rx_Buffer[USART_Rx_ptr_in] = USART_ReceiveData(USART);
  }

  USART_Rx_ptr_in++;

  /* To avoid buffer overflow */
  if(USART_Rx_ptr_in == USART_RX_DATA_SIZE)
  {
    USART_Rx_ptr_in = 0;
  }
}

/*******************************************************************************
* Function Name  : STM_USART_Init.
* Description    : Configures USART (RX,TX,CLK, others)
* Input          : USART_InitStruct: pointer to a USART_InitTypeDef structure that
*   			   contains the configuration information for the specified USART peripheral.
* Output         : None.
* Return         : None.
*******************************************************************************/
/*-------------------------------------- переписанная STM_EVAL_COMInit ------------------------------------------*/
/*Для начала рассмотрим общую последовательность действий, необходимых для запуска USART в STM32F4 и
настройки его для работы в качестве приемника:

	--Работаем с тактированием – включаем тактирование приемо-передатчика, а заодно и тактирование порта,
	который отвечает за ножки Rx/Tx.
	--Сначала настраиваем нужные ножки микроконтроллера, а затем и сам USART.
	--Включаем прерывания – функция NVIC_EnableIRQ() и запускаем USART - USART_Cmd().
	--Наконец включаем прерывание, которое нам в данном случае понадобится, то есть прерывание по приему
	данных - для этого нам пригодится функция USART_ITConfig().
Ссылка - https://microtechnics.ru/programmirovanie-stm32f4-usart-priem-dannyx/
Еще про usart https://we.easyelectronics.ru/STM32/uart-usart-na-stm32l-stm32.html
*/
void STM_USART_Init(USART_InitTypeDef* USART_InitStruct){
//Подробнее про настройку - в примере SPL USART_Interrupt/main.c

	  GPIO_InitTypeDef GPIO_InitStructure;

//	  /* Enable GPIO clock */
//	  RCC_AHBPeriphClockCmd(USART_TX_RX_GPIO_CLK, ENABLE);

	  /* Enable GPIO clock */
	  RCC_APB2PeriphClockCmd(USART_TX_RX_GPIO_PORT, ENABLE);

	  /* Enable USART clock */
#ifdef USART_1
	  RCC_APB2PeriphClockCmd(USART_CLK, ENABLE);
#else
	  RCC_APB1PeriphClockCmd(USART_CLK, ENABLE);
#endif


//Как будто для f103 этого делать не нужно
//	  /* Connect PXx to USARTx_Tx */
//	  GPIO_PinAFConfig(USART_TX_RX_GPIO_PORT, USART_TX_GPIO_SOURCE, COM_TX_AF[COM]);
//
//	  /* Connect PXx to USARTx_Rx */
//	  GPIO_PinAFConfig(USART_TX_RX_GPIO_PORT, USART_RX_GPIO_SOURCE, COM_RX_AF[COM]);

	  /* Configure USART Tx as alternate function push-pull */
	  GPIO_InitStructure.GPIO_Pin = USART_TX_PIN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
//	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_Init(USART_TX_RX_GPIO_PORT, &GPIO_InitStructure);

	  /* Configure USART Rx as alternate function push-pull */
	  GPIO_InitStructure.GPIO_Pin = USART_RX_PIN;
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	  GPIO_Init(USART_TX_RX_GPIO_PORT, &GPIO_InitStructure);

	  /* USART configuration */
	  USART_Init(USART, USART_InitStruct);

	  /* Enable USART */
	  USART_Cmd(USART, ENABLE);


  }

/*******************************************************************************
* Function Name  : Get_SerialNum.
* Description    : Create the serial number string descriptor.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Get_SerialNum(void)
{
    uint32_t Device_Serial0, Device_Serial1, Device_Serial2;

    Device_Serial0 = *(uint32_t *)ID1_ADDR;
    Device_Serial1 = *(uint32_t *)ID2_ADDR;
    Device_Serial2 = *(uint32_t *)ID3_ADDR;

    Device_Serial0 += Device_Serial1;
    Device_Serial0 += Device_Serial2;

    if (Device_Serial0 != 0) {
        IntToUnicode(Device_Serial0, &Blaster_StringSerial[2], 8);
    }
}

/*******************************************************************************
* Function Name  : HexToChar.
* Description    : Convert Hex 32Bits value into char.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
static void IntToUnicode(uint32_t value , uint8_t *pbuf , uint8_t len)
{
    uint8_t idx = 0;

    for (idx = 0 ; idx < len ; idx ++) {
        if (((value >> 28)) < 0xA) {
            pbuf[ 2 * idx] = (value >> 28) + '0';
        } else {
            pbuf[2 * idx] = (value >> 28) + 'A' - 10;
        }

        value = value << 4;

        pbuf[ 2 * idx + 1] = 0;
    }
}




/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
