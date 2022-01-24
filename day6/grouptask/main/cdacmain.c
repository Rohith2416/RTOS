#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/timers.h>
#include<freertos/event_groups.h>

TaskHandle_t temp_handle;
TaskHandle_t pres_handle;
TaskHandle_t cali_handle;

EventGroupHandle_t sensor_eg;
const uint32_t temp_event_bit = (1<<0);
const uint32_t pres_event_bit = (1<<1);
const uint32_t all_bit = (temp_event_bit | pres_event_bit);
void TemperatureTask(void *pv)
{
    while(1)
    {
        printf("temperature task\n");
        xEventGroupSetBits(sensor_eg,temp_event_bit);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    
}
void PressureTask(void *pv)
{
    while(1)
    {
        printf("pressure task\n");
        xEventGroupSetBits(sensor_eg,pres_event_bit);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    
}
void CalibrationTask(void *pv)
{
    uint32_t result ;
    while(1)
    {
    printf("calibration task\n");
    result = xEventGroupWaitBits(sensor_eg, all_bit ,pdTRUE,pdTRUE,pdMS_TO_TICKS(5000));
    printf("results %d \n",result);
    }
    vTaskDelete(NULL);
}


void app_main()
{
    sensor_eg = xEventGroupCreate();




    xTaskCreate(TemperatureTask,"TempratureTask",2048,NULL,5,&temp_handle);
    xTaskCreate(PressureTask,"PressureTask",2048,NULL,5,&pres_handle);
    xTaskCreate(CalibrationTask,"CalibrationTask",2048,NULL,5,&cali_handle);


while(1)
{
    printf("main task\n");
    vTaskDelay(pdMS_TO_TICKS(1000));
}

}



