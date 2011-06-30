CC=avr-gcc
CFLAGS=-g -Os -Wall -mcall-prologues -mmcu=atmega32
OBJ2HEX=avr-objcopy 
UISP=uisp 
TARGET=blink

program : $(TARGET).hex
	$(UISP) -dprog=stk500 -dserial=/dev/ttyS1 --erase -dpart=atmega32
	$(UISP) -dprog=stk500 -dserial=/dev/ttyS1 --upload -dpart=atmega32 \
		if=$(TARGET).hex -v=2
%.obj : %.o
	$(CC) $(CFLAGS) $< -o $@

%.hex : %.obj
	$(OBJ2HEX) -R .eeprom -O ihex $< $@

clean :
	rm -f *.hex *.obj *.o
