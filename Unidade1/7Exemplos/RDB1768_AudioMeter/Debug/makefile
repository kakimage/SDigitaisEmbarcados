################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include src/subdir.mk
-include bitmaps/subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: RDB1768_AudioMeter.axf

# Tool invocations
RDB1768_AudioMeter.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\code_red\ws_examples_to_committ\RDB1768_LCDlib\Debug" -Xlinker --gc-sections -Xlinker -Map=RDB1768_AudioMeter.map -mcpu=cortex-m3 -mthumb -T "rdb1768_audiometer_Debug.ld" -o"RDB1768_AudioMeter.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(OBJS)$(C_DEPS)$(EXECUTABLES) RDB1768_AudioMeter.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size RDB1768_AudioMeter.axf; # arm-none-eabi-objdump -h -S RDB1768_AudioMeter.axf >RDB1768_AudioMeter.lss
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
