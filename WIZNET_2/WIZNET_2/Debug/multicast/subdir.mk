################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Application/multicast/multicast.c 

OBJS += \
./multicast/multicast.o 

C_DEPS += \
./multicast/multicast.d 


# Each subdirectory must supply rules for building sources it contributes
multicast/multicast.o: C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Application/multicast/multicast.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DUSE_HAL_DRIVER -DSTM32F303xE -DDEBUG -c -I../Drivers/CMSIS/Device/ST/STM32F3xx/Include -I"C:/Users/alperen/Desktop/WIZNET_2/sht21_driver" -I"C:/Users/alperen/Desktop/WIZNET_2/w5500_driver" -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Ethernet" -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Application/multicast" -I../Drivers/CMSIS/Include -I../Drivers/STM32F3xx_HAL_Driver/Inc -I../Core/Inc -I"C:/Users/alperen/Desktop/WIZNET_2/MyLibrary/Application/loopback" -I"C:/Users/alperen/Desktop/WIZNET_2/lcd20x4_driver" -I../Drivers/STM32F3xx_HAL_Driver/Inc/Legacy -I"C:/Users/alperen/Desktop/WIZNET_2/flash_driver" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"multicast/multicast.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

