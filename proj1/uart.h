#ifndef _UART_H
#define _UART_H

#include "gpio.h"

struct stm_uart {
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;

};

struct stm_uart *uart1 = (struct stm_uart *)(0x40013800);
struct stm_uart *uart2 = (struct stm_uart *)(0x40004400);
struct stm_uart *uart3 = (struct stm_uart *)(0x40004800);
struct stm_uart *uart4 = (struct stm_uart *)(0x40004C00);
struct stm_uart *uart5 = (struct stm_uart *)(0x40005000);

static inline void uart_init(struct stm_uart *uart) {

	
		rcc_reg->APB2ENR |= (1 << 14);
		rcc_reg->APB2ENR |= (1 << 2);
//		rcc_reg->APB2ENR |= (1 << 0);
//		gpio_clk_init(rcc_reg, 2);
		//PA9 tx, PA10 rx
		gpio_set_mode(gpioa, 9, 0b11, 0b10); //gpio alternate function output
		gpio_set_mode(gpioa, 10, GPIO_OUTPUT, 0b00);
	
		uart->CR1 &= 0x00;
//		uart->BRR |= (0x6 << 0) | (0xF3 << 4); 
//		uart->BRR |= (0xA << 0) | (0x27<<4);//72MHz
		uart->BRR |= (0x9 << 0) | (0x13 << 4);//36MHz
		uart->CR1 |= (1 << 2) | (1 << 3) | (1 << 13);	
}

static inline void uart_write_byte(struct stm_uart *uart, uint8_t byte) {
	uart->DR = byte;
	while(!(uart->SR & (1 << 6)));
}

static inline void uart_write_buf(struct stm_uart *uart, char *buf, size_t len) {
	while (len-- > 0)
		uart_write_byte(uart, *(uint8_t *) buf++);
}

static inline uint8_t uart_read(struct stm_uart *uart) {
	while(!(uart->SR & (1 << 5)));
	return (uint8_t) (uart->DR & 0xFF);
}

#endif
