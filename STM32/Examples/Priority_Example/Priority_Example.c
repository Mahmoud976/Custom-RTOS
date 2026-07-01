
#include <Priority_Example/Priority_Example.h>





Task_ref Priority_High_Task;
Task_ref Priority_Medium_Task;
Task_ref Priority_Low_Task;

GPIO_Config_Pin_t LED1,LED2,LED3;



void Priority_High_Task_Function(void)
{
    while(1)
    {
        GPIO_TogglePin(PORTB, GPIO_PIN12);

        for(volatile int i=0;i<50000;i++);

        MY_RTOS_Terminate_Task(&Priority_High_Task);
    }
}



void Priority_Medium_Task_Function(void)
{
    while(1)
    {
        GPIO_TogglePin(PORTB, GPIO_PIN13);

        for(volatile int i=0;i<50000;i++);

        MY_RTOS_Terminate_Task(&Priority_Medium_Task);
    }
}



void Priority_Low_Task_Function(void)
{
    while(1)
    {
        GPIO_TogglePin(PORTB, GPIO_PIN14);

        for(volatile int i=0;i<50000;i++);

        MY_RTOS_Terminate_Task(&Priority_Low_Task);
    }
}




void Priority_Example_Init(void)
{


    LED1.PORTx=PORTB;
    LED1.Pin_Number=GPIO_PIN12;
    LED1.mode=GPIO_MODE_Output_PP;
    LED1.Speed=GPIO_SPEED_10M;
    GPIO_InitPin(&LED1);



    LED2.PORTx=PORTB;
    LED2.Pin_Number=GPIO_PIN13;
    LED2.mode=GPIO_MODE_Output_PP;
    LED2.Speed=GPIO_SPEED_10M;
    GPIO_InitPin(&LED2);



    LED3.PORTx=PORTB;
    LED3.Pin_Number=GPIO_PIN14;
    LED3.mode=GPIO_MODE_Output_PP;
    LED3.Speed=GPIO_SPEED_10M;
    GPIO_InitPin(&LED3);



    Priority_High_Task.Stack_Size=1024;
    Priority_High_Task.P_Task_Entry=Priority_High_Task_Function;
    Priority_High_Task.priority=5;


    Priority_Medium_Task.Stack_Size=1024;
    Priority_Medium_Task.P_Task_Entry=Priority_Medium_Task_Function;
    Priority_Medium_Task.priority=3;


    Priority_Low_Task.Stack_Size=1024;
    Priority_Low_Task.P_Task_Entry=Priority_Low_Task_Function;
    Priority_Low_Task.priority=1;



    MY_RTOS_Create_Task(&Priority_High_Task);
    MY_RTOS_Create_Task(&Priority_Medium_Task);
    MY_RTOS_Create_Task(&Priority_Low_Task);



    MY_RTOS_Activate_Task(&Priority_Low_Task);
    MY_RTOS_Activate_Task(&Priority_Medium_Task);
    MY_RTOS_Activate_Task(&Priority_High_Task);

}
