/**
  ******************************************************************************
  * @file    usb_prop.c
  * @author  MCD Application Team
  * @version V4.0.0
  * @date    21-January-2013
  * @brief   All processings related to USB Blaster
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
#include "usb_conf.h"
#include "usb_prop.h"
#include "usb_desc.h"
#include "usb_pwr.h"
#include "ft245rom.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

uint8_t Request = 0;

LINE_CODING linecoding =
  {
    115200, /* baud rate*/
    0x00,   /* stop bits-1*/
    0x00,   /* parity - none*/
    0x08    /* no. of bits 8*/
  };

static uint8_t s_Report_Buf[2];

/* -------------------------------------------------------------------------- */
/*  Structures initializations */
/* -------------------------------------------------------------------------- */

DEVICE Device_Table = {
    EP_NUM,
    1
};

DEVICE_PROP Device_Property = {
    Device_Init,
    Device_Reset,
    Device_Status_In,
    Device_Status_Out,
	Device_Data_Setup,
	Device_NoData_Setup,
	Device_Get_Interface_Setting,
	Device_GetDeviceDescriptor,
	Device_GetConfigDescriptor,
	Device_GetStringDescriptor,
    0,
    ENDP0_SIZE /*MAX PACKET SIZE*/
};

USER_STANDARD_REQUESTS User_Standard_Requests = {
	Device_GetConfiguration,
	Device_SetConfiguration,
	Device_GetInterface,
	Device_SetInterface,
	Device_GetStatus,
	Device_ClearFeature,
	Device_SetEndPointFeature,
	Device_SetDeviceFeature,
	Device_SetDeviceAddress
};

/*------------------------------------------Blaster Descriptors--------------------------------------------------------*/

ONE_DESCRIPTOR Blaster_Device_Descriptor = {
	(uint8_t *)Blaster_DeviceDescriptor,
    BLASTER_SIZ_DEVICE_DESC
};


ONE_DESCRIPTOR Blaster_Config_Descriptor = {
    (uint8_t *)Blaster_ConfigDescriptor,
    BLASTER_SIZ_CONFIG_DESC
};

ONE_DESCRIPTOR Blaster_String_Descriptor[4] = {
    {(uint8_t *)Blaster_StringLangID, BLASTER_SIZ_STRING_LANGID},
    {(uint8_t *)Blaster_StringVendor, BLASTER_SIZ_STRING_VENDOR},
    {(uint8_t *)Blaster_StringProduct, BLASTER_SIZ_STRING_PRODUCT},
    {(uint8_t *)Blaster_StringSerial, BLASTER_SIZ_STRING_SERIAL}
};

/*------------------------------------------CDC Descriptors-----------------------------------------------------*/

ONE_DESCRIPTOR CDC_Device_Descriptor = {
	(uint8_t *)CDC_DeviceDescriptor,
    CDC_SIZ_DEVICE_DESC
};

ONE_DESCRIPTOR CDC_Config_Descriptor = {
	(uint8_t *)CDC_ConfigDescriptor,
	CDC_SIZ_CONFIG_DESC
};

ONE_DESCRIPTOR CDC_String_Descriptor[4] = {
    {(uint8_t *)CDC_StringLangID, CDC_SIZ_STRING_LANGID},
    {(uint8_t *)CDC_StringVendor, CDC_SIZ_STRING_VENDOR},
    {(uint8_t *)CDC_StringProduct, CDC_SIZ_STRING_PRODUCT},
    {(uint8_t *)CDC_StringSerial, CDC_SIZ_STRING_SERIAL}
};

/*--------------------------------------------------------------------------------------------------------------*/



/* Extern variables ----------------------------------------------------------*/
extern uint8_t SetupPin;
/* Private function prototypes -----------------------------------------------*/
uint8_t *Blaster_Get_VendorData(uint16_t Length);
uint8_t *CDC_GetLineCoding(uint16_t Length);
uint8_t *CDC_SetLineCoding(uint16_t Length);
/* Extern function prototypes ------------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*******************************************************************************
* Function Name  : Blaster_Init.
* Description    : Blaster init routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Device_Init(void)
{
    /* Update the serial number string descriptor with the data from the unique ID*/
    Get_SerialNum();

    pInformation->Current_Configuration = 0;

    /* Connect the device */
    PowerOn();

    /* Perform basic device initialization operations */
    USB_SIL_Init();

    ft245rom_init();

    	USART_Config_Default();

    bDeviceState = UNCONNECTED;
}

