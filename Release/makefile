################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include MP_SSD1306/subdir.mk
-include BMP/subdir.mk
-include 1Wire/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Piwowar.lss \

FLASH_IMAGE += \
Piwowar.hex \

EEPROM_IMAGE += \
Piwowar.eep \

SIZEDUMMY += \
sizedummy \


# All Target
all: Piwowar.elf secondary-outputs

# Tool invocations
Piwowar.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Piwowar.map -mmcu=atmega32 -o "Piwowar.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Piwowar.lss: Piwowar.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Piwowar.elf  >"Piwowar.lss"
	@echo 'Finished building: $@'
	@echo ' '

Piwowar.hex: Piwowar.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Piwowar.elf  "Piwowar.hex"
	@echo 'Finished building: $@'
	@echo ' '

Piwowar.eep: Piwowar.elf
	@echo 'Create eeprom image (ihex format)'
	-avr-objcopy -j .eeprom --no-change-warnings --change-section-lma .eeprom=0 -O ihex Piwowar.elf  "Piwowar.eep"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Piwowar.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Piwowar.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(EEPROM_IMAGE)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Piwowar.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(EEPROM_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
