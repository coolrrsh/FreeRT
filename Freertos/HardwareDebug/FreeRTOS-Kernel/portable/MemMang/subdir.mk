################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../FreeRTOS-Kernel/portable/MemMang/heap_4.c 

COMPILER_OBJS += \
FreeRTOS-Kernel/portable/MemMang/heap_4.obj 

C_DEPS += \
FreeRTOS-Kernel/portable/MemMang/heap_4.d 

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS-Kernel/portable/MemMang/%.obj: ../FreeRTOS-Kernel/portable/MemMang/%.c 
	@echo 'Scanning and building file: $<'
	ccrh @"FreeRTOS-Kernel/portable/MemMang/cDepSubCommand.tmp" -o"$(@:%.obj=%.d)" -MT="$(@:%.d=%.obj)" -MT="$(@:%.obj=%.d)" -Xmsg_lang=english "$<"
	ccrh @"FreeRTOS-Kernel/portable/MemMang/cSubCommand.tmp" -Xmsg_lang=english "$<"


