#include "defines.h"
#include <usbh_cdc.h>


static USBH_StatusTypeDef USBH_CDC_InterfaceInit(USBH_HandleTypeDef *) { return USBH_OK; };
static USBH_StatusTypeDef USBH_CDC_InterfaceDeInit(USBH_HandleTypeDef *) { return USBH_OK; };
static USBH_StatusTypeDef USBH_CDC_ClassRequest(USBH_HandleTypeDef *) { return USBH_OK; };
static USBH_StatusTypeDef USBH_CDC_Process(USBH_HandleTypeDef *) { return USBH_OK; };
static USBH_StatusTypeDef USBH_CDC_SOFProcess(USBH_HandleTypeDef *) { return USBH_OK; };


USBH_ClassTypeDef  CDC_Class =
{
    "CDC",
    USB_CDC_CLASS,
    USBH_CDC_InterfaceInit,
    USBH_CDC_InterfaceDeInit,
    USBH_CDC_ClassRequest,
    USBH_CDC_Process,
    USBH_CDC_SOFProcess,
    NULL
};
