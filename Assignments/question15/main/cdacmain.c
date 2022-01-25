#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>


TaskHandle_t xHandler_1;
TaskHandle_t xHandler_2;


void sensor_task(void *pv)
{
    int num=0;
    while(1)
    {
        printf("SENSOR TASK  RUNNING: \n");
        num++;
        
        if(num==12)
        {
              vTaskResume(xHandler_2); 
              num=0;  
        }
        vTaskDelay(100/ portTICK_PERIOD_MS);
    }
}
void Alarm_task(void *pv)
{
    int count=0; 
    while(1)
    {
        
        printf("ALARM_TASK \n");
        
        count++;
        if(count==12)
        {
            vTaskSuspend(NULL);
            printf("ALARM TASK SUSPENDED AFTER 1200ms\n");
            count=0;
        }
        vTaskDelay(100/ portTICK_PERIOD_MS);
    }
}
void app_main()
{
    BaseType_t result;
    
    result=xTaskCreate(sensor_task,"sensortask_1",2048,NULL,5,&xHandler_1);

    if(result==pdPASS)
    {
        printf("sensortask created\n");
    }
    result=xTaskCreate(Alarm_task,"Alarmtask_1",2048,NULL,5,&xHandler_2);

    if(result==pdPASS)
    {
        printf("Alarm_task created\n");
    }
}
