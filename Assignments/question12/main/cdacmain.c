#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>


TaskHandle_t xHandler_1;



void Alarm_task(void *pv)
{
    int count=0;
    while(1)
    {
       
        printf("ALARM TASK  RUNNING\n");
        taskENTER_CRITICAL(NULL);
        count++;
        printf("I am in critical section\n");
        if(count==2)
        {
            taskEXIT_CRITICAL(NULL);
        }
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}
void app_main()
{
    BaseType_t result;
    
    
    result=xTaskCreate(Alarm_task,"Alarm_task",2048,NULL,5,&xHandler_1);

    if(result==pdPASS)
    {
        printf("Alarm_task created\n");
    }
}
