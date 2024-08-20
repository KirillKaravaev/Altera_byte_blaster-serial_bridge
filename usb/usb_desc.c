/* Includes ------------------------------------------------------------------*/
#include "usb_lib.h"
#include "usb_desc.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Extern variables ----------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/* USB Standard Device Descriptor */
const uint8_t Blaster_DeviceDescriptor[BLASTER_SIZ_DEVICE_DESC] = {
    0x12,                       /*bLength */
    USB_DEVICE_DESCRIPTOR_TYPE, /*bDescriptorType*/
    0x00,                       /*bcdUSB */
    0x02,
//	0x02,                       /*bDeviceClass*/
    0x00,                       /*bDeviceClass*/
    0x00,                       /*bDeviceSubClass*/
    0x00,                       /*bDeviceProtocol*/
    0x40,                       /*bMaxPacketSize(64bytes)*/
    0xFB,                       /*idVendor (0x09FB=Altera)*/
    0x09,
    0x01,                       /*idProduct(0x6001=USB-Blaster)*/
    0x60,
    0x00,                       /*bcdDevice rel. B*/
    0x04,
    1,                          /*Index of string descriptor describing manufacturer */
    2,                          /*Index of string descriptor describing product*/
    3,                          /*Index of string descriptor describing the device serial number */
    0x01                        /*bNumConfigurations*/
};


/* USB Configuration Descriptor */
/*   All Descriptors (Configuration, Interface, Endpoint, Class, Vendor */
const uint8_t Blaster_ConfigDescriptor[BLASTER_SIZ_CONFIG_DESC] = {
    /* Configuration Descriptor */
    /* 00 */
    0x09,         /* bLength: Configuration Descriptor size */
    USB_CONFIGURATION_DESCRIPTOR_TYPE, /* bDescriptorType: Configuration */
    BLASTER_SIZ_CONFIG_DESC,  /* wTotalLength: Bytes returned */
    0x00,
    0x01,         /* bNumInterfaces: 1 interface */
    0x01,         /* bConfigurationValue: Configuration value */
    0x00,         /* iConfiguration: Index of string descriptor describing the configuration*/
    0x80,         /* bmAttributes: Bus powered(bit6=0) */
    0xE1,         /* MaxPower 450mA(225*2) */

    /* Interface Descriptor */
    /* 09 */
    0x09,         /* bLength: Interface Descriptor size */
    USB_INTERFACE_DESCRIPTOR_TYPE,/* bDescriptorType: Interface descriptor type */
    0x00,         /* bInterfaceNumber: Number of Interface */
    0x00,         /* bAlternateSetting: Alternate setting */
//    EP_NUM - 1,   /* bNumEndpoints */
    0x02,
	0xFF,         /* bInterfaceClass: NA */
    0xFF,         /* bInterfaceSubClass : NA */
    0xFF,         /* nInterfaceProtocol : NA */
    0,            /* iInterface: Index of string descriptor */
    
    /* Endpoint Descriptor */
    /* 18 */
    0x07,          /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE, /* bDescriptorType: Endpoint descriptor */
    EP1_IN,        /* bEndpointAddress: Endpoint 1 IN */
    0x02,          /* bmAttributes: Bulk endpoint */
    ENDP1_TXSIZE,  /* wMaxPacketSize: 64 Bytes max */
    0x00,
    0x01,          /* bInterval: Polling Interval (1 ms) */
    /* 25 */
    0x07,          /* bLength: Endpoint Descriptor size */
    USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint descriptor */
    EP2_OUT,       /* bEndpointAddress: Endpoint 2 OUT */
    0x02,          /* bmAttributes: Bulk endpoint */
    ENDP2_RXSIZE,  /* wMaxPacketSize: 64 Bytes max  */
    0x00,
    0x01,          /* bInterval: Polling Interval (1 ms) */
    /* 32 */
};

	/*----------------------------------Second Device Descriptor(CDC)-----------------------------------------------*/


const uint8_t CDC_DeviceDescriptor[CDC_SIZ_DEVICE_DESC] =
  {
    0x12,   /* bLength */
    USB_DEVICE_DESCRIPTOR_TYPE,     /* bDescriptorType */
    0x00,
    0x02,   /* bcdUSB = 2.00 */
    0x02,   /* bDeviceClass: CDC */
    0x00,   /* bDeviceSubClass */
    0x00,   /* bDeviceProtocol */
    0x40,   /* bMaxPacketSize0 */
    0x83,
    0x04,   /* idVendor = 0x0483 */
    0x40,
    0x57,   /* idProduct = 0x7540 */
    0x00,
    0x02,   /* bcdDevice = 2.00 */
    1,              /* Index of string descriptor describing manufacturer */
    2,              /* Index of string descriptor describing product */
    3,              /* Index of string descriptor describing the device's serial number */
    0x01    /* bNumConfigurations */
  };
