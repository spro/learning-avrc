all:
	avr-gcc -DF_CPU=1000000L -std=gnu99 -Os -mmcu=attiny85 -I include -c main.c lib/mirf.c lib/spi.c
	avr-gcc -mmcu=attiny85 -o main.elf main.o mirf.o spi.o
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avrdude -P usb -p attiny85 -c usbtiny -e -U flash:w:main.hex

