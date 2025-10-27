################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../FreeRTOS-Kernel/portable/CCRH/RH850_F1KM_S4/port.c 

S_SRCS += \
../FreeRTOS-Kernel/portable/CCRH/RH850_F1KM_S4/portasm.s 

ASSEMBLER_OBJS += \
FreeRTOS-Kernel/portable/CCRH/RH850_F1KM_S4/portasm.obj 

S_DEPS += \
FreeRTOS-Kernel/portable/CCRH/RH850_F1KM_S4/portasm.d 

COMPILER_OBJS += \
FreeRTOS-Kernel/portable/CCRH/RH850_F1KM_S4/port.obj 

C_DEPS += \
FreeRTOS-Kernel/portable/CCRH/RH850_F1KM_S4/port.d 

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS-Kernel/portable/CCRH/RH850_F1KM_S4/%.obj: ../FreeRTOS-Kernel/portable/CCRH/RH850_F1KM_S4/%.c 
	@echo 'Scanning and building file: $<'
	ccrh @"FreeRTOS-Kernel/portable/CCRH/RH850_F1KM_S4/cDepSubCommand.tmp" -o"$(@:%.obj=%.d)" -MT="$(@:%.d=%.obj)" -MT="$(@:%.obj=%.d)" -Xmsg_lang=english "$<"
	ccrh @"FreeRTOS-Kernel/portable/CCRH/RH850_F1KM_S4/cSubCommand.tmp" -Xmsg_lang=english "$<"


FreeRTOS-Kernel/portable/CCRH/RH850_F1KM_S4/%.obj: ../FreeRTOS-Kernel/portable/CCRH/RH850_F1KM_S4/%.s 
	@echo 'Scanning and building file: $<'
	ccrh @"FreeRTOS-Kernel/portable/CCRH/RH850_F1KM_S4/sDepSubCommand.tmp" -Xasm_option=-MF="$(@:%.obj=%.d)" -Xasm_option=-MT="$(@:%.d=%.obj)" -Xasm_option=-MT="$(@:%.obj=%.d)" -Xmsg_lang=english "$<"
	ccrh @"FreeRTOS-Kernel/portable/CCRH/RH850_F1KM_S4/sSubCommand.tmp" -Xmsg_lang=english  "$<"


