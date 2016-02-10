#include "librpi.h"

/**
 * Timer
 */

static rpi_timer_t *rpi_timer = (rpi_timer_t *)RPI_TIMER;

rpi_timer_t *rpi_get_timer() {
	return rpi_timer;
}

void rpi_sleep_us(uint32_t us) {
	volatile uint32_t ts = rpi_timer->counter_lo;
	while ((rpi_timer->counter_lo - ts) < us) {
		// nop
	}
}
