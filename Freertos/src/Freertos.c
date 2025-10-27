/***********************************************************************/
/*                                                                     */
/*  FILE        :Main.c                                                */
/*  DATE        :                                                      */
/*  DESCRIPTION :Main Program                                          */
/*  CPU TYPE    :                                                      */
/*                                                                     */
/*  NOTE:THIS IS A TYPICAL EXAMPLE.                                    */
/*                                                                     */
/***********************************************************************/

int main(void);

/* Standard includes. */
#include <stdio.h>
#include <stdint.h>

/* FreeRTOS includes. */
#include "FreeRTOS.h"
#include "task.h"

/*-----------------------------------------------------------*/
/* Task Definitions */
/*-----------------------------------------------------------*/

/* Shared variables */
static volatile int32_t a = 0;
static volatile int32_t b = 0;

/* Task function prototypes */
void vTask1_Incrementer( void *pvParameters );
void vTask2_Decrementer( void *pvParameters );

/*-----------------------------------------------------------*/

void vTask1_Incrementer( void *pvParameters )
{
    const TickType_t xDelay = pdMS_TO_TICKS( 10 );
    ( void ) pvParameters; /* Unused parameter */

    for( ;; )
    {
        // Enter a Critical Section to protect the shared variables
        taskENTER_CRITICAL();
        {
            a++;
            b++;
        }
        // Exit the Critical Section
        taskEXIT_CRITICAL();

        // Optional: Perform a volatile read for debugging/observation
        volatile int32_t current_a = a;
        volatile int32_t current_b = b;

        // Delay for a short period
        vTaskDelay( xDelay );
    }
}

/*-----------------------------------------------------------*/

void vTask2_Decrementer( void *pvParameters )
{
    const TickType_t xDelay = pdMS_TO_TICKS( 5 );
    ( void ) pvParameters; /* Unused parameter */

    for( ;; )
    {
        // Enter a Critical Section to protect the shared variables
        taskENTER_CRITICAL();
        {
            a--;
            b--;
        }
        // Exit the Critical Section
        taskEXIT_CRITICAL();

        // Optional: Perform a volatile read for debugging/observation
        volatile int32_t current_a = a;
        volatile int32_t current_b = b;

        // Delay for a short period (faster than Task 1)
        vTaskDelay( xDelay );
    }
}

/*-----------------------------------------------------------*/
/* Main function to setup tasks and start the scheduler */
/*-----------------------------------------------------------*/

/*LEDBLINK*/

#include "../generate/iodefine.h"

// Define a constant for the delay loop count (adjust this value to change the blink speed)
#define BLINK_DELAY_COUNT 1000000

/* Function prototypes */
void System_Init(void);
void LED_Init(void);
void LED_On(void);
void LED_Off(void);
void LED_Toggle(void);
void Delay(unsigned int count);

/**
 * @brief Initializes protected system registers (equivalent to PRCR unlock).
 * Uses SYS.PROTCMD0 to enable configuration writes.
 */
void System_Init(void)
{
    /* Unlock protected registers (SRPR equivalent of writing 0xA502) */
    /* 1. Write the command key (0xA5) to the command register (SYS.PROTCMD0) */
    SYS.PROTCMD0.UINT32 = 0x000000A5;
    /* 2. Set PCMD0 bit to 1 (Enable Write/Unlock) */
    SYS.PROTCMD0.BIT.PCMD0 = 1;
}

void Clock_Init_Comprehensive(void)
{
    /* Step 1: Enable main oscillator */
    SYS.MOSCE.BIT.MOSCENTRG = 1;      /* Enable main oscillator */

    /* Wait for oscillator stabilization */
    while(SYS.MOSCS.BIT.MOSCCLKACT == 0)
    {
        Delay(100);
    }

    /* Step 2: Enable various system clocks */
    /* Enable peripheral clocks */
    SYS.CKSC_IPCRSCANS_CTL.BIT.PCRSCANSSTP = 0;  /* Peripheral clock */
    SYS.CKSC_IPCETNBS_CTL.BIT.IPCETNBSSTP = 0;   /* Peripheral bus clock */

    /* Enable other essential clocks */
    SYS.CKSC_IXCCLKS_CTL.BIT.XCCLKSSTP = 0;      /* System clock */
    SYS.CKSC_IXCETNBS_CTL.BIT.IXCETNBSSTP = 0;   /* External bus clock */

    /* Step 3: Enable specific peripheral clocks that might be needed for GPIO */
    SYS.CKSC_IISMS_CTL.BIT.ISMSCSID0 = 0;        /* Interface module clock */
    SYS.CKSC_ILCBIS_CTL.BIT.LCBISCSID0 = 0;      /* Local bus clock */

    /* Wait for clocks to stabilize */
    Delay(1000);
}