/*******************************************************************************
* Function Name  : Blaster_Reset.
* Description    : Blaster reset routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Device_Reset(void)
{
    /* Set the device as not configured */
    pInformation->Current_Configuration = 0;
    pInformation->Current_Interface = 0;/*the default Interface*/

    /* Current Feature initialization */
//    pInformation->Current_Feature = Blaster_ConfigDescriptor[7];
    pInformation->Current_Feature = SetupPin ? CDC_ConfigDescriptor[7] : Blaster_ConfigDescriptor[7];

    SetBTABLE(BTABLE_ADDRESS);

    /* Initialize Endpoint 0 */
    SetEPType(ENDP0, EP_CONTROL);

    if(SetupPin)
    	SetEPTxStatus(ENDP0, EP_TX_STALL);
    else
    	SetEPTxStatus(ENDP0, EP_TX_NAK);

    SetEPRxAddr(ENDP0, ENDP0_RXADDR);
    SetEPTxAddr(ENDP0, ENDP0_TXADDR);
    Clear_Status_Out(ENDP0);
    SetEPRxCount(ENDP0, Device_Property.MaxPacketSize);
    SetEPRxValid(ENDP0);

/*-------------------------------------------------ENDPOINTS FOR BLASTER-----------------------------------------*/

    /* Initialize Endpoint 1 as BULK IN */
    SetEPType(ENDP1, EP_BULK);
    SetEPTxAddr(ENDP1, ENDP1_TXADDR);
    if(SetupPin){
    }
    else{
    	SetEPTxCount(ENDP1, ENDP1_TXSIZE);
    }
    SetEPTxStatus(ENDP1, EP_TX_NAK);
    SetEPRxStatus(ENDP1, EP_RX_DIS);

    /* Initialize Endpoint 2 as INTERRUPT */
    SetEPType(ENDP2, EP_INTERRUPT);
    SetEPTxAddr(ENDP2, ENDP2_TXADDR);
    SetEPRxStatus(ENDP2, EP_RX_DIS);
    SetEPTxStatus(ENDP2, EP_TX_NAK);

    /* Initialize Endpoint 3 as BULK OUT */
    SetEPType(ENDP3, EP_BULK);
    if(SetupPin){
    	SetEPRxAddr(ENDP3, ENDP3_RXADDR0);
    	SetEPRxCount(ENDP3, CDC_DATA_SIZE);
    }
    else{
    	SetEPDoubleBuff(ENDP3);
    	SetEPDblBuffAddr(ENDP3, ENDP3_RXADDR0, ENDP3_RXADDR1);
    	SetEPDblBuffCount(ENDP3, EP_DBUF_OUT, ENDP3_RXSIZE);
    	ClearDTOG_RX(ENDP3);
    	ClearDTOG_TX(ENDP3);
    	ToggleDTOG_TX(ENDP3);
    }
    SetEPRxStatus(ENDP3, EP_RX_VALID);
    SetEPTxStatus(ENDP3, EP_TX_DIS);



/*-------------------------------------------------ENDPOINTS FOR CDC-------------------------------------------*/
    
//    /* Initialize Endpoint 3 as BULK IN */
//    SetEPType(ENDP3, EP_BULK);
//    SetEPTxAddr(ENDP3, ENDP3_TXADDR);
//    SetEPTxStatus(ENDP3, EP_TX_NAK);
//    SetEPRxStatus(ENDP3, EP_RX_DIS);
//
//    /* Initialize Endpoint 4 as BULK OUT */
//    SetEPType(ENDP4, EP_BULK);
//    SetEPRxAddr(ENDP4, ENDP4_RXADDR);
//    SetEPRxCount(ENDP4, CDC_DATA_SIZE);
//    SetEPRxStatus(ENDP4, EP_RX_VALID);
//    SetEPTxStatus(ENDP4, EP_TX_DIS);
//
//    /* Initialize Endpoint 5 as INTERRUPT IN */
//    SetEPType(ENDP5, EP_INTERRUPT);
//    SetEPTxAddr(ENDP5, ENDP5_TXADDR);
//    SetEPRxStatus(ENDP5, EP_RX_DIS);
//    SetEPTxStatus(ENDP5, EP_TX_NAK);


    /* Set the device to response on default address */
    SetDeviceAddress(0);

    bDeviceState = ATTACHED;
}

/*******************************************************************************
* Function Name  : Blaster_SetConfiguration.
* Description    : Update the device state to configured and command the ADC
*                  conversion.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Device_SetConfiguration(void)
{
    if (pInformation->Current_Configuration != 0) {
        /* Device configured */
        bDeviceState = CONFIGURED;
    }
}

