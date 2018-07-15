################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/usbcontrol.c \
../src/usbhw_lpc.c \
../src/usbinit.c \
../src/usbstdreq.c 

OBJS += \
./src/usbcontrol.o \
./src/usbhw_lpc.o \
./src/usbinit.o \
./src/usbstdreq.o 

C_DEPS += \
./src/usbcontrol.d \
./src/usbhw_lpc.d \
./src/usbinit.d \
./src/usbstdreq.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DNDEBUG -D__CODE_RED -I"C:\code_red\ws_examples_to_committ\RDB1768_usbstack\inc" -O3 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


