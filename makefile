MCU		= atmega328p
TARGET 		= main
SOURCES		= $(wildcard */*.c)
PROGRAMMER	= gpio
PORT 		= /dev/spidev0.0
BAUD 		= 115200
FORMAT		= ihex

CC		= avr-gcc
OBJECTS 	= $(TARGET).o
OPTIMIZE	= s
CFLAGS 		= -g -c -Werror -Wall -O$(OPTIMIZE)

# MAKE COMMANDS
all : clean hex program
hex : $(TARGET).hex
$(TARGET).elf : .c.o
	$(CC) $(LDFLAGS) -mmcu=$(MCU) $(OBJECTS) -o $(TARGET).elf

$(TARGET).hex : $(TARGET).elf
	avr-objcopy -O $(FORMAT) $< $@
.c.o : 
	$(CC) $(CFLAGS) -mmcu=$(MCU) ${SOURCES}
program :
	avrdude -p $(MCU) -P $(PORT) -b $(BAUD) -c $(PROGRAMMER) -e -U flash:w:$(TARGET).hex:a
clean :
	rm -rf *.o *.elf *.hex
