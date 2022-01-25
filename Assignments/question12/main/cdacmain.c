#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <freertos/event_groups.h>

EventGroupHandle_t sensor;
TaskHandle_t xHandler_1;
TaskHandle_t xHandler_2;

const uint32_t first_bit=(1<<0);
const uint32_t all_bit=first_bit;

void Alarm_task(void *pvparameters)
{
    uint32_t result;
    
       
    printf("ALARM TASK  RUNNING\n");
    taskENTER_CRITICAL();
    {
        printf("I am in critical section\n");
        result = xEventGroupWaitBits(sensor,all_bit,pdTRUE,pdTRUE,pdMS_TO_TICKS(5000));
        printf("BIT OUT%d\n",result);
    }
    taskEXIT_CRITICAL();
    //vTaskDelay(1000/ portTICK_PERIOD_MS);
    

    
}
void Delay_task(void *pv)
{
    int count =0;
    while(1)
    {
        count++;
        printf("DALEY TASK RUNNING\n");
        if(count==3)
        {
            xEventGroupSetBits(sensor,first_bit);
        } 
    }
}
void app_main()
{
    sensor =xEventGroupCreate();
    BaseType_t result;
    
    
    result=xTaskCreate(Alarm_task,"Alarmtask_1",2048,NULL,5,&xHandler_1);

    if(result==pdPASS)
    {
        printf("Alarmtask created\n");
    }
    result=xTaskCreate(Delay_task,"Delaytask_1",2048,NULL,5,&xHandler_2);

    if(result==pdPASS)
    {
        printf("Alarm_task created\n");
    }
}