/*******************************************************************************
* Function Name  : Blaster_SetConfiguration.
* Description    : Update the device state to addressed.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Device_SetDeviceAddress(void)
{
    bDeviceState = ADDRESSED;
}

/*******************************************************************************
* Function Name  : Blaster_Status_In.
* Description    : Blaster status IN routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Device_Status_In(void)
{
	if (Request == SET_LINE_CODING)
	  {
	    USART_Config();
	    Request = 0;
	  }
	return;
}

/*******************************************************************************
* Function Name  : Blaster_Status_Out
* Description    : Blaster status OUT routine.
* Input          : None.
* Output         : None.
* Return         : None.
*******************************************************************************/
void Device_Status_Out(void)
{
    return;
}

/*******************************************************************************
* Function Name  : Blaster_Data_Setup
* Description    : Handle the data class specific requests.
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT Device_Data_Setup(uint8_t RequestNo)
{
    uint8_t *(*CopyRoutine)(uint16_t);
    uint8_t addr;

    CopyRoutine = NULL;
/*------------------------------------------CDC DATA SETUP-----------------------------------------------------*/
if(SetupPin){

	if (RequestNo == GET_LINE_CODING)
	  {
	    if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
	    {
	      CopyRoutine = CDC_GetLineCoding;
	    }
	  }
	  else if (RequestNo == SET_LINE_CODING)
	  {
	    if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
	    {
	      CopyRoutine = CDC_SetLineCoding;
	    }
	    Request = SET_LINE_CODING;
	  }

	  if (CopyRoutine == NULL)
	  {
	    return USB_UNSUPPORT;
	  }

}   //if end
/*-----------------------------------------Blaster DATA SETUP---------------------------------------------------*/
else{
    // emulate ft245
    if (Type_Recipient == (VENDOR_REQUEST | DEVICE_RECIPIENT)) {
        if (pInformation->USBbmRequestType & 0x80) {
            // device -> host
            switch (RequestNo) {
            case FTDI_VEN_REQ_RD_EEPROM:
                addr = ((pInformation->USBwIndex >> 8) & 0x3F) << 1;
                s_Report_Buf[0] = ft245rom_read(addr);
                s_Report_Buf[1] = ft245rom_read(addr + 1);
                CopyRoutine = Blaster_Get_VendorData;
                break;
            case FTDI_VEN_REQ_GET_MODEM_STA:
                // return fixed modem status
                s_Report_Buf[0] = FTDI_MODEM_STA_DUMMY0;
                s_Report_Buf[1] = FTDI_MODEM_STA_DUMMY1;
                CopyRoutine = Blaster_Get_VendorData;
                break;
            default:
                // return dummy data
                s_Report_Buf[0] = 0x0;
                s_Report_Buf[1] = 0x0;
                CopyRoutine = Blaster_Get_VendorData;
                break;
            }
        } else {
            return USB_UNSUPPORT;
        }
    }

    if (CopyRoutine == NULL) {
        return USB_UNSUPPORT;
    }

}    //else end

/*---------------------------------------------------------------------------------------------------------------*/

    pInformation->Ctrl_Info.CopyData = CopyRoutine;
    pInformation->Ctrl_Info.Usb_wOffset = 0;
    (*CopyRoutine)(0);
    
    return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Blaster_NoData_Setup
* Description    : handle the no data class specific requests
* Input          : Request Nb.
* Output         : None.
* Return         : USB_UNSUPPORT or USB_SUCCESS.
*******************************************************************************/
RESULT Device_NoData_Setup(uint8_t RequestNo)
{
/*------------------------------------------CDC NoDATA SETUP-----------------------------------------------------*/
if(SetupPin){
	if (Type_Recipient == (CLASS_REQUEST | INTERFACE_RECIPIENT))
	  {
	    if (RequestNo == SET_COMM_FEATURE)
	    {
	      return USB_SUCCESS;
	    }
	    else if (RequestNo == SET_CONTROL_LINE_STATE)
	    {
	      return USB_SUCCESS;
	    }
	  }
}
/*----------------------------------------BLASTER NoDATA SETUP-----------------------------------------------------*/
else{
	if ((Type_Recipient == (VENDOR_REQUEST | DEVICE_RECIPIENT))) {
        switch (RequestNo) {
        case FTDI_VEN_REQ_RESET:
            break;
        case FTDI_VEN_REQ_SET_BAUDRATE:
            break;
        case FTDI_VEN_REQ_SET_DATA_CHAR:
            break;
        case FTDI_VEN_REQ_SET_FLOW_CTRL:
            break;
        case FTDI_VEN_REQ_SET_MODEM_CTRL:
            break;
        default:
            break;
        }
        return USB_SUCCESS;
    }

}

    return USB_UNSUPPORT;
}

