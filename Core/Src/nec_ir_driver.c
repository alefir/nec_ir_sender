/*
 * nec_ir_driver.c
 *
 *  Created on: Mar 8, 2021
 *      Author: alefir
 */

#include <nec_ir_driver.h>

/*
 * @brief assembly fuckery to delay for CPU cycles
 * @param delay number of cycles to delay for
 */
void nec_delay(uint32_t delay) {
	register int R0 __asm("r0");
	R0 = delay / 3;
	__asm("dloop:");
	__asm("subs r0, r0, #1");
	__asm("bne dloop");
}

void nec_send_bom(void) {
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	nec_delay(9000 * NEC_USEC_TO_CYCLES);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	nec_delay(4500 * NEC_USEC_TO_CYCLES);
}

void nec_send_bom_no_carrier(void) {
	HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_SET);
	nec_delay(9000 * NEC_USEC_TO_CYCLES);
	HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_RESET);
	nec_delay(4500 * NEC_USEC_TO_CYCLES);
}

void nec_send_code(uint8_t addr_low, uint8_t addr_high, uint8_t cmd) {
	/* send beginning of message marker */
	nec_send_bom();

	const uint8_t nec_ir_power_addr_high = addr_high;
	const uint8_t nec_ir_power_addr_low = addr_low;
	const uint8_t nec_ir_power_comd = cmd;

	for (int i = 0; i < 8; i++) {
		/* cycle through bits of message and set LED accordingly */
		if ( (nec_ir_power_addr_low >> i) & 0x01 ) {
			HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
			nec_delay(NEC_SHORT_PULSE);
			HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
			nec_delay(NEC_LONG_PULSE);
		} else {
			HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
			nec_delay(NEC_SHORT_PULSE);
			HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
			nec_delay(NEC_SHORT_PULSE);
		}
	}

	for (int i = 0; i < 8; i++) {
		/* cycle through bits of message and set LED accordingly */
		if ( ((nec_ir_power_addr_high) >> i) & 0x01 ) {
			HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
			nec_delay(NEC_SHORT_PULSE);
			HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
			nec_delay(NEC_LONG_PULSE);
		} else {
			HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
			nec_delay(NEC_SHORT_PULSE);
			HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
			nec_delay(NEC_SHORT_PULSE);
		}
	}

	for (int i = 0; i < 8; i++) {
		/* cycle through bits of message and set LED accordingly */
		if ( (nec_ir_power_comd >> i) & 0x01 ) {
			HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
			nec_delay(NEC_SHORT_PULSE);
			HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
			nec_delay(NEC_LONG_PULSE);
		} else {
			HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
			nec_delay(NEC_SHORT_PULSE);
			HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
			nec_delay(NEC_SHORT_PULSE);
		}
	}

	for (int i = 0; i < 8; i++) {
		/* cycle through bits of message and set LED accordingly */
		if ( ((~nec_ir_power_comd) >> i) & 0x01 ) {
			HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
			nec_delay(NEC_SHORT_PULSE);
			HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
			nec_delay(NEC_LONG_PULSE);
		} else {
			HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
			nec_delay(NEC_SHORT_PULSE);
			HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
			nec_delay(NEC_SHORT_PULSE);
		}
	}


	/* send end of message marker */
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	nec_delay(NEC_SHORT_PULSE);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
}

void nec_send_code_no_carrier(uint8_t addr_low, uint8_t addr_high, uint8_t cmd) {
	/* send beginning of message marker */
	nec_send_bom_no_carrier();

	const uint8_t nec_ir_power_addr_high = addr_high;
	const uint8_t nec_ir_power_addr_low = addr_low;
	const uint8_t nec_ir_power_comd = cmd;

	for (int i = 0; i < 8; i++) {
		/* cycle through bits of message and set LED accordingly */
		if ( (nec_ir_power_addr_low >> i) & 0x01 ) {
			HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_SET);
			nec_delay(NEC_SHORT_PULSE);
			HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_RESET);
			nec_delay(NEC_LONG_PULSE);
		} else {
			HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_SET);
			nec_delay(NEC_SHORT_PULSE);
			HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_RESET);
			nec_delay(NEC_SHORT_PULSE);
		}
	}

	for (int i = 0; i < 8; i++) {
		/* cycle through bits of message and set LED accordingly */
		if ( ((nec_ir_power_addr_high) >> i) & 0x01 ) {
			HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_SET);
			nec_delay(NEC_SHORT_PULSE);
			HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_RESET);
			nec_delay(NEC_LONG_PULSE);
		} else {
			HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_SET);
			nec_delay(NEC_SHORT_PULSE);
			HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_RESET);
			nec_delay(NEC_SHORT_PULSE);
		}
	}

	for (int i = 0; i < 8; i++) {
		/* cycle through bits of message and set LED accordingly */
		if ( (nec_ir_power_comd >> i) & 0x01 ) {
			HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_SET);
			nec_delay(NEC_SHORT_PULSE);
			HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_RESET);
			nec_delay(NEC_LONG_PULSE);
		} else {
			HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_SET);
			nec_delay(NEC_SHORT_PULSE);
			HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_RESET);
			nec_delay(NEC_SHORT_PULSE);
		}
	}

	for (int i = 0; i < 8; i++) {
		/* cycle through bits of message and set LED accordingly */
		if ( ((~nec_ir_power_comd) >> i) & 0x01 ) {
			HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_SET);
			nec_delay(NEC_SHORT_PULSE);
			HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_RESET);
			nec_delay(NEC_LONG_PULSE);
		} else {
			HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_SET);
			nec_delay(NEC_SHORT_PULSE);
			HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_RESET);
			nec_delay(NEC_SHORT_PULSE);
		}
	}


	/* send end of message marker */
	HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_SET);
	nec_delay(NEC_SHORT_PULSE);
	HAL_GPIO_WritePin(LED_EXT_GPIO_Port, LED_EXT_Pin, GPIO_PIN_RESET);
}
