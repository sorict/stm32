#include <stdint.h>

struct systick {

	volatile uint32_t CTRL;
	volatile uint32_t LOAD;
	volatile uint32_t VAL;
	volatile uint32_t CALIB;
};

struct systick *tick_reg = (struct systick *)0xE000E010;

static inline void systick_init(uint32_t ticks) {

	tick_reg->LOAD = ticks-1;
	tick_reg->VAL = 0;
	tick_reg->CTRL |= 0b111;
	rcc_reg->APB2ENR |= (1 << 11);
}
