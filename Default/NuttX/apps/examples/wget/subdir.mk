################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../NuttX/apps/examples/wget/host.c \
../NuttX/apps/examples/wget/target.c 

OBJS += \
./NuttX/apps/examples/wget/host.o \
./NuttX/apps/examples/wget/target.o 

C_DEPS += \
./NuttX/apps/examples/wget/host.d \
./NuttX/apps/examples/wget/target.d 


# Each subdirectory must supply rules for building sources it contributes
NuttX/apps/examples/wget/%.o: ../NuttX/apps/examples/wget/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


