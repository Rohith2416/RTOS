#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <freertos/event_groups.h>

//when other task are not running the idle task will run...

volatile uint32_t ulIdleCycleCount = 0;
TaskHandle_t xHandler_1;
TaskHandle_t xHandler_2;

void sensor_task(void *pv)
{
    while(1)
    {
        printf("SENSOR TASK  RUNNING \n");
        printf("REMAINING TIME :%ld\n",ulIdleCycleCount);
        vTaskDelay(250/ portTICK_PERIOD_MS);
        
    }
}
void Alarm_task(void *pv)
{ 
    while(1)
    {
        printf("ALARM TASK RUNNING \n");
        printf("REMAINING TIME :%ld\n",ulIdleCycleCount);
        vTaskDelay(250/ portTICK_PERIOD_MS);
        
    }
}
void idle_task(void *pv)                                              //idle task
{
    ulIdleCycleCount++;
}
void app_main()
{
    BaseType_t result;
    
    
    result=xTaskCreate(sensor_task,"sensor_task",2048,NULL,15,&xHandler_1);

    if(result==pdPASS)
    {
        printf("sensortask created\n");
    }
    result=xTaskCreate(Alarm_task,"Alarm_task",2048,NULL,5,&xHandler_2);

    if(result==pdPASS)
    {
        printf("Alarmtask created\n");
    }
    result=xTaskCreate(idle_task,"idletask",2048,NULL,0,NULL);
    
}
