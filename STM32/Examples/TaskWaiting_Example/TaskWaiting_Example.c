#include <TaskWaiting_Example/TaskWaiting_Example.h>

Task_ref WaitTask1;
Task_ref WaitTask2;
Task_ref WaitTask3;

GPIO_Config_Pin_t WaitLED1;
GPIO_Config_Pin_t WaitLED2;
GPIO_Config_Pin_t WaitLED3;

/*======================================================
 *                Task 1
 *=====================================================*/
void WaitTask1_Function(void)
{
    while(1)
    {
        GPIO_TogglePin(PORTB, GPIO_PIN12);

        MY_RTOS_Task_Wait(500, &WaitTask1);
    }
}

/*======================================================
 *                Task 2
 *=====================================================*/
void WaitTask2_Function(void)
{
    while(1)
    {
        GPIO_TogglePin(PORTB, GPIO_PIN13);

        MY_RTOS_Task_Wait(300, &WaitTask2);
    }
}

/*======================================================
 *                Task 3
 *=====================================================*/
void WaitTask3_Function(void)
{
    while(1)
    {
        GPIO_TogglePin(PORTB, GPIO_PIN14);

        MY_RTOS_Task_Wait(700, &WaitTask3);
    }
}

/*======================================================
 *          Task Waiting Example Initialization
 *=====================================================*/
void TaskWaiting_Example_Init(void)
{
    /*------------- LED12 -------------*/
    WaitLED1.PORTx = PORTB;
    WaitLED1.Pin_Number = GPIO_PIN12;
    WaitLED1.mode = GPIO_MODE_Output_PP;
    WaitLED1.Speed = GPIO_SPEED_10M;
    GPIO_InitPin(&WaitLED1);

    /*------------- LED13 -------------*/
    WaitLED2.PORTx = PORTB;
    WaitLED2.Pin_Number = GPIO_PIN13;
    WaitLED2.mode = GPIO_MODE_Output_PP;
    WaitLED2.Speed = GPIO_SPEED_10M;
    GPIO_InitPin(&WaitLED2);

    /*------------- LED14 -------------*/
    WaitLED3.PORTx = PORTB;
    WaitLED3.Pin_Number = GPIO_PIN14;
    WaitLED3.mode = GPIO_MODE_Output_PP;
    WaitLED3.Speed = GPIO_SPEED_10M;
    GPIO_InitPin(&WaitLED3);

    /*------------- Task 1 -------------*/
    WaitTask1.Stack_Size = 1024;
    WaitTask1.P_Task_Entry = WaitTask1_Function;
    WaitTask1.priority = 3;
    strcpy(WaitTask1.Task_Name, "WaitTask1");

    /*------------- Task 2 -------------*/
    WaitTask2.Stack_Size = 1024;
    WaitTask2.P_Task_Entry = WaitTask2_Function;
    WaitTask2.priority = 3;
    strcpy(WaitTask2.Task_Name, "WaitTask2");

    /*------------- Task 3 -------------*/
    WaitTask3.Stack_Size = 1024;
    WaitTask3.P_Task_Entry = WaitTask3_Function;
    WaitTask3.priority = 3;
    strcpy(WaitTask3.Task_Name, "WaitTask3");

    /*------------- Create Tasks -------------*/
    MY_RTOS_Create_Task(&WaitTask1);
    MY_RTOS_Create_Task(&WaitTask2);
    MY_RTOS_Create_Task(&WaitTask3);

    /*------------- Activate Tasks -------------*/
    MY_RTOS_Activate_Task(&WaitTask1);
    MY_RTOS_Activate_Task(&WaitTask2);
    MY_RTOS_Activate_Task(&WaitTask3);
}
