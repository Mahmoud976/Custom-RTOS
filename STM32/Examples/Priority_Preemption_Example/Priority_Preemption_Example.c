#include <Priority_Preemption_Example/Priority_Preemption_Example.h>

/*===============================
 * Tasks
 *===============================*/
Task_ref Preemption_High_Task;
Task_ref Preemption_Low_Task;

/*===============================
 * GPIO
 *===============================*/

GPIO_Config_Pin_t Low_LED;
GPIO_Config_Pin_t High_LED;

/*===============================
 * High Priority Task
 *===============================*/

void Preemption_High_Task_Function(void)
{
    while (1)
    {
        GPIO_WritePin(PORTB, GPIO_PIN13, 1);

        for (volatile int i = 0; i < 70000; i++);

        GPIO_WritePin(PORTB, GPIO_PIN13, 0);

        MY_RTOS_Terminate_Task(&Preemption_High_Task);
    }
}

/*===============================
 * Low Priority Task
 *===============================*/

void Preemption_Low_Task_Function(void)
{
    while (1)
    {
        GPIO_WritePin(PORTB, GPIO_PIN12, 1);

        /* Simulate some processing */
        for (volatile int i = 0; i < 300000; i++);

        /* High Priority Task becomes READY */
        MY_RTOS_Activate_Task(&Preemption_High_Task);

        /*
         * If Preemption works correctly,
         * High_Task executes BEFORE this line.
         */

        GPIO_WritePin(PORTB, GPIO_PIN12, 0);

        MY_RTOS_Terminate_Task(&Preemption_Low_Task);
    }
}

/*===============================
 * Example Initialization
 *===============================*/

void Priority_Preemption_Example_Init(void)
{
    /* LED PB12 */

    Low_LED.PORTx = PORTB;
    Low_LED.Pin_Number = GPIO_PIN12;
    Low_LED.mode = GPIO_MODE_Output_PP;
    Low_LED.Speed = GPIO_SPEED_10M;
    GPIO_InitPin(&Low_LED);

    /* LED PB13 */

    High_LED.PORTx = PORTB;
    High_LED.Pin_Number = GPIO_PIN13;
    High_LED.mode = GPIO_MODE_Output_PP;
    High_LED.Speed = GPIO_SPEED_10M;
    GPIO_InitPin(&High_LED);

    /*--------------- Low Task ---------------*/

    Preemption_Low_Task.Stack_Size = 1024;
    Preemption_Low_Task.P_Task_Entry = Preemption_Low_Task_Function;
    Preemption_Low_Task.priority = 5;
    strcpy(Preemption_Low_Task.Task_Name, "LOW TASK");

    /*--------------- High Task ---------------*/

    Preemption_High_Task.Stack_Size = 1024;
    Preemption_High_Task.P_Task_Entry = Preemption_High_Task_Function;
    Preemption_High_Task.priority = 1;
    strcpy(Preemption_High_Task.Task_Name, "HIGH TASK");

    MY_RTOS_Create_Task(&Preemption_Low_Task);
    MY_RTOS_Create_Task(&Preemption_High_Task);

    /* Only Low Task starts */

    MY_RTOS_Activate_Task(&Preemption_Low_Task);
}
