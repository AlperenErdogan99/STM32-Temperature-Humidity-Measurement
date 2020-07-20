################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include w5500_driver/subdir.mk
-include sht21_driver/subdir.mk
-include multicast/subdir.mk
-include loopback/subdir.mk
-include lcd20x4_driver/.metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
-include lcd20x4_driver/subdir.mk
-include flash_driver/subdir.mk
-include Ethernet/W5500/subdir.mk
-include Ethernet/W5300/subdir.mk
-include Ethernet/W5200/subdir.mk
-include Ethernet/W5100S/subdir.mk
-include Ethernet/W5100/subdir.mk
-include Ethernet/subdir.mk
-include Drivers/STM32F3xx_HAL_Driver/Src/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Stm32_TempHum.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Stm32_TempHum.list \

OBJCOPY_BIN += \
Stm32_TempHum.bin \


# All Target
all: Stm32_TempHum.elf secondary-outputs

# Tool invocations
Stm32_TempHum.elf: $(OBJS) $(USER_OBJS) C:\Users\alperen\Desktop\WIZNET_2\WIZNET_2\STM32F303RETX_FLASH.ld
	arm-none-eabi-gcc -o "Stm32_TempHum.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"C:\Users\alperen\Desktop\WIZNET_2\WIZNET_2\STM32F303RETX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Stm32_TempHum.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -u _printf_float -u _scanf_float -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Stm32_TempHum.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Stm32_TempHum.list"
	@echo 'Finished building: $@'
	@echo ' '

Stm32_TempHum.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Stm32_TempHum.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
