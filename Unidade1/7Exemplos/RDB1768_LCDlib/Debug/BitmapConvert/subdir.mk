################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../BitmapConvert/RDBbmconvert.c 

OBJS += \
./BitmapConvert/RDBbmconvert.o 

C_DEPS += \
./BitmapConvert/RDBbmconvert.d 


# Each subdirectory must supply rules for building sources it contributes
BitmapConvert/%.o: ../BitmapConvert/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


