CC=avr-gcc
CFLAGS=-g -Os -Wall -mcall-prologues -mmcu=atmega328p
OBJ2HEX=avr-objcopy 
TARGET=convik

OBJS=main.o core/pwm.o core/usart.o core/adc.o core/acmp.o utils/char_fifo.o utils/char_buffer.o proto/commands.o proto/serial_proto.o motor.o

all: $(TARGET).hex

%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET).hex : $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET)
	$(OBJ2HEX) -R .eeprom -O ihex $(TARGET) $(TARGET).hex

clean :
	rm -f *.hex *.obj *.o */*.o $(TARGET)