/*second configuration for virtual COM port*/
const uint8_t CDC_ConfigDescriptor[CDC_SIZ_CONFIG_DESC] = {

	/* CDC Configuration Descriptor*/
	  0x09,   /* bLength: Configuration Descriptor size */
	  USB_CONFIGURATION_DESCRIPTOR_TYPE,      /* bDescriptorType: Configuration */
	  CDC_SIZ_CONFIG_DESC,                /* wTotalLength:no of returned bytes */
	  0x00,
	  0x02,   /* bNumInterfaces: 2 interface */
	  0x01,   /* bConfigurationValue: Configuration value */
	  0x00,   /* iConfiguration: Index of string descriptor describing the configuration */
	  0xC0,   /* bmAttributes: self powered */
	  0x32,   /* MaxPower 0 mA */
	  /* 9 */

	/*Interface Descriptor */
	  0x09,   /* bLength: Interface Descriptor size */
	  USB_INTERFACE_DESCRIPTOR_TYPE,  /* bDescriptorType: Interface */
	  /* Interface descriptor type */
	  0x00,   /* bInterfaceNumber: Number of Interface */
	  0x00,   /* bAlternateSetting: Alternate setting */
	  0x01,   /* bNumEndpoints: One endpoints used */
	  0x02,   /* bInterfaceClass: Communication Interface Class */
	  0x02,   /* bInterfaceSubClass: Abstract Control Model */
	  0x01,   /* bInterfaceProtocol: Common AT commands */
	  0x00,   /* iInterface: */
	  /* 18 */

	  /*Header Functional Descriptor*/
	  0x05,   /* bLength: Endpoint Descriptor size */
	  0x24,   /* bDescriptorType: CS_INTERFACE */
	  0x00,   /* bDescriptorSubtype: Header Func Desc */
	  0x10,   /* bcdCDC: spec release number */
	  0x01,
	  /* 23 */

	  /*Call Management Functional Descriptor*/
	  0x05,   /* bFunctionLength */
	  0x24,   /* bDescriptorType: CS_INTERFACE */
	  0x01,   /* bDescriptorSubtype: Call Management Func Desc */
	  0x00,   /* bmCapabilities: D0+D1 */
	  0x01,   /* bDataInterface: 1 */
	  /* 28 */

	  /*ACM Functional Descriptor*/
	  0x04,   /* bFunctionLength */
	  0x24,   /* bDescriptorType: CS_INTERFACE */
	  0x02,   /* bDescriptorSubtype: Abstract Control Management desc */
	  0x02,   /* bmCapabilities */
	  /* 32 */

	  /*Union Functional Descriptor*/
	  0x05,   /* bFunctionLength */
	  0x24,   /* bDescriptorType: CS_INTERFACE */
	  0x06,   /* bDescriptorSubtype: Union func desc */
//	  0x01,   /* bMasterInterface: Communication class interface */
//	  0x02,   /* bSlaveInterface0: Data Class Interface */
	  0x00,   /* bMasterInterface: Communication class interface */
	  0x01,   /* bSlaveInterface0: Data Class Interface */
	  /* 37 */

	  /*Endpoint 3 Descriptor*/
	  0x07,                           /* bLength: Endpoint Descriptor size */
	  USB_ENDPOINT_DESCRIPTOR_TYPE,   /* bDescriptorType: Endpoint */
	  EP3_IN,                     /* bEndpointAddress */
	  0x03,                           /* bmAttributes: Interrupt */
	  CDC_CMD_PACKET_SIZE,     /* wMaxPacketSize: */
	  0x00,
	  0xFF,                           /* bInterval: */
	  /* 44 */

	  /*---------------------------------------------------------------------------*/

	  /*Data class interface descriptor*/
	  0x09,   /* bLength: Endpoint Descriptor size */
	  USB_INTERFACE_DESCRIPTOR_TYPE,  /* bDescriptorType: */
	  0x01,   /* bInterfaceNumber: Number of Interface */
	  0x00,   /* bAlternateSetting: Alternate setting */
	  0x02,   /* bNumEndpoints: Two endpoints used */
	  0x0A,   /* bInterfaceClass: CDC */
	  0x00,   /* bInterfaceSubClass: */
	  0x00,   /* bInterfaceProtocol: */
	  0x00,   /* iInterface: */
	  /* 53 */

	  /*Endpoint 1 IN Descriptor*/
	  0x07,   /* bLength: Endpoint Descriptor size */
	  USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType: Endpoint */
	  EP1_IN,                         /* bEndpointAddress */
	  0x02,                              /* bmAttributes: Bulk */
	  ENDP1_TXSIZE,  /* wMaxPacketSize: */
	  0x00,
	  0x00,                               /* bInterval: ignore for Bulk transfer */
	 /* 60 */

	  /*Endpoint 2 OUT Descriptor*/
	  0x07,   /* bLength: Endpoint Descriptor size */
	  USB_ENDPOINT_DESCRIPTOR_TYPE,      /* bDescriptorType: Endpoint */
	  EP2_OUT,                        /* bEndpointAddress */
	  0x02,                              /* bmAttributes: Bulk */
	  ENDP2_RXSIZE,  /* wMaxPacketSize: */
	  0x00,
	  0x00                              /* bInterval: ignore for Bulk transfer */
	  /* 67 */


};

