#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/timers.h>

TimerHandle_t motor_timer_handle;

int count = 0;

void TurnMotorOFF(TimerHandle_t xTimer)
{
    count++;
    printf("turning motor off\n");
    if(count==5)
    {
    printf("turning  off timer\n");
    xTimerStop(xTimer,0);
    }
}


void app_main()
{
    motor_timer_handle = xTimerCreate("MotorOFF",pdMS_TO_TICKS(2000),pdTRUE,NULL,TurnMotorOFF);

xTimerStart(motor_timer_handle,0);

while(1)
{
    printf("main task\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
}

}



