################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
ELF_SRCS += \
../Modulo_SSegDisplay.elf 

O_SRCS += \
../core_cm3.o \
../main.o \
../startup_LPC17xx.o \
../system_LPC17xx.o 

C_SRCS += \
../core_cm3.c \
../main.c \
../system_LPC17xx.c 

OBJS += \
./core_cm3.o \
./main.o \
./system_LPC17xx.o 

C_DEPS += \
./core_cm3.d \
./main.d \
./system_LPC17xx.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM Sourcery Windows GCC C Compiler'
	arm-none-eabi-gcc -O0 -Wall -Wa,-adhlns="$@.lst" -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -mcpu=cortex-m3 -mthumb -g3 -gdwarf-2 -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


