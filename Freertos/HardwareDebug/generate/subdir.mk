################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
ASM_SRCS += \
../generate/boot.asm \
../generate/cstart.asm 

ASSEMBLER_OBJS += \
generate/boot.obj \
generate/cstart.obj 

ASM_DEPS += \
generate/boot.d \
generate/cstart.d 

# Each subdirectory must supply rules for building sources it contributes
generate/%.obj: ../generate/%.asm 
	@echo 'Scanning and building file: $<'
	ccrh @"generate/asmDepSubCommand.tmp" -Xasm_option=-MF="$(@:%.obj=%.d)" -Xasm_option=-MT="$(@:%.d=%.obj)" -Xasm_option=-MT="$(@:%.obj=%.d)" -Xmsg_lang=english "$<"
	ccrh @"generate/asmSubCommand.tmp" -Xmsg_lang=english  "$<"


