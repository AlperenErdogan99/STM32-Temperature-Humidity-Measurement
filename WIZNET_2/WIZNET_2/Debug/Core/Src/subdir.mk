################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/main.c \
../Core/Src/stm32f3xx_hal_msp.c \
../Core/Src/stm32f3xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f3xx.c 

OBJS += \
./Core/Src/main.o \
./Core/Src/stm32f3xx_hal_msp.o \
./Core/Src/stm32f3xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f3xx.o 

C_DEPS += \
./Core/Src/main.d \
./Core/Src/stm32f3xx_hal_msp.d \
./Core/Src/stm32f3xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f3xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/main.o: ../Core/Src/main.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I"C:/Users/alperen/Desktop/WIZNET_2/sht21_driver" -I"C:/Users/alperen/Desktop/WIZNET_2/w5500_driver" -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Ethernet" -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Application/multicast" -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Core/Inc -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Application/loopback" -I"C:/Users/alperen/Desktop/WIZNET_2/lcd20x4_driver" -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I"C:/Users/alperen/Desktop/WIZNET_2/flash_driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/main.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f3xx_hal_msp.o: ../Core/Src/stm32f3xx_hal_msp.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I"C:/Users/alperen/Desktop/WIZNET_2/sht21_driver" -I"C:/Users/alperen/Desktop/WIZNET_2/w5500_driver" -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Ethernet" -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Application/multicast" -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Core/Inc -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Application/loopback" -I"C:/Users/alperen/Desktop/WIZNET_2/lcd20x4_driver" -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I"C:/Users/alperen/Desktop/WIZNET_2/flash_driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f3xx_hal_msp.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/stm32f3xx_it.o: ../Core/Src/stm32f3xx_it.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I"C:/Users/alperen/Desktop/WIZNET_2/sht21_driver" -I"C:/Users/alperen/Desktop/WIZNET_2/w5500_driver" -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Ethernet" -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Application/multicast" -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Core/Inc -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Application/loopback" -I"C:/Users/alperen/Desktop/WIZNET_2/lcd20x4_driver" -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I"C:/Users/alperen/Desktop/WIZNET_2/flash_driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/stm32f3xx_it.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/syscalls.o: ../Core/Src/syscalls.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I"C:/Users/alperen/Desktop/WIZNET_2/sht21_driver" -I"C:/Users/alperen/Desktop/WIZNET_2/w5500_driver" -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Ethernet" -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Application/multicast" -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Core/Inc -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Application/loopback" -I"C:/Users/alperen/Desktop/WIZNET_2/lcd20x4_driver" -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I"C:/Users/alperen/Desktop/WIZNET_2/flash_driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/syscalls.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/sysmem.o: ../Core/Src/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I"C:/Users/alperen/Desktop/WIZNET_2/sht21_driver" -I"C:/Users/alperen/Desktop/WIZNET_2/w5500_driver" -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Ethernet" -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Application/multicast" -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Core/Inc -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Application/loopback" -I"C:/Users/alperen/Desktop/WIZNET_2/lcd20x4_driver" -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I"C:/Users/alperen/Desktop/WIZNET_2/flash_driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/sysmem.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"
Core/Src/system_stm32f3xx.o: ../Core/Src/system_stm32f3xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I"C:/Users/alperen/Desktop/WIZNET_2/sht21_driver" -I"C:/Users/alperen/Desktop/WIZNET_2/w5500_driver" -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Ethernet" -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Application/multicast" -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Core/Inc -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Application/loopback" -I"C:/Users/alperen/Desktop/WIZNET_2/lcd20x4_driver" -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I"C:/Users/alperen/Desktop/WIZNET_2/flash_driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Core/Src/system_stm32f3xx.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

