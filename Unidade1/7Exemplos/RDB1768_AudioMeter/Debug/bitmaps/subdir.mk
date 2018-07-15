################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../bitmaps/codered128x37.c 

OBJS += \
./bitmaps/codered128x37.o 

C_DEPS += \
./bitmaps/codered128x37.d 


# Each subdirectory must supply rules for building sources it contributes
bitmaps/%.o: ../bitmaps/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -I"C:\code_red\ws_examples_to_committ\RDB1768_LCDlib\src" -I"C:\code_red\ws_examples_to_committ\RDB1768_AudioMeter\bitmaps" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


