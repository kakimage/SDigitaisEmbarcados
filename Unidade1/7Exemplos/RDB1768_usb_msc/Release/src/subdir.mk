################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/blockdev_sd.c \
../src/cr_startup_lpc17.c \
../src/lpc2000_spi.c \
../src/main_msc.c \
../src/msc_bot.c \
../src/msc_scsi.c \
../src/target.c 

OBJS += \
./src/blockdev_sd.o \
./src/cr_startup_lpc17.o \
./src/lpc2000_spi.o \
./src/main_msc.o \
./src/msc_bot.o \
./src/msc_scsi.o \
./src/target.o 

C_DEPS += \
./src/blockdev_sd.d \
./src/cr_startup_lpc17.d \
./src/lpc2000_spi.d \
./src/main_msc.d \
./src/msc_bot.d \
./src/msc_scsi.d \
./src/target.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DNDEBUG -D__CODE_RED -I"C:\code_red\ws_examples_to_committ\RDB1768_usbstack\inc" -O3 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -mcpu=cortex-m3 -mthumb -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