/*******************************************************************************
* Function Name  : Blaster_GetDeviceDescriptor.
* Description    : Gets the device descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the device descriptor.
*******************************************************************************/
uint8_t *Device_GetDeviceDescriptor(uint16_t Length)  //Отправляем дескриптор устройства в ответ на запрос хоста(ПК)
{
    if(SetupPin) { 	//Проверяем высокий уровень на настроечном пине PA1.
													//При 1 отправляем дескипторы CDC, иначе - дескрипторы blaster
    	return Standard_GetDescriptorData(Length, &CDC_Device_Descriptor);
    }
	return Standard_GetDescriptorData(Length, &Blaster_Device_Descriptor);
}

/*******************************************************************************
* Function Name  : Blaster_GetConfigDescriptor.
* Description    : Gets the configuration descriptor.
* Input          : Length
* Output         : None.
* Return         : The address of the configuration descriptor.
*******************************************************************************/
uint8_t *Device_GetConfigDescriptor(uint16_t Length)	//Отправляем дескриптор конфигурации в ответ на запрос хоста(ПК)
{
	if(SetupPin) {	//Проверяем высокий уровень на настроечном пине PA1.
													//При 1 отправляем дескипторы CDC, иначе - дескрипторы blaster
	    return Standard_GetDescriptorData(Length, &CDC_Config_Descriptor);
	}
    return Standard_GetDescriptorData(Length, &Blaster_Config_Descriptor);
}

/*******************************************************************************
* Function Name  : Blaster_GetStringDescriptor
* Description    : Gets the string descriptors according to the needed index
* Input          : Length
* Output         : None.
* Return         : The address of the string descriptors.
*******************************************************************************/
uint8_t *Device_GetStringDescriptor(uint16_t Length)
{
    uint8_t wValue0 = pInformation->USBwValue0;
    
    if (wValue0 > 4) {
        return NULL;
    } else if(SetupPin){ 	//В зависимости от состояния пина отправляем тот или иной дескриптор
        return Standard_GetDescriptorData(Length, &CDC_String_Descriptor[wValue0]);
    } else {
    	return Standard_GetDescriptorData(Length, &Blaster_String_Descriptor[wValue0]);
    }
}

/*******************************************************************************
* Function Name  : Blaster_Get_Interface_Setting.
* Description    : tests the interface and the alternate setting according to the
*                  supported one.
* Input          : - Interface : interface number.
*                  - AlternateSetting : Alternate Setting number.
* Output         : None.
* Return         : USB_SUCCESS or USB_UNSUPPORT.
*******************************************************************************/
RESULT Device_Get_Interface_Setting(uint8_t Interface, uint8_t AlternateSetting)
{
    if (AlternateSetting > 0) {
        return USB_UNSUPPORT;
//    } else if (Interface > 0) {
      } else if (Interface > 1) {
        return USB_UNSUPPORT;
    }
    
    return USB_SUCCESS;
}

/*******************************************************************************
* Function Name  : Blaster_Get_VendorData.
* Description    : send the Vendor Data to the PC host.
* Input          : Length.
* Output         : None.
* Return         : Vendor Data base address.
*******************************************************************************/
uint8_t *Blaster_Get_VendorData(uint16_t Length)
{
    if (Length == 0) {
        pInformation->Ctrl_Info.Usb_wLength = sizeof(s_Report_Buf);
        return NULL;
    }
    
    return (uint8_t *)s_Report_Buf;
}

/*******************************************************************************
* Function Name  : Virtual_Com_Port_GetLineCoding.
* Description    : send the linecoding structure to the PC host.
* Input          : Length.
* Output         : None.
* Return         : Linecoding structure base address.
*******************************************************************************/
uint8_t *CDC_GetLineCoding(uint16_t Length)
{
	if (Length == 0)
	{
		pInformation->Ctrl_Info.Usb_wLength = sizeof(linecoding);
		return NULL;
	}
	return(uint8_t *)&linecoding;
}

/*******************************************************************************
* Function Name  : Virtual_Com_Port_SetLineCoding.
* Description    : Set the linecoding structure fields.
* Input          : Length.
* Output         : None.
* Return         : Linecoding structure base address.
*******************************************************************************/
uint8_t *CDC_SetLineCoding(uint16_t Length)
{
	if (Length == 0)
	{
		pInformation->Ctrl_Info.Usb_wLength = sizeof(linecoding);
		return NULL;
	}
	return(uint8_t *)&linecoding;
}

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
