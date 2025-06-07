# ==============================================================================
# Project Makefile (Transmitter)
# ==============================================================================

# USB port for programming
PORT       = /dev/ttyUSB0

# Build output directory (relative to this Makefile)
ROUTE      = ../build

# Target microcontroller and clock
MCU        = atmega328p
F_CPU      = 16000000UL

# Toolchain
CC         = avr-gcc
OBJCOPY    = avr-objcopy
AVRDUDE    = avrdude

# Optimization & standards
OPT        = -Os
CSTD       = -std=c99

# Compiler flags (for .c → .o)
#  -mmcu: selects device and linker script
#  -DF_CPU: defines CPU clock for delays, <util/delay.h>
#  -I../include: header search path
#  -Wall: all warnings
CFLAGS     = -mmcu=$(MCU) -DF_CPU=$(F_CPU) $(OPT) -I../include -Wall $(CSTD)

# Linker flags (for .o → .elf)
LFLAGS     = -mmcu=$(MCU)

# Output name file 
OUTPUT = program

# Source files
SRC        = main.c \
             pwm.c \
             spi.c \
             radio.c \
             usart.c \
             receiver.c

# Object files (in $(ROUTE) directory)
OBJ        = $(SRC:%.c=$(ROUTE)/%.o)

# Default target: build .hex
all: prebuild $(ROUTE)/$(OUTPUT).hex

# ------------------------------------------------------------------------------
# Prebuild echo
# ------------------------------------------------------------------------------
prebuild:
	@echo "  [BUILD]   Starting build..."

# ------------------------------------------------------------------------------
# Compile each .c into .o
# ------------------------------------------------------------------------------
$(ROUTE)/%.o: %.c
	@echo "  [CC]      Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

# ------------------------------------------------------------------------------
# Link .o to .elf
# ------------------------------------------------------------------------------
$(ROUTE)/$(OUTPUT).elf: $(OBJ)
	@echo "  [LD]      Linking to $(OUTPUT).elf"
	@$(CC) $(LFLAGS) $(OBJ) -o $@

# ------------------------------------------------------------------------------
# Convert .elf to .hex
# ------------------------------------------------------------------------------
$(ROUTE)/$(OUTPUT).hex: $(ROUTE)/$(OUTPUT).elf
	@echo "  [OBJCOPY] Generating $(OUTPUT).hex"
	@$(OBJCOPY) -O ihex -R .eeprom $< $@
	@echo "  [DONE]    Build complete."

# ------------------------------------------------------------------------------
# Upload firmware to MCU
# ------------------------------------------------------------------------------
upload: $(ROUTE)/program.hex
	@echo "  [UPLOAD]  Flashing to MCU"
	@$(AVRDUDE) -c arduino -p $(MCU) -P $(PORT) -b 115200 -U flash:w:$<
	@echo "  [DONE]    Flash complete."

# ------------------------------------------------------------------------------
# Clean build artifacts
# ------------------------------------------------------------------------------
clear:
	@echo "  [CLEAN]   Removing build artifacts"
	@rm -f $(OBJ) $(ROUTE)/$(OUTPUT).elf $(ROUTE)/$(OUTPUT).hex

# ==============================================================================
# End of Makefile
# ==============================================================================

