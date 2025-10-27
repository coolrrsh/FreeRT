################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables
C_SRCS += \
../FreeRTOS-Kernel/croutine.c \
../FreeRTOS-Kernel/event_groups.c \
../FreeRTOS-Kernel/list.c \
../FreeRTOS-Kernel/queue.c \
../FreeRTOS-Kernel/stream_buffer.c \
../FreeRTOS-Kernel/tasks.c \
../FreeRTOS-Kernel/timers.c 

COMPILER_OBJS += \
FreeRTOS-Kernel/croutine.obj \
FreeRTOS-Kernel/event_groups.obj \
FreeRTOS-Kernel/list.obj \
FreeRTOS-Kernel/queue.obj \
FreeRTOS-Kernel/stream_buffer.obj \
FreeRTOS-Kernel/tasks.obj \
FreeRTOS-Kernel/timers.obj 

C_DEPS += \
FreeRTOS-Kernel/croutine.d \
FreeRTOS-Kernel/event_groups.d \
FreeRTOS-Kernel/list.d \
FreeRTOS-Kernel/queue.d \
FreeRTOS-Kernel/stream_buffer.d \
FreeRTOS-Kernel/tasks.d \
FreeRTOS-Kernel/timers.d 

# Each subdirectory must supply rules for building sources it contributes
FreeRTOS-Kernel/%.obj: ../FreeRTOS-Kernel/%.c 
	@echo 'Scanning and building file: $<'
	ccrh @"FreeRTOS-Kernel/cDepSubCommand.tmp" -o"$(@:%.obj=%.d)" -MT="$(@:%.d=%.obj)" -MT="$(@:%.obj=%.d)" -Xmsg_lang=english "$<"
	ccrh @"FreeRTOS-Kernel/cSubCommand.tmp" -Xmsg_lang=english "$<"


