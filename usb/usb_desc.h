/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __USB_DESC_H
#define __USB_DESC_H

/* Includes ------------------------------------------------------------------*/
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported define -----------------------------------------------------------*/

#define USB_DEVICE_DESCRIPTOR_TYPE              0x01
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02
#define USB_STRING_DESCRIPTOR_TYPE              0x03
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05

#define CDC_DATA_SIZE              				64
#define CDC_INT_SIZE               				8

#define BLASTER_SIZ_DEVICE_DESC                 18

#define CDC_SIZ_DEVICE_DESC                 	18 							//

#define BLASTER_SIZ_CONFIG_DESC                 32
//#define BLASTER_SIZ_CONFIG_DESC                 55
//#define BLASTER_SIZ_CONFIG_DESC                 sizeof (Blaster_ConfigDescriptor)
//#define BLASTER_SIZ_CONFIG_DESC					90
#define CDC_SIZ_CONFIG_DESC						67

#define BLASTER_SIZ_STRING_LANGID               4
#define BLASTER_SIZ_STRING_VENDOR               14
#define BLASTER_SIZ_STRING_PRODUCT              24
#define BLASTER_SIZ_STRING_SERIAL               18

#define CDC_SIZ_STRING_LANGID               	4
#define CDC_SIZ_STRING_VENDOR               	38
#define CDC_SIZ_STRING_PRODUCT              	50
#define CDC_SIZ_STRING_SERIAL               	26

/* Exported functions ------------------------------------------------------- */

extern const uint8_t Blaster_DeviceDescriptor[BLASTER_SIZ_DEVICE_DESC];
extern const uint8_t CDC_DeviceDescriptor[CDC_SIZ_DEVICE_DESC];				//Второй дескриптор устройства

extern const uint8_t Blaster_ConfigDescriptor[BLASTER_SIZ_CONFIG_DESC];
extern const uint8_t CDC_ConfigDescriptor[CDC_SIZ_CONFIG_DESC];				//second configuration for CDC device

/*-------------------------------------------------Дескрипторы строк для blaster----------------------------------*/

extern const uint8_t Blaster_StringLangID[BLASTER_SIZ_STRING_LANGID];
extern const uint8_t Blaster_StringVendor[BLASTER_SIZ_STRING_VENDOR];
extern const uint8_t Blaster_StringProduct[BLASTER_SIZ_STRING_PRODUCT];
extern uint8_t Blaster_StringSerial[BLASTER_SIZ_STRING_SERIAL];

/*-------------------------------------------------Дескрипторы строк для CDC--------------------------------------*/

extern const uint8_t CDC_StringLangID[CDC_SIZ_STRING_LANGID];
extern const uint8_t CDC_StringVendor[CDC_SIZ_STRING_VENDOR];
extern const uint8_t CDC_StringProduct[CDC_SIZ_STRING_PRODUCT];
extern uint8_t CDC_StringSerial[CDC_SIZ_STRING_SERIAL];

#endif /* __USB_DESC_H */

