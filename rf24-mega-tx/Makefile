all:
	avr-gcc -DF_CPU=2000000L -std=gnu99 -Os -mmcu=atmega328 -I include -c main.c softuart.c lib/mirf.c lib/spi.c
	avr-gcc -mmcu=atmega328 -o main.elf main.o softuart.o mirf.o spi.o
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avrdude -P usb -p atmega328 -c usbtiny -e -U flash:w:main.hex

