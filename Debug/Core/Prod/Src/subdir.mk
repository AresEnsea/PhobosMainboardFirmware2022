################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Prod/Src/avoidance.c \
../Core/Prod/Src/bezier.c \
../Core/Prod/Src/drv8825.c \
../Core/Prod/Src/lidar.c \
../Core/Prod/Src/odometry.c \
../Core/Prod/Src/propulsion.c \
../Core/Prod/Src/serial.c \
../Core/Prod/Src/strategy.c \
../Core/Prod/Src/symetry.c \
../Core/Prod/Src/vector2.c 

OBJS += \
./Core/Prod/Src/avoidance.o \
./Core/Prod/Src/bezier.o \
./Core/Prod/Src/drv8825.o \
./Core/Prod/Src/lidar.o \
./Core/Prod/Src/odometry.o \
./Core/Prod/Src/propulsion.o \
./Core/Prod/Src/serial.o \
./Core/Prod/Src/strategy.o \
./Core/Prod/Src/symetry.o \
./Core/Prod/Src/vector2.o 

C_DEPS += \
./Core/Prod/Src/avoidance.d \
./Core/Prod/Src/bezier.d \
./Core/Prod/Src/drv8825.d \
./Core/Prod/Src/lidar.d \
./Core/Prod/Src/odometry.d \
./Core/Prod/Src/propulsion.d \
./Core/Prod/Src/serial.d \
./Core/Prod/Src/strategy.d \
./Core/Prod/Src/symetry.d \
./Core/Prod/Src/vector2.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Prod/Src/%.o Core/Prod/Src/%.su: ../Core/Prod/Src/%.c Core/Prod/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F446xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/Prod/Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-Prod-2f-Src

clean-Core-2f-Prod-2f-Src:
	-$(RM) ./Core/Prod/Src/avoidance.d ./Core/Prod/Src/avoidance.o ./Core/Prod/Src/avoidance.su ./Core/Prod/Src/bezier.d ./Core/Prod/Src/bezier.o ./Core/Prod/Src/bezier.su ./Core/Prod/Src/drv8825.d ./Core/Prod/Src/drv8825.o ./Core/Prod/Src/drv8825.su ./Core/Prod/Src/lidar.d ./Core/Prod/Src/lidar.o ./Core/Prod/Src/lidar.su ./Core/Prod/Src/odometry.d ./Core/Prod/Src/odometry.o ./Core/Prod/Src/odometry.su ./Core/Prod/Src/propulsion.d ./Core/Prod/Src/propulsion.o ./Core/Prod/Src/propulsion.su ./Core/Prod/Src/serial.d ./Core/Prod/Src/serial.o ./Core/Prod/Src/serial.su ./Core/Prod/Src/strategy.d ./Core/Prod/Src/strategy.o ./Core/Prod/Src/strategy.su ./Core/Prod/Src/symetry.d ./Core/Prod/Src/symetry.o ./Core/Prod/Src/symetry.su ./Core/Prod/Src/vector2.d ./Core/Prod/Src/vector2.o ./Core/Prod/Src/vector2.su

.PHONY: clean-Core-2f-Prod-2f-Src

