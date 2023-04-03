#ifndef PLL_H_
#define PLL_H_

#include "gpio.h"

static inline void apb2_pll_clk_init_36MHz() {
	
	rcc_reg->CFGR |=  (0x7 << 24);
	rcc_reg->CFGR |= (0x7 << 18);
	rcc_reg->CFGR |= (0x2 << 0);
	rcc_reg->CFGR |= (0x0 << 4);
	rcc_reg->CFGR |= (0b00 << 11);
	rcc_reg->CR |= (1 << 24);
	while(!(rcc_reg->CR & (1 << 25)));

}

#endif
