all:
	avr-gcc -std=gnu99 -Os -mmcu=atmega328p -c main.c
	avr-gcc -mmcu=atmega328p -o main.elf main.o
	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
	avrdude -P usb -p atmega328p -c usbtiny -e -U flash:w:main.hex

