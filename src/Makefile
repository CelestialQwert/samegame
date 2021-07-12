#
# Simple Makefile that compiles all .c and .s files in the same folder
#

# If you move this project you can change the directory 
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
GBDK_HOME = /mnt/d/Programs/gameboy_dev/gbdk/

LCC = $(GBDK_HOME)bin/lcc -Wm-yn"SAMEGAME"  -Wm-yc

# You can uncomment the line below to turn on debug output
# LCC = $(LCC) -debug

# You can set the name of the .gb ROM file here
PROJECTNAME = samegame

BINS	    = $(PROJECTNAME).gb
CSOURCES   := $(wildcard *.c) $(wildcard gfx/*.c) 
ASMSOURCES := $(wildcard *.s)

all:	$(BINS)

make.bat: Makefile
	@echo "REM Automatically generated from Makefile" > make.bat
	@make -sn | sed y/\\//\\\\/ | grep -v make >> make.bat

# Compile and link all source files in a single call to LCC
$(BINS):	$(CSOURCES) $(ASMSOURCES)
	$(LCC) -o $@ $(CSOURCES) $(ASMSOURCES)

clean:
	rm -rf *.o *.lst *.map *.gb *.gbc *.ihx *.sym *.cdb *.adb *.asm

