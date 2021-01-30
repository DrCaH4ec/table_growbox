#Makefile for building code for avr microcontrollers

#------------------------------------------------------------------------------
# ------------------------YOU CAN(and NEED) TO CHANGE IT-----------------------
#------------------------------------------------------------------------------
MCU = atmega328p
TARGET = growbox
#------------------------------------------------------------------------------

#you need to contain all you *.h files in dir "inc" IT'S A RULE
INC_DIR = ../inc
OUT_DIR = ../output
#flags for compiler
WFLAGS = -Wall -Werror
#level of optimisation
OPTIM = -O2 -Os



#------------------------------------------------------------------------------
src_files := $(wildcard *.c)
obj_files := $(src_files:.c=.o)

#------------------------------------------------------------------------------
%.o: %.c
	avr-gcc $(WFLAGS) $(OPTIM) -I $(INC_DIR) -mmcu=$(MCU) -c $^ -o ${OUT_DIR}/$@

#------------------------------------------------------------------------------
$(TARGET).elf: $(obj_files)
	avr-gcc -mmcu=$(MCU) -o $(OUT_DIR)/$@ $(wildcard $(OUT_DIR)/*.o)

#------------------------------------------------------------------------------
build: $(TARGET).elf
	avr-objcopy -j .text -j .data -O ihex $(OUT_DIR)/$^ $(OUT_DIR)/$(TARGET).hex

#------------------------------------------------------------------------------
.PHONY: clean
clean:
	rm $(OUT_DIR)/$(obj_files) $(OUT_DIR)/$(TARGET).elf

#------------------------------------------------------------------------------
.PHONY: tidy
tidy: clean
	rm $(OUT_DIR)/$(TARGET).hex

#------------------------------------------------------------------------------
#------------------------------------------------------------------------------
PROGRAMMER=arduino
SPEED=57600
PORT=/dev/ttyUSB0
MEMTYPE=flash
.PHONY: prog
prog:
	avrdude -p $(MCU) -b $(SPEED) -c $(PROGRAMMER) -P $(PORT) -U $(MEMTYPE):w:$(OUT_DIR)/$(TARGET).hex
