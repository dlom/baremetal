#include <stddef.h>
#include <stdint.h>

#define GPIO_BASE 0x20200000
#define RPI_TIMER 0x20003000

static inline void mmio_write(uint32_t reg, uint32_t data) {
	*(volatile uint32_t *)reg = data;
}

static inline uint32_t mmio_read(uint32_t reg) {
	return *(volatile uint32_t *)reg;
}

void kernel_wait(uint32_t us) {
	volatile uint32_t ts = mmio_read(RPI_TIMER + 0x20);
	while ((mmio_read(RPI_TIMER + 0x20) - ts) < us) {
		// nop
	}
}

void initialize_led() {
	volatile uint32_t led_init = mmio_read(GPIO_BASE + 0x20);
	led_init |= (1 << 18);
	mmio_write(GPIO_BASE + 0x020, led_init);
}

void led_on() {
	mmio_write(GPIO_BASE + 0x160, (1 << 16));
}

void led_off() {
	mmio_write(GPIO_BASE + 0x0e0, (1 << 16));
}

void kernel_main() {
	initialize_led();

	while (1) {
		kernel_wait(500000);
		led_on();
		kernel_wait(500000);
		led_off();
	}
}