/**
 * @brief Initializes the P16_11 pin for output (LED).
 * Assumes the LED is active-low (sets low to turn ON).
 *
 * This function uses PORT_ISO registers for Pin Function Control,
 * configuring P16_11 as a General-Purpose Output.
 */
void LED_Init(void)
{
    /* --- 1. Configure Pin P16_11 function using PORT_ISO Registers (for GPIO) --- */

    /* PFCE (Pin Function Control Enable): 0 = Disable Alternative Function (enforces GPIO mode) */
    PORT_ISO.PFCE16.BIT.PFCE16_11 = 0;

    /* PFC (Pin Function Control): 0 = GPIO Function */
    PORT_ISO.PFC16.BIT.PFC16_11 = 0;

    /* PMC (Port Mode Control): 0 = Standard Pin Function (Digital I/O, not analog) */
    PORT_ISO.PMC16.BIT.PMC16_11 = 0;

    /* PM (Pin Mode/Direction Register): 0 = Output Direction */
    PORT_ISO.PM16.BIT.PM16_11 = 0;

    /* Initial state HIGH (LED OFF for active-low) using the atomic Set Register bit 11 */
    PORT_ISO.PSR16.BIT.PSR16_11 = 1;

    /* --- 2. Lock system protection register (SRPR equivalent of writing 0xA500) --- */
    /* 1. Write the command key (0xA5) to the command register (SYS.PROTCMD0) */
    SYS.PROTCMD0.UINT32 = 0x000000A5;
    /* 2. Clear PCMD0 bit to 0 (Disable Write/Lock) */
    SYS.PROTCMD0.BIT.PCMD0 = 0;
}

/**
 * @brief Turns the LED ON (Sets P16_11 LOW, assuming active low).
 * Uses the atomic Port Clear mechanism: PSR16 bit 27 (11 + 16).
 */
void LED_On(void)
{
    /* Writing 1 to PSR16_27 clears the P16_11 output to 0 (ON) */
    PORT_ISO.PSR16.BIT.PSR16_27 = 1;
}

/**
 * @brief Turns the LED OFF (Sets P16_11 HIGH).
 * Uses the atomic Port Set mechanism: PSR16 bit 11.
 */
void LED_Off(void)
{
    /* Writing 1 to PSR16_11 sets the P16_11 output to 1 (OFF) */
    PORT_ISO.PSR16.BIT.PSR16_11 = 1;
}

/**
 * @brief Toggles the LED state.
 * Uses the atomic Port Not Register (PNOT16).
 */
void LED_Toggle(void)
{
    /* Writing 1 to PNOT16_11 toggles the P16_11 output bit */
    PORT_ISO.PNOT16.BIT.PNOT16_11 = 1;
}

/**
 * @brief Simple software delay (blocking busy-loop).
 * NOTE: The exact delay time depends on the MCU clock speed.
 * @param count The loop iteration count.
 */
void Delay(unsigned int count)
{
    volatile unsigned int i;
    for(i = 0; i < count; i++);
}

/**
 * @brief Main application entry point for the microcontroller.
 */
int led_main(void)
{
    /* Initialize system protection settings */
	Clock_Init_Comprehensive();
    System_Init();

    Delay(10000);
    /* Initialize P16_11 for LED control */
    LED_Init();

    Delay(10000);

    LED_Off();               /* Turn LED ON (Sets P16_11 to 0) */
    Delay(BLINK_DELAY_COUNT);
   //     LED_Off();              /* Turn LED OFF (Sets P16_11 to 1) */
    Delay(BLINK_DELAY_COUNT);
    /* Main loop for blinking */
    while(1)
    {
                   // Turn LED OFF (Sets P16_11 to 1)
        Delay(BLINK_DELAY_COUNT);

        LED_Toggle();
    }

    return 0; /* Should not be reached in embedded systems main loop */
}


//LEDBLINK

int main(void)
{
    // 1. Create the tasks

	led_main();
/*
    // Task 1: Increments 'a' and 'b'
    xTaskCreate( vTask1_Incrementer,       // The task function
                 "Inc",                    // The name of the task (for debugging)
                 configMINIMAL_STACK_SIZE, // The stack size
                 NULL,                     // Task parameter
                 tskIDLE_PRIORITY + 1,     // The priority (1 higher than idle)
                 NULL );                   // Task handle (not used here)

    // Task 2: Decrements 'a' and 'b'
    xTaskCreate( vTask2_Decrementer,       // The task function
                 "Dec",                    // The name of the task (for debugging)
                 configMINIMAL_STACK_SIZE, // The stack size
                 NULL,                     // Task parameter
                 tskIDLE_PRIORITY + 2,     // The priority (2 higher than idle)
                 NULL );                   // Task handle (not used here)

    // 2. Start the FreeRTOS scheduler
    vTaskStartScheduler();

    // Scheduler should never return, but if it does, it indicates a failure.
    for( ;; )
    {
        // Should not be reached
    }
*/
    return 0;
}
