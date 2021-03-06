/*****************************************************************************
 * @file    ble_const.h
 * @author  MCD Application Team
 * @brief   This file contains the definitions which are compiler dependent.
 *****************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2019 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under Ultimate Liberty license
 * SLA0044, the "License"; You may not use this file except in compliance with
 * the License. You may obtain a copy of the License at:
 *                             www.st.com/SLA0044
 *
 ******************************************************************************
 */

#ifndef BLE_CONST_H__
#define BLE_CONST_H__


#include "hal_types.h"
#include "ble_defs.h"


/* Return status */
#define BLE_STATUS_SUCCESS             (0x00)
#define BLE_STATUS_ERROR               (0x47)
#define BLE_STATUS_TIMEOUT             (0xFF)


/* Size of command/events buffers:
 *
 * To change the size of commands and events parameters used in the
 * auto-generated files, you need to update 2 defines:
 *
 *  - BLE_CMD_MAX_PARAM_LEN          
 *  - BLE_EVT_MAX_PARAM_LEN          
 *
 * These 2 defines are set below with default values and can be changed.
 *
 * To compute the value to support a characteristic of 512 bytes for a specific
 * command or an event, you need to look in "ble_types.h".
 *
 * Here are 2 examples, one with a command and one with an event:
 *
 * - aci_gatt_update_char_value_ext_cp0
 *   ----------------------------------
 *
 *   we have in the structure:
 *
 *      uint8_t Value[(BLE_CMD_MAX_PARAM_LEN- 12)/sizeof(uint8_t)];
 *
 *   so to support a 512 byte value, we need to have
 *
 *   BLE_CMD_MAX_PARAM_LEN at least equal to: 512 + 12 = 524
 *
 * - aci_gatt_read_handle_value_rp0
 *   ------------------------------
 *
 *   we have in the structure:
 *
 *     uint8_t Value[((BLE_EVT_MAX_PARAM_LEN - 3) - 5)/sizeof(uint8_t)];
 *
 *   so to support a 512 byte value, we need to have
 *
 *   BLE_EVT_MAX_PARAM_LEN at least equal to: 512 + 3 + 5 = 520
 *
 * If you need several events or commands with 512-size values, you need to
 * take the maximum values for BLE_EVT_MAX_PARAM_LEN and BLE_CMD_MAX_PARAM_LEN.
 *
 */

/* Maximum parameter size of BLE commands.
 * Change this value if needed. */
#define BLE_CMD_MAX_PARAM_LEN          HCI_COMMAND_MAX_PARAM_LEN

/* Maximum parameter size of BLE responses/events.
 * Change this value if needed. */
#define BLE_EVT_MAX_PARAM_LEN          HCI_EVENT_MAX_PARAM_LEN


/* Callback function to send command and receive response */
struct hci_request
{
  uint16_t ogf;
  uint16_t ocf;
  int      event;
  void*    cparam;
  int      clen;
  void*    rparam;
  int      rlen;
};
extern int hci_send_req( struct hci_request* req, BOOL async );


/* Byte order conversions */
#define htob( d, n )  (d)     /* LE */
#define btoh( d, n )  (d)     /* LE */


#endif /* ! BLE_CONST_H__ */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE***/
