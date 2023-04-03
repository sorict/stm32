CC=arm-none-eabi-gcc
OBJCOPY=arm-none-eabi-objcopy

MACH=cortex-m3
CFLAGS= -c -mcpu=$(MACH) -mthumb -std=gnu11 -Wall -g -O0
LDFLAGS= -T stm32_ls.ld -nostdlib -Wl,-Map=blink.map

all: blink.bin

blink.bin: blink.elf
	$(OBJCOPY) -O binary $^ $@

blink.elf: blink.o stm32_startup.o 
	$(CC) $(LDFLAGS) -o $@ $^

.PHONY: clean
clean:
	rm *.o *.elf

.PHONY: flash
flash: all
	st-flash write blink.bin 0x08000000

.PHONY: reset
reset:
	st-flash reset

.PHONY: debughost
debughost:
	st-util

.PHONY: gdb
gdb: blink.elf
	arm-none-eabi-gdb blink.elf
