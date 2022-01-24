#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>

TaskHandle_t xHandleTaskLog;

void TaskLog(void *pvParameters)
{
    printf("task logs\n");
    vTaskDelete(xHandleTaskLog);//this the API used to delete a task
}

void app_main()
{
    BaseType_t result;
    result = xTaskCreate(TaskLog, "TaskLog" ,2048,NULL,5,&xHandleTaskLog);
    if(result == pdPASS)
    {
        printf("tasklog created\n");
    }
}

