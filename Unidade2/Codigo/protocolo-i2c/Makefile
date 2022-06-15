
INCLUDE_PATHS = -I.  
LINKER_SCRIPT = ./config/LPC1768.ld
PROJECT = main



CC      = $(GCC_BIN)arm-none-eabi-gcc
CPP     = $(GCC_BIN)arm-none-eabi-g++
LD      = $(GCC_BIN)arm-none-eabi-gcc
OBJCOPY = $(GCC_BIN)arm-none-eabi-objcopy
CCLOCAL = gcc

CPU = -mcpu=cortex-m3 -mthumb
CC_FLAGS = -D_USA_ARM_  $(CPU) -c -fno-common -fmessage-length=0 -Wall -fno-exceptions -ffunction-sections -fdata-sections -g 
CC_SYMBOLS = -DTARGET_LPC1769 -DTOOLCHAIN_GCC_ARM -DNDEBUG -D__CORTEX_M3
LD_FLAGS = -mcpu=cortex-m3 -mthumb -Wl,--gc-sections,-Map=$(PROJECT).map,--cref 
LD_SYS_LIBS = -lc -lgcc -lnosys

BASICOS    = src/system_LPC17xx.o src/startup_LPC17xx.o src/core_cm3.o
MEUPROJETO = main.o i2c_software.o digital.o delay.o uart.o memoria.o



$(PROJECT).bin: $(PROJECT).elf nxpsum
	# *************************** $(PROJECT).bin *****************************  
	$(OBJCOPY) -O binary $< $@
	./nxpsum $@
	# ****************************************************************


$(PROJECT).elf: $(BASICOS)  $(MEUPROJETO) 
	# *************************** $(PROJECT).elf *****************************  
	$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ $(addprefix $(BUILD_DIR), $^) $(LIBRARIES) $(LD_SYS_LIBS) $(LIBRARIES) $(LD_SYS_LIBS)

	# ****************************************************************


main.o:	main.c
	# *************************** main *****************************
	$(CC) $(CC_FLAGS) $(CC_SYMBOLS) $(INCLUDE_PATHS) -std=gnu99 main.c -c
	# **************************************************************

memoria.o:  memoria.h i2c_software.o memoria.c
	$(CC) $(CC_FLAGS) $(CC_SYMBOLS) $(INCLUDE_PATHS) -std=gnu99 memoria.c -c

i2c_software.o:	i2c_software.c i2c_software.h digital.h delay.o
	# *************************** main *****************************
	$(CC) $(CC_FLAGS) $(CC_SYMBOLS) $(INCLUDE_PATHS) -std=gnu99 i2c_software.c -c
	# **************************************************************

digital.o:	digital.c digital.h
	# *************************** main *****************************
	$(CC) $(CC_FLAGS) $(CC_SYMBOLS) $(INCLUDE_PATHS) -std=gnu99 digital.c -c
	# **************************************************************

uart.o:	uart.c uart.h
	# *************************** main *****************************
	$(CC) $(CC_FLAGS) $(CC_SYMBOLS) $(INCLUDE_PATHS) -std=gnu99 uart.c -c
	# **

delay.o:	delay.c delay.h
	# *************************** main *****************************
	$(CC) $(CC_FLAGS) $(CC_SYMBOLS) $(INCLUDE_PATHS) -std=gnu99 delay.c -c
	# **************************************************************



src/core_cm3.o:	src/core_cm3.c
	# *************************** core_cm3 *************************
	$(CC) $(CC_FLAGS) $(CC_SYMBOLS) $(INCLUDE_PATHS) -std=gnu99 src/core_cm3.c -c  -o src/core_cm3.o
	# **************************************************************


src/system_LPC17xx.o:	src/system_LPC17xx.c
	# *********************** system_LPC17xx ***********************
	$(CC) $(CC_FLAGS) $(CC_SYMBOLS) $(INCLUDE_PATHS) -std=gnu99 src/system_LPC17xx.c -c -o src/system_LPC17xx.o
	# **************************************************************


src/startup_LPC17xx.o:	src/startup_LPC17xx.c
	# *********************** startup_LPC17xx **********************
	$(CC) $(CC_FLAGS) $(CC_SYMBOLS) $(INCLUDE_PATHS) -std=gnu99 src/startup_LPC17xx.c -c -o src/startup_LPC17xx.o
	# **************************************************************

nxpsum:
	# **************************** nxpsum ****************************
	$(CCLOCAL) nxpsum.c -std=c99 -o nxpsum
	# ****************************************************************
	
clean:
	rm -f *.elf *.bin *.o src/*.o *.map nxpsum

flash:
	 lpc21isp -control -bin $(PROJECT).bin /dev/ttyUSB0 115200 12000

