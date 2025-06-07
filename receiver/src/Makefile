# Direction from your USB connection between the arduino and the computer (can be found on the "dev" directory)
PORT = /dev/ttyUSB0
# Target microcontroller
ROUTE = ../build
MCU = atmega328p
# CPU Clock Speed
F_CPU = 16000000UL
#Compiler and tools

CC = avr-gcc
OBJCOPY = avr-objcopy


# Optimization level
OPT = -Os

# Flags for compiling the .c files and generating the .o files
#The -I flag tells the compiler where to look for the #include in the C files
CFLAGS = -mmcu=$(MCU) -DF_CPU=$(F_CPU) $(OPT) -I../include -Wall -std=c99 

# Flags for linking all the .o files and resolve dependencies
LFLAGS = -mmcu=$(MCU)

# SRC files to be compiled 
SRC = main.c spi.c radio.c pwm.c receiver.c usart.c


#We define .o files from the .c files from SRC 
OBJ = $(SRC:%.c=$(ROUTE)/%.o) 


#We send an echo before starting the compilation

all: prebuild $(ROUTE)/program.hex

prebuild:
	@echo "	Building project..."
	 


#Rule to create .o files

$(ROUTE)/%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "	Creating the .o file from the $< file"
	
#Rule to create .hex file

$(ROUTE)/program.hex: $(ROUTE)/program.elf
	@$(OBJCOPY) -O ihex -R .eeprom $< $@
	@echo "	Creating the .hex file from the .elf file"
	@echo "	End of compilation"

#Rule to create .elf file
	
$(ROUTE)/program.elf: $(OBJ)
	@$(CC) $(LFLAGS) $(OBJ) -o $@
	@echo "	Creating the .elf file from the .o files"
	
	
#Rule to upload the code
		
upload: $(ROUTE)/program.hex
	@avrdude -c arduino -p $(MCU) -P $(PORT) -b 115200 -U flash:w:$<
	@echo "	Code uploaded into the microcontroller"
	
#Rule to clear the compilation files from the file especified by ROUTE
clear:
	@rm -f $(OBJ) $(ROUTE)/program.elf $(ROUTE)/program.hex 
	@echo "	Cleaning all compilation files"
	


