################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/RDB1768_AUDIO.c \
../src/audiometer_main.c \
../src/cr_startup_lpc17.c \
../src/delay.c \
../src/i2c.c \
../src/target.c 

OBJS += \
./src/RDB1768_AUDIO.o \
./src/audiometer_main.o \
./src/cr_startup_lpc17.o \
./src/delay.o \
./src/i2c.o \
./src/target.o 

C_DEPS += \
./src/RDB1768_AUDIO.d \
./src/audiometer_main.d \
./src/cr_startup_lpc17.d \
./src/delay.d \
./src/i2c.d \
./src/target.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DNDEBUG -D__CODE_RED -I"C:\code_red\ws_examples_to_committ\RDB1768_LCDlib\src" -I"C:\code_red\ws_examples_to_committ\RDB1768_AudioMeter\bitmaps" -O3 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


