#include <stddef.h>
#include "librpi/librpi.h"

void kernel_wait(uint32_t ms) {
	rpi_sleep_us(ms * 1000);
}

void initialize_led() {
	uint32_t led_init = rpi_mmio_read(GPIO_BASE + sizeof(uint32_t));
	led_init |= (1 << 18);
	rpi_mmio_write(GPIO_BASE + sizeof(uint32_t), led_init);
}

void led_on() {
	rpi_mmio_write(GPIO_BASE + (sizeof(uint32_t) * 10), (1 << 16));
}

void led_off() {
	rpi_mmio_write(GPIO_BASE + (sizeof(uint32_t) *  7), (1 << 16));
}

void kernel_main() {
	initialize_led();

	while (1) {
		kernel_wait(500);
		led_on();
		kernel_wait(500);
		led_off();
	}
}
