#ifndef GPIO_H
#define GPIO_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define GPIO_INPUT 0
#define GPIO_OUTPUT 1
#define GPIO_AF 2
#define GPIO_ANALOG 3
 
struct stm_gpio {
  volatile uint32_t CRL;
  volatile uint32_t CRH; 
  volatile uint32_t IDR;
  volatile uint32_t ODR;
  volatile uint32_t BSRR;
  volatile uint32_t BRR;
  volatile uint32_t LCKR; 
};

struct stm_afio {
  volatile uint32_t EVCR;
  volatile uint32_t MAPR;
  volatile uint32_t EXTICR1;
  volatile uint32_t EXTICR2;
  volatile uint32_t EXTICR3;
  volatile uint32_t EXTICR4;
  volatile uint32_t MAPR2;

};

struct rcc {
  volatile uint32_t CR;
  volatile uint32_t CFGR;
  volatile uint32_t CIR;
  volatile uint32_t APB2RSRT;
  volatile uint32_t APB1RSTR;
  volatile uint32_t AHBENR;
  volatile uint32_t APB2ENR;
  volatile uint32_t APB1ENR;
  volatile uint32_t BDCR;
  volatile uint32_t CSR;
};


struct stm_gpio *gpioa = (struct stm_gpio*)(0x40010800);
struct stm_gpio *gpiob = (struct stm_gpio*)(0x40010C00);
struct stm_gpio *gpioc = (struct stm_gpio*)(0x40011000);
struct stm_gpio *gpiod = (struct stm_gpio*)(0x40011400);
struct stm_gpio *gpioe = (struct stm_gpio*)(0x40011800);
struct stm_gpio *gpiof = (struct stm_gpio*)(0x40011C00);
struct stm_gpio *gpiog = (struct stm_gpio*)(0x40012000);

struct stm_afio *afio = (struct stm_afio*)(0x40010000);

struct rcc *rcc_reg = (struct rcc*)(0x40021000);

void gpio_mode_set(int pin, int mode);

static inline void gpio_set_mode(struct stm_gpio *gpio, uint8_t pin, uint8_t mode, uint8_t type){
	if (pin < 7) {
	   
           gpio->CRL &= ~(0b11 << pin*4);
	   gpio->CRL |= (mode & 0b11) << (pin*4);
	   gpio->CRL &= ~(0b11) << ((pin*4) + 2);
	   gpio->CRL |= (type & 0b11) << ((pin*4) + 2);  
        } else {
	   gpio->CRH &= ~(0b11 << ((pin-8)*4));
	   gpio->CRH &= ~(0b11 << ((pin-8)*4 + 2));
	   gpio->CRH |= (mode & 0b11) << ((pin-8)*4);
	   gpio->CRH |= (type & 0b11) << (((pin-8)*4)+2); 
        }
}

static inline void gpio_set_value(struct stm_gpio *gpio, uint16_t pin, bool level){
	
	if (!level) {
	   gpio->BSRR |= (0x01 << pin);
	} else {
	   gpio->ODR |= (level & 0x01) << pin;
	   gpio->BSRR |= (1 << (pin+16));
        }

}

static inline void gpio_clk_init(struct rcc *rcc_addr, uint16_t pin) {
	
	rcc_addr->APB2ENR |= (1 << pin);
}

#endif
