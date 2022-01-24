#include <stdio.h>
#include<driver/gpio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/queue.h>
#include<freertos/semphr.h>
#define ALARM_PIN 15
TaskHandle_t processHandle;
TaskHandle_t sensorHandle;

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
    vTaskResume(processHandle);
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
       vTaskSuspend(NULL);
        printf("processing task : recv data %d \n",recv_data);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
    }
}

void app_main()
{
    xTaskCreate(SensorTask, "SensorTask" ,2048,NULL,5,&sensorHandle);
    xTaskCreate(ProcessingTask, "ProcessingTask" ,2048,NULL,3,&processHandle);
    printf("hello\n");
}

