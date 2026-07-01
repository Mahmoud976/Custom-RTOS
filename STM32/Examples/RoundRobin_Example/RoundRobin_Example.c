#include <RoundRobin_Example/RoundRobin_Example.h>

Task_ref TaskA;
Task_ref TaskB;
Task_ref TaskC;

GPIO_Config_Pin_t LEDA;
GPIO_Config_Pin_t LEDB;
GPIO_Config_Pin_t LEDC;


/*=============================
 * Task A
 *=============================*/
void TaskA_Function(void)
{
    while(1)
    {
        GPIO_TogglePin(PORTB, GPIO_PIN12);

        for(volatile uint32_t i=0;i<70000;i++);
    }
}


/*=============================
 * Task B
 *=============================*/
void TaskB_Function(void)
{
    while(1)
    {
        GPIO_TogglePin(PORTB, GPIO_PIN13);

        for(volatile uint32_t i=0;i<70000;i++);
    }
}


/*=============================
 * Task C
 *=============================*/
void TaskC_Function(void)
{
    while(1)
    {
        GPIO_TogglePin(PORTB, GPIO_PIN14);

        for(volatile uint32_t i=0;i<70000;i++);
    }
}


/*=============================
 * Initialization
 *=============================*/
void RoundRobin_Example_Init(void)
{

    /* LED1 */
    LEDA.PORTx = PORTB;
    LEDA.Pin_Number = GPIO_PIN12;
    LEDA.mode = GPIO_MODE_Output_PP;
    LEDA.Speed = GPIO_SPEED_10M;
    GPIO_InitPin(&LEDA);

    /* LED2 */
    LEDB.PORTx = PORTB;
    LEDB.Pin_Number = GPIO_PIN13;
    LEDB.mode = GPIO_MODE_Output_PP;
    LEDB.Speed = GPIO_SPEED_10M;
    GPIO_InitPin(&LEDB);

    /* LED3 */
    LEDC.PORTx = PORTB;
    LEDC.Pin_Number = GPIO_PIN14;
    LEDC.mode = GPIO_MODE_Output_PP;
    LEDC.Speed = GPIO_SPEED_10M;
    GPIO_InitPin(&LEDC);

    /************* Task A *************/
    TaskA.Stack_Size = 1024;
    TaskA.P_Task_Entry = TaskA_Function;
    TaskA.priority = 3;
    strcpy(TaskA.Task_Name,"Task A");

    /************* Task B *************/
    TaskB.Stack_Size = 1024;
    TaskB.P_Task_Entry = TaskB_Function;
    TaskB.priority = 3;
    strcpy(TaskB.Task_Name,"Task B");

    /************* Task C *************/
    TaskC.Stack_Size = 1024;
    TaskC.P_Task_Entry = TaskC_Function;
    TaskC.priority = 3;
    strcpy(TaskC.Task_Name,"Task C");

    MY_RTOS_Create_Task(&TaskA);
    MY_RTOS_Create_Task(&TaskB);
    MY_RTOS_Create_Task(&TaskC);

    MY_RTOS_Activate_Task(&TaskA);
    MY_RTOS_Activate_Task(&TaskB);
    MY_RTOS_Activate_Task(&TaskC);
}
