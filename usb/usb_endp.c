/* Includes ------------------------------------------------------------------*/
#include "base.h"
#include "hw_config.h"
#include "usb_lib.h"
#include "usb_istr.h"


#include "usb_desc.h"
#include "usb_mem.h"
#include "usb_pwr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Interval between sending IN packets in frame number (1 frame = 1ms) */
#define VCOMPORT_IN_FRAME_INTERVAL             5

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
uint8_t USB_Rx_Buffer[CDC_DATA_SIZE];
extern  uint8_t USART_Rx_Buffer[];
extern uint32_t USART_Rx_ptr_out;
extern uint32_t USART_Rx_length;
extern uint8_t  USB_Tx_State;

extern __IO BOOL g_blaster_rx_req;
extern __IO BOOL g_blaster_tx_ready;

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*--------------------------------------------EP for Blaster--------------------------------------------------*/

/*******************************************************************************
* Function Name  : EP2_OUT_Callback.
* Description    : EP2 OUT Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
//void EP2_OUT_Callback(void)
//{
//    g_blaster_rx_req = TRUE;
//}



/*******************************************************************************
* Function Name  : EP1_IN_Callback.
* Description    : EP1 IN Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP1_IN_Callback(void)
{
if(SetupPin){
		uint16_t USB_Tx_ptr;
		  uint16_t USB_Tx_length;

		  if (USB_Tx_State == 1)
		  {
		    if (USART_Rx_length == 0)
		    {
		      USB_Tx_State = 0;
		    }
		    else
		    {
		      if (USART_Rx_length > CDC_DATA_SIZE){
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
		      UserToPMABufferCopy(&USART_Rx_Buffer[USB_Tx_ptr], ENDP1_TXADDR, USB_Tx_length);
		      SetEPTxCount(ENDP1, USB_Tx_length);
		      SetEPTxValid(ENDP1);
		    }
		  }

}
else{
	g_blaster_tx_ready = TRUE;
}

}

/*--------------------------------------------EP for CDC--------------------------------------------------------*/

/*******************************************************************************
* Function Name  : EP3_IN_Callback.
* Description    : EP3 IN Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/

//void EP3_IN_Callback(void)
//{
//	uint16_t USB_Tx_ptr;
//	  uint16_t USB_Tx_length;
//
//	  if (USB_Tx_State == 1)
//	  {
//	    if (USART_Rx_length == 0)
//	    {
//	      USB_Tx_State = 0;
//	    }
//	    else
//	    {
//	      if (USART_Rx_length > CDC_DATA_SIZE){
//	        USB_Tx_ptr = USART_Rx_ptr_out;
//	        USB_Tx_length = CDC_DATA_SIZE;
//
//	        USART_Rx_ptr_out += CDC_DATA_SIZE;
//	        USART_Rx_length -= CDC_DATA_SIZE;
//	      }
//	      else
//	      {
//	        USB_Tx_ptr = USART_Rx_ptr_out;
//	        USB_Tx_length = USART_Rx_length;
//
//	        USART_Rx_ptr_out += USART_Rx_length;
//	        USART_Rx_length = 0;
//	      }
//	      UserToPMABufferCopy(&USART_Rx_Buffer[USB_Tx_ptr], ENDP3_TXADDR, USB_Tx_length);
//	      SetEPTxCount(ENDP3, USB_Tx_length);
//	      SetEPTxValid(ENDP3);
//	    }
//	  }
//
//}

/*******************************************************************************
* Function Name  : EP4_OUT_Callback.
* Description    : EP4 OUT Callback Routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/

//void EP4_OUT_Callback(void)
//{
//	uint16_t USB_Rx_Cnt;
//
//	  /* Get the received data buffer and update the counter */
//	  USB_Rx_Cnt = USB_SIL_Read(EP4_OUT, USB_Rx_Buffer);
//
//	  /* USB data will be immediately processed, this allow next USB traffic being
//	  NAKed till the end of the USART Xfer */
//
//	  USB_To_USART_Send_Data(USB_Rx_Buffer, USB_Rx_Cnt);
//
//	  /* Enable the receive of data on EP4 */
//	  SetEPRxValid(ENDP4);
//}

/*******************************************************************************
* Function Name  : EP3_OUT_Callback
* Description    :
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void EP2_OUT_Callback(void)
{
if(SetupPin){
	uint16_t USB_Rx_Cnt;

  /* Get the received data buffer and update the counter */
  USB_Rx_Cnt = USB_SIL_Read(EP2_OUT, USB_Rx_Buffer);

  /* USB data will be immediately processed, this allow next USB traffic being
  NAKed till the end of the USART Xfer */

  USB_To_USART_Send_Data(USB_Rx_Buffer, USB_Rx_Cnt);

  /* Enable the receive of data on EP3 */
  SetEPRxValid(ENDP2);
}
else{
	g_blaster_rx_req = TRUE;
}
}


/*******************************************************************************
* Function Name  : SOF_Callback / INTR_SOFINTR_Callback
* Description    : Start Of Frame Callback Routine
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void SOF_Callback(void)
{
  static uint32_t FrameCount = 0;

  if(bDeviceState == CONFIGURED)
  {
    if (FrameCount++ == VCOMPORT_IN_FRAME_INTERVAL)
    {
      /* Reset the frame counter */
      FrameCount = 0;

      /* Check the data to be sent through IN pipe */
      Handle_USBAsynchXfer();
    }
  }
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
