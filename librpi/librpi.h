#ifndef LIBRPI_H__
#define LIBRPI_H__

#include <stdint.h>

/**
 * Base
 */

#ifdef RPI2
	#define PERIPHERAL_BASE	0x3F000000UL
#else
	#define PERIPHERAL_BASE	0x20000000UL
#endif

typedef volatile uint32_t rpi_reg_rw_t;

static inline void rpi_mmio_write(uint32_t reg, uint32_t data) {
	*(rpi_reg_rw_t *)reg = data;
}

static inline uint32_t rpi_mmio_read(uint32_t reg) {
	return *(rpi_reg_rw_t *)reg;
}

/**
 * GPIO
 */

#define GPIO_BASE (PERIPHERAL_BASE + 0x200000)

/**
 * Timer
 */

#define RPI_TIMER (PERIPHERAL_BASE + 0x003000)

typedef struct {
	rpi_reg_rw_t control_status;
	rpi_reg_rw_t counter_lo;
	rpi_reg_rw_t counter_hi;
	rpi_reg_rw_t compare0;
	rpi_reg_rw_t compare1;
	rpi_reg_rw_t compare2;
	rpi_reg_rw_t compare3;
} rpi_timer_t;

rpi_timer_t *rpi_get_timer();
void rpi_sleep_us(uint32_t us);


#endif
