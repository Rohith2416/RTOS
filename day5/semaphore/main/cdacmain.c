#include <stdio.h>
#include<driver/gpio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/queue.h>
#include<freertos/semphr.h>
#define ALARM_PIN 15

SemaphoreHandle_t sem;
void SensorTask(void *pv)
{
int sensor_data =0;
	
    while(1)
    {
    sensor_data++;
    printf("sensor task : send data %d \n",sensor_data);
    vTaskDelay(500 / portTICK_PERIOD_MS);
    
    if (sensor_data == 10)
    {
    xSemaphoreGive(sem);
    printf("sensor task :sensor data %d\n",sensor_data);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
    }	
    }
}

void ProcessingTask(void *pv)
{
    int recv_data = 0;
    while(1)
    {
       xSemaphoreTake(sem ,portMAX_DELAY);
        printf("processing task : recv data %d \n",recv_data);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
    }
}

void app_main()
{
sem = xSemaphoreCreateBinary();
    xTaskCreate(SensorTask, "SensorTask" ,2048,NULL,5,NULL);
    xTaskCreate(ProcessingTask, "ProcessingTask" ,2048,NULL,3,NULL);
    xSemaphoreTake(sem,portMAX_DELAY);
    printf("hello\n");
}

