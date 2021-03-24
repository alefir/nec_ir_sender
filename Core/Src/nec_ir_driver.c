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
	/* This function is dumb. I could not for the life of me find an actual
	 * system function that allows for the sub-millisecond delays that I need
	 * for NEC timing. The HAL driver only provides a delay of integer milliseconds,
	 * I'm guessing because the RTOS runs on a 1ms tick. There's probably a more
	 * proper way of doing this, but I like that I can now say I've now used ASM
	 * outside of a classroom.
	 */
	register int R0 __asm("r0");
	R0 = delay / 3; /* divide by 2 because 2 instruction cycles per loop,
	                   then multiplied by 2/3 because my oscilloscope read
	                   all of the NEC timings running 33% slow, due to what
	                   I believe is scheduling overhead from the RTOS */
	__asm("dloop:");
	__asm("subs r0, r0, #1");
	__asm("bne dloop");
}

void nec_send_code(uint8_t addr_low, uint8_t addr_high, uint8_t cmd) {
	/* send beginning of message marker */
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	nec_delay(9000 * NEC_USEC_TO_CYCLES);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	nec_delay(4500 * NEC_USEC_TO_CYCLES);

	for (int i = 0; i < 8; i++) {
		/* cycle through bits of lower byte of address and set LED accordingly */
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		nec_delay(NEC_SHORT_PULSE);
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
		if ( (addr_low >> i) & 0x01 ) { /* data is sent LSB first */
			nec_delay(NEC_LONG_PULSE);
		} else {
			nec_delay(NEC_SHORT_PULSE);
		}
	}

	for (int i = 0; i < 8; i++) {
		/* cycle through bits of upper byte of address and set LED accordingly */
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		nec_delay(NEC_SHORT_PULSE);
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
		if ( ((addr_high) >> i) & 0x01 ) { /* data is sent LSB first */
			nec_delay(NEC_LONG_PULSE);
		} else {
			nec_delay(NEC_SHORT_PULSE);
		}
	}

	for (int i = 0; i < 8; i++) {
		/* cycle through bits of command byte and set LED accordingly */
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		nec_delay(NEC_SHORT_PULSE);
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
		if ( (cmd >> i) & 0x01 ) { /* data is sent LSB first */
			nec_delay(NEC_LONG_PULSE);
		} else {
			nec_delay(NEC_SHORT_PULSE);
		}
	}

	for (int i = 0; i < 8; i++) {
		/* cycle through bits of logical inverse of command byte and set LED accordingly */
		HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
		nec_delay(NEC_SHORT_PULSE);
		HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
		if ( ((~cmd) >> i) & 0x01 ) { /* data is sent LSB first */
			nec_delay(NEC_LONG_PULSE);
		} else {
			nec_delay(NEC_SHORT_PULSE);
		}
	}

	/* send end of message marker */
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	nec_delay(NEC_SHORT_PULSE);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
}
