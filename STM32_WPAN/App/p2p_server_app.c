/**
 ******************************************************************************
 * File Name          : App/p2p_server_app.c
 * Description        : P2P Server Application
 ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */
#include "main.h"
#include "app_common.h"
#include "dbg_trace.h"
#include "ble.h"
#include "p2p_server_app.h"
#include "scheduler.h"
void P2PS_STM_App_Notification(P2PS_STM_App_Notification_evt_t *pNotification)
{
  switch(pNotification->P2P_Evt_Opcode)
  {

    case P2PS_STM__NOTIFY_ENABLED_EVT:
      break;

    case P2PS_STM_NOTIFY_DISABLED_EVT:
      break;

    case P2PS_STM_WRITE_EVT:; /* if a new bluetooth event is a write event from the client with a payload */
    	uint8_t payload = pNotification->DataTransfered.pPayload[1]; /* grab the command byte of the payload */
    	nec_send_code(0x00, 0x00, payload); /* transmit the command byte
    	                                       NOTE: the LED strip that I am controlling does not read the
    	                                       address bytes, only the command byte. This is why the low
    	                                       and high address bytes (or address and ~address for classic
    	                                       NEC) are hardcoded to 0x00. */
      break;

    default:
      break;
  }
  return;
}

void P2PS_APP_Notification(P2PS_APP_ConnHandle_Not_evt_t *pNotification)
{
  switch(pNotification->P2P_Evt_Opcode)
  {
  case PEER_CONN_HANDLE_EVT :
    break;

    case PEER_DISCON_HANDLE_EVT:
    break;

    default:
      break;
  }
  return;
}

void P2PS_APP_Init(void)
{
  return;
}
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
