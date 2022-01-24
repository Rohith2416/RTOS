#include <stdio.h>
#include<driver/gpio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>

#define ALARM_PIN 15

void TaskLog(void *pv)
{
    while(1)
    {
    printf("sensor task logs\n");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void AlarmTask(void *pv)
{
    gpio_pad_select_gpio(ALARM_PIN);
    gpio_set_direction(ALARM_PIN,GPIO_MODE_OUTPUT);

    while(1)
    {
        gpio_set_level(ALARM_PIN,0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        gpio_set_level(ALARM_PIN,1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    xTaskCreate(TaskLog, "TaskLog" ,2048,NULL,5,NULL);
    xTaskCreate(AlarmTask, "AlarmTask" ,2048,NULL,5,NULL);
    printf("hello\n");
}

