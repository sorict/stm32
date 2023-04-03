#include <stdint.h>
#include "gpio.h"
#include "systick.h"
#include "uart.h"
#include "pll.h"

void setup(){

// gpio_clk_init(rcc_reg, 2); //enable gpioa clk
 apb2_pll_clk_init_36MHz();
 gpio_clk_init(rcc_reg, 3);
 gpio_clk_init(rcc_reg, 4); //enable gpioc clk
 gpio_set_mode(gpioc, 13, 0b01, 0b01);
 systick_init(72000000/1400);
 uart_init(uart1);

}


static volatile uint32_t ticks;

void SysTick_Handler(void) {
	ticks++;
}

void delay(unsigned time) {
	uint32_t cnt = ticks + time;
	while(ticks < cnt)
		__asm("nop");
}


int main(){
    setup();
    while(1) {
	gpio_set_value(gpioc, 13, true);
	delay(1000);
	gpio_set_value(gpioc, 13, false);
	uart_write_buf(uart1, "Helo\n", 5);
//	uart_write_byte(uart1, 0b01010101);
	delay(10000);
    }
}
