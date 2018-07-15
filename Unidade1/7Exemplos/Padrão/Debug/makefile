################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := cs-rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
SECONDARY_FLASH += \
Módulo7SegmentDisplay.hex \

SECONDARY_LIST += \
Módulo7SegmentDisplay.lst \

SECONDARY_SIZE += \
Módulo7SegmentDisplay.siz \


# All Target
all: Módulo7SegmentDisplay.elf secondary-outputs

# Tool invocations
Módulo7SegmentDisplay.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM Sourcery Windows GCC C Linker'
	arm-none-eabi-gcc -nostartfiles -Wl,-Map,Módulo7SegmentDisplay.map -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o"Módulo7SegmentDisplay.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Módulo7SegmentDisplay.hex: Módulo7SegmentDisplay.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Flash Image'
	arm-none-eabi-objcopy -O ihex Módulo7SegmentDisplay.elf "Módulo7SegmentDisplay.hex"
	@echo 'Finished building: $@'
	@echo ' '

Módulo7SegmentDisplay.lst: Módulo7SegmentDisplay.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Create Listing'
	arm-none-eabi-objdump -h -S Módulo7SegmentDisplay.elf >"Módulo7SegmentDisplay.lst"
	@echo 'Finished building: $@'
	@echo ' '

Módulo7SegmentDisplay.siz: Módulo7SegmentDisplay.elf
	@echo 'Invoking: ARM Sourcery Windows GNU Print Size'
	arm-none-eabi-size  --format=berkeley Módulo7SegmentDisplay.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(SECONDARY_SIZE)$(OBJS)$(C_DEPS)$(ASM_DEPS)$(SECONDARY_FLASH)$(EXECUTABLES)$(SECONDARY_LIST)$(S_UPPER_DEPS) Módulo7SegmentDisplay.elf
	-@echo ' '

secondary-outputs: $(SECONDARY_FLASH) $(SECONDARY_LIST) $(SECONDARY_SIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
