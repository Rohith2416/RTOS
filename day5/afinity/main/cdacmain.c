#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>


void TaskLog(void *pv)
{
    while(1)
    {
    printf("sensor task logs %d \n",xTaskGetAffinity(NULL));
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    xTaskCreate(TaskLog, "TaskLog" ,2048,NULL,5,NULL);
    printf("hello\n");
}

