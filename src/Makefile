CC=avr-gcc
CFLAGS=-g -Os -Wall -mcall-prologues -mmcu=atmega328p
OBJ2HEX=avr-objcopy 
TARGET=convik

OBJS=main.o

%.obj: %.o
	avr-gcc -g -Os -Wall -mcall-prologues -mmcu=atmega328p -c $< -o $@

$(TARGET).hex: $(OBJS)
	$(OBJ2HEX) -R .eeprom -O ihex $(OBJS) $(TARGET).hex

clean:
	rm -f *.o *.objs *.hex

