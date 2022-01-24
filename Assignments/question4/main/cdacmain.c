#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>


TaskHandle_t xHandler_1;
TaskHandle_t xHandler_2;


void sensor_task(void *pvparameters)
{
    while(1)
    {
        printf("SENSOR TASK PRIORITY %d\n",uxTaskPriorityGet(NULL));
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}
void Alarm_task(void *pvparameters)
{
   
    while(1)
    {
        printf("ALARM TASK PRIORITY %d\n",uxTaskPriorityGet(NULL));
        
        vTaskDelay(2000/ portTICK_PERIOD_MS);
    }
}
void app_main()
{
    BaseType_t result;
    
    result=xTaskCreate(sensor_task,"sensor_task",2048,NULL,10,&xHandler_1);

    if(result==pdPASS)
    {
        printf("sensortask created\n");
    }
    result=xTaskCreate(Alarm_task,"Alarm_task",2048,NULL,20,&xHandler_2);

    if(result==pdPASS)
    {
        printf("Alarmtask created\n");
    }
}
