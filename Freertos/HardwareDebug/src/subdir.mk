################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../src/Freertos.c 

COMPILER_OBJS += \
src/Freertos.obj 

C_DEPS += \
src/Freertos.d 

# Each subdirectory must supply rules for building sources it contributes
src/%.obj: ../src/%.c 
	@echo 'Scanning and building file: $<'
	ccrh @"src/cDepSubCommand.tmp" -o"$(@:%.obj=%.d)" -MT="$(@:%.d=%.obj)" -MT="$(@:%.obj=%.d)" -Xmsg_lang=english "$<"
	ccrh @"src/cSubCommand.tmp" -Xmsg_lang=english "$<"


