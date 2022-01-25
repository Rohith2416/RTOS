/* we can set priority for the tasks the sheduler prempt lower priority task with higher priority tasks,sheduler is a piece of code software it will figure out which task to run at each tick */

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
        
        num++;
        printf("SENSOR TASK  RUNNING: \n");
        
        vTaskDelay(100/ portTICK_PERIOD_MS);
    }
}
void Alarm_task(void *pv)
{
    int count=0; 
    while(1)
    {
     
        
        count++;
         printf("ALARM TASK  RUNNING: \n");
        vTaskDelay(1000/ portTICK_PERIOD_MS);
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
    result=xTaskCreate(Alarm_task,"Alarmtask_1",2048,NULL,15,&xHandler_2);

    if(result==pdPASS)
    {
        printf("Alarm_task created\n");
    }
}
