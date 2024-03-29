#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

TaskHandle_t xHandleTaskLog_1;
TaskHandle_t xHandleTaskLog_2;
eTaskState x;

void alarm_task(void *pv)
    while(1)
    {
        printf("ALARM_TASK RUNNING\n");
        vTaskDelay(1000/ portTICK_PERIOD_MS);
    }
}
void pressure_task(void *pv)
{
    uint32_t count=0;
    while(1)
    {
        count++;
        printf("PRESSURE_TASK RUNNING\n");
        vTaskDelay(1000/ portTICK_PERIOD_MS);
        if(count==5)
        {
            vTaskDelete(NULL);
        }
    }
}
void app_main()
{

    //y=uxTaskGetNumberOfTasks();

    BaseType_t result;
    
    result=xTaskCreate(alarm_task,"alarm_task",1024,NULL,5,&xHandleTaskLog_1);

    if(result==pdPASS)
    {
        printf("task_1 created\n");
    }
    result=xTaskCreate(pressure_task,"pressure_task",1024,NULL,5,&xHandleTaskLog_2);

    if(result==pdPASS)
    {
        printf("task_2 created\n");
    }
    while(1)
    {
     x=eTaskGetState( xHandleTaskLog_2 );
     switch(x)
     {
         case eRunning:
             printf("TI IS RUNNING\n");
             break;
         case eReady:
             printf("IT IS READY\n");
             break;
         case eDeleted:
             printf("IT IS DELETED\n");
             break;
         case eBlocked:
             printf("IT IS BLOCKED\n");
             break;
         case eSuspended:
             printf("IT IS SUSPEND\n");
             break;
         default:
             printf("UNKNOW STATE\n");
             break; 
        }  
     printf("STATE :%d\n",x);  
     vTaskDelay(1000/portTICK_PERIOD_MS);
    }

}
