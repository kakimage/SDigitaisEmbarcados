
INCLUDE_PATHS = -I.  
LINKER_SCRIPT = ./config/LPC1768.ld
PROJECT = main



CC      = $(GCC_BIN)arm-none-eabi-gcc
CPP     = $(GCC_BIN)arm-none-eabi-g++
LD      = $(GCC_BIN)arm-none-eabi-gcc
OBJCOPY = $(GCC_BIN)arm-none-eabi-objcopy
CCLOCAL = gcc

CPU = -mcpu=cortex-m3 -mthumb
CC_FLAGS = $(CPU) -c -fno-common -fmessage-length=0 -Wall -fno-exceptions -ffunction-sections -fdata-sections -g 
CC_SYMBOLS = -DTARGET_LPC1769 -DTOOLCHAIN_GCC_ARM -DNDEBUG -D__CORTEX_M3
LD_FLAGS = -mcpu=cortex-m3 -mthumb -Wl,--gc-sections,-Map=$(PROJECT).map,--cref 
LD_SYS_LIBS = -lc -lgcc -lnosys

BASICOS    = src/system_LPC17xx.o src/startup_LPC17xx.o src/core_cm3.o
MEUPROJETO = main.o uart.o digital.o interrupcao_externa.o teclado.o



$(PROJECT).bin: $(PROJECT).elf nxpsum
	# *************************** $(PROJECT).bin *****************************  
	$(OBJCOPY) -O binary $< $@
	./nxpsum $@
	# ****************************************************************


$(PROJECT).elf: $(BASICOS)  $(MEUPROJETO) 
	# *************************** $(PROJECT).elf *****************************  
	$(LD) $(LD_FLAGS) -T$(LINKER_SCRIPT) $(LIBRARY_PATHS) -o $@ $(addprefix $(BUILD_DIR), $^) $(LIBRARIES) $(LD_SYS_LIBS) $(LIBRARIES) $(LD_SYS_LIBS)

	# ****************************************************************






main.o:	main.cpp uart.h teclado.h
	# *************************** main *****************************
	$(CC) $(CC_FLAGS) $(CC_SYMBOLS) $(INCLUDE_PATHS) -std=gnu++98 main.cpp -c
	# **************************************************************

teclado.o: teclado.cpp teclado.h digital.h uart.h interrupcao_externa.h
	$(CC) $(CC_FLAGS) $(CC_SYMBOLS) $(INCLUDE_PATHS) -std=gnu++98 teclado.cpp -c

interrupcao_externa.o: interrupcao_externa.cpp digital.h uart.h interrupcao_externa.h
	$(CC) $(CC_FLAGS) $(CC_SYMBOLS) $(INCLUDE_PATHS) -std=gnu++98 interrupcao_externa.cpp -c

uart.o: uart.cpp  uart.h
	$(CC) $(CC_FLAGS) $(CC_SYMBOLS) $(INCLUDE_PATHS) -std=gnu++98 uart.cpp -c

digital.o: digital.cpp  digital.h
	$(CC) $(CC_FLAGS) $(CC_SYMBOLS) $(INCLUDE_PATHS) -std=gnu++98 digital.cpp -c






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

