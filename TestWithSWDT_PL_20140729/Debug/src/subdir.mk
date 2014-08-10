################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/alu_test.c \
../src/cache_test.c \
../src/cpu_register_test.c \
../src/dma_test.c \
../src/extra_platform_init.c \
../src/fpu_test.c \
../src/gic_test.c \
../src/main.c \
../src/memory_test.c \
../src/peripheral_test.c \
../src/pl_test.c \
../src/platform.c \
../src/qspips_test.c \
../src/uart_com.c \
../src/vector.c 

LD_SRCS += \
../src/lscript.ld 

OBJS += \
./src/alu_test.o \
./src/cache_test.o \
./src/cpu_register_test.o \
./src/dma_test.o \
./src/extra_platform_init.o \
./src/fpu_test.o \
./src/gic_test.o \
./src/main.o \
./src/memory_test.o \
./src/peripheral_test.o \
./src/pl_test.o \
./src/platform.o \
./src/qspips_test.o \
./src/uart_com.o \
./src/vector.o 

C_DEPS += \
./src/alu_test.d \
./src/cache_test.d \
./src/cpu_register_test.d \
./src/dma_test.d \
./src/extra_platform_init.d \
./src/fpu_test.d \
./src/gic_test.d \
./src/main.d \
./src/memory_test.d \
./src/peripheral_test.d \
./src/pl_test.d \
./src/platform.d \
./src/qspips_test.d \
./src/uart_com.d \
./src/vector.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -I../../MicroZed_PLtest_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


