################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MP_SSD1306/mp_ssd1306.c 

OBJS += \
./MP_SSD1306/mp_ssd1306.o 

C_DEPS += \
./MP_SSD1306/mp_ssd1306.d 


# Each subdirectory must supply rules for building sources it contributes
MP_SSD1306/%.o: ../MP_SSD1306/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: AVR Compiler'
	avr-gcc -Wall -Os -fpack-struct -fshort-enums -ffunction-sections -fdata-sections -std=gnu99 -funsigned-char -funsigned-bitfields -mmcu=atmega32 -DF_CPU=11059200UL -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


