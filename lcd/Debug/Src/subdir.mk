################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/font12.c \
../Src/font16.c \
../Src/font20.c \
../Src/font24.c \
../Src/font8.c \
../Src/ltdc.c \
../Src/main.c \
../Src/stm32f7xx_hal_msp.c \
../Src/stm32f7xx_it.c \
../Src/system_stm32f7xx.c 

OBJS += \
./Src/font12.o \
./Src/font16.o \
./Src/font20.o \
./Src/font24.o \
./Src/font8.o \
./Src/ltdc.o \
./Src/main.o \
./Src/stm32f7xx_hal_msp.o \
./Src/stm32f7xx_it.o \
./Src/system_stm32f7xx.o 

C_DEPS += \
./Src/font12.d \
./Src/font16.d \
./Src/font20.d \
./Src/font24.d \
./Src/font8.d \
./Src/ltdc.d \
./Src/main.d \
./Src/stm32f7xx_hal_msp.d \
./Src/stm32f7xx_it.d \
./Src/system_stm32f7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m7 -mthumb -mfloat-abi=hard -mfpu=fpv5-sp-d16 '-D__weak=__attribute__((weak))' '-D__packed="__attribute__((__packed__))"' -DUSE_HAL_DRIVER -DSTM32F746xx -I"/home/eivanov/stm32/workspace/lcd/Inc" -I"/home/eivanov/stm32/workspace/lcd/Drivers/STM32F7xx_HAL_Driver/Inc" -I"/home/eivanov/stm32/workspace/lcd/Drivers/STM32F7xx_HAL_Driver/Inc/Legacy" -I"/home/eivanov/stm32/workspace/lcd/Drivers/CMSIS/Device/ST/STM32F7xx/Include" -I"/home/eivanov/stm32/workspace/lcd/Drivers/CMSIS/Include"  -Og -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


