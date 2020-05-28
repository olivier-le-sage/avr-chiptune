AVRPART=attiny10
AVRCFLAGS=-g -Wall -Os -mmcu=$(AVRPART) -DF_CPU=1000000UL
AVRASFLAGS:=$(AVRCFLAGS)

chiptune.hex : chiptune.cpp
	avr-gcc -I  -g $(AVRCFLAGS)   -mmcu=$(AVRPART) -Wl,-Map,chiptune.map -o chiptune.elf $^
	avr-objdump chiptune.elf -S > asm/chiptune.lst
	avr-objcopy -j .text -j .data -O ihex chiptune.elf chiptune.hex

frequency_cycle.hex : frequency_cycle.cpp
	avr-gcc -I  -g $(AVRCFLAGS)   -mmcu=$(AVRPART) -Wl,-Map,frequency_cycle.map -o frequency_cycle.elf $^
	avr-objdump frequency_cycle.elf -S > asm/frequency_cycle.lst
	avr-objcopy -j .text -j .data -O ihex frequency_cycle.elf frequency_cycle.hex

clean :
	rm -rf *.o *.elf *.bin *.hex