/*------------------------------- USB String Descriptors for blaster (optional)-------------------------------- */

const uint8_t Blaster_StringLangID[BLASTER_SIZ_STRING_LANGID] = {
    BLASTER_SIZ_STRING_LANGID, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    0x09, /* LangID = 0x0409: U.S. English */
    0x04
};

const uint8_t Blaster_StringVendor[BLASTER_SIZ_STRING_VENDOR] = {
    BLASTER_SIZ_STRING_VENDOR, /* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,  /* bDescriptorType*/
    'A', 0, 'l', 0, 't', 0, 'e', 0, 'r', 0, 'a', 0 /* Manufacturer: "Altera" */
};

const uint8_t Blaster_StringProduct[BLASTER_SIZ_STRING_PRODUCT] = {
    BLASTER_SIZ_STRING_PRODUCT,   /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,     /* bDescriptorType */
    'U', 0, 'S', 0, 'B', 0, '-', 0, 'B', 0, 'l', 0, 'a', 0, 's', 0, 't', 0, 'e', 0, 'r', 0  /* "USB-Blaster" */
};

uint8_t Blaster_StringSerial[BLASTER_SIZ_STRING_SERIAL] = {
    BLASTER_SIZ_STRING_SERIAL,    /* bLength */
    USB_STRING_DESCRIPTOR_TYPE,     /* bDescriptorType */
    '0', 0, '0', 0, '0', 0, '0', 0, '0', 0, '0', 0, '0', 0, '0', 0  /* "00000000" */
};

//---------------------------------------/* USB String Descriptors for CDC */-----------------------------------//

const uint8_t CDC_StringLangID[CDC_SIZ_STRING_LANGID] =
  {
    CDC_SIZ_STRING_LANGID,
    USB_STRING_DESCRIPTOR_TYPE,
    0x09,
    0x04 /* LangID = 0x0409: U.S. English */
  };

const uint8_t CDC_StringVendor[CDC_SIZ_STRING_VENDOR] =
  {
    CDC_SIZ_STRING_VENDOR,     						/* Size of Vendor string */
    USB_STRING_DESCRIPTOR_TYPE,             		/* bDescriptorType*/
    /* Manufacturer: "STMicroelectronics" */
    'S', 0, 'T', 0, 'M', 0, 'i', 0, 'c', 0, 'r', 0, 'o', 0, 'e', 0,
    'l', 0, 'e', 0, 'c', 0, 't', 0, 'r', 0, 'o', 0, 'n', 0, 'i', 0,
    'c', 0, 's', 0
  };

const uint8_t CDC_StringProduct[CDC_SIZ_STRING_PRODUCT] =
  {
    CDC_SIZ_STRING_PRODUCT,          				/* bLength */
    USB_STRING_DESCRIPTOR_TYPE,       			 	/* bDescriptorType */
    /* Product name: "STM32 Virtual COM Port" */
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0, ' ', 0, 'V', 0, 'i', 0,
    'r', 0, 't', 0, 'u', 0, 'a', 0, 'l', 0, ' ', 0, 'C', 0, 'O', 0,
    'M', 0, ' ', 0, 'P', 0, 'o', 0, 'r', 0, 't', 0, ' ', 0, ' ', 0
  };

uint8_t CDC_StringSerial[CDC_SIZ_STRING_SERIAL] =
  {
    CDC_SIZ_STRING_SERIAL,           		      	/* bLength */
    USB_STRING_DESCRIPTOR_TYPE,                   	/* bDescriptorType */
    'S', 0, 'T', 0, 'M', 0, '3', 0, '2', 0
  };

