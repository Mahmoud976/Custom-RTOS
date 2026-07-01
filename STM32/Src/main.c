/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Mahmoud Saleh
 * @brief          : Main program body
 ******************************************************************************
 */


#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include <Mutex_Example/Mutex_Example.h>
#include <Priority_Example/Priority_Example.h>
#include <Priority_Preemption_Example/Priority_Preemption_Example.h>
#include <RoundRobin_Example/RoundRobin_Example.h>
#include <TaskWaiting_Example/TaskWaiting_Example.h>

int main(void)
{

    /* Initialize Hardware (Clock, Reset Controller, etc.) */
    HW_Init();


    /* Initialize RTOS */
    if(MY_RTOS_Init() != NO_ERROR)
    {
        while(1);
    }


    /* Initialize selected RTOS Example
     * Active one function to test it */
    //Mutex_Example_Init();
    //Priority_Example_Init();
    //Priority_Preemption_Example_Init();
    //RoundRobin_Example_Init();
    TaskWaiting_Example_Init();

    /* Start RTOS Scheduler */
    MY_RTOS_START_OS();



    while(1)
    {
        __asm("NOP");
    }

}
