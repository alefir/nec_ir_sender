/*
 * dumb_delay.h
 *
 *  Created on: Mar 8, 2021
 *      Author: alefir
 */

#ifndef INC_NEC_IR_DRIVER_H_
#define INC_NEC_IR_DRIVER_H_

#include <stdint.h>
#include "main.h"

#define NEC_SHORT_PULSE 18000U
#define NEC_LONG_PULSE 54000U
#define NEC_USEC_TO_CYCLES 32

void nec_delay(uint32_t delay);
void nec_send_code(uint8_t, uint8_t, uint8_t);

#endif /* INC_NEC_IR_DRIVER_H_ */
