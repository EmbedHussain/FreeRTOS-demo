#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* Shared objects */
QueueHandle_t speedQueue;
QueueHandle_t brakeQueue;
SemaphoreHandle_t buttonSem;
SemaphoreHandle_t printMutex;

/* -------- ISR Simulation -------- */
void ButtonISR_Task(void *params)
{
    while(1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("\n[ISR] Button Pressed!\n");
        xSemaphoreGive(buttonSem);
    }
}

/* -------- Sensor Task -------- */
void SensorTask(void *params)
{
    int speed = 0;

    while(1)
    {
        xSemaphoreTake(buttonSem, portMAX_DELAY);

        speed += 20;
        if(speed > 100) speed = 0;

        printf("[Sensor] Speed = %d\n", speed);

        xQueueSend(speedQueue, &speed, portMAX_DELAY);
    }
}

/* -------- Control Task -------- */
void ControlTask(void *params)
{
    int speed, brake;

    while(1)
    {
        xQueueReceive(speedQueue, &speed, portMAX_DELAY);

        brake = (speed > 60) ? 1 : 0;

        printf("[Control] Brake = %s\n", brake ? "ON" : "OFF");

        xQueueSend(brakeQueue, &brake, portMAX_DELAY);
    }
}

/* -------- Communication Task -------- */
void CommTask(void *params)
{
    int brake;

    while(1)
    {
        xQueueReceive(brakeQueue, &brake, portMAX_DELAY);

        xSemaphoreTake(printMutex, portMAX_DELAY);

        printf("[Comm] Sending Brake Status: %s\n",
               brake ? "ON" : "OFF");

        xSemaphoreGive(printMutex);
    }
}

/* -------- Main -------- */
int main(void)
{
    speedQueue = xQueueCreate(5, sizeof(int));
    brakeQueue = xQueueCreate(5, sizeof(int));

    buttonSem = xSemaphoreCreateBinary();
    printMutex = xSemaphoreCreateMutex();

    xTaskCreate(ButtonISR_Task, "ISR", 1024, NULL, 3, NULL);
    xTaskCreate(SensorTask, "Sensor", 1024, NULL, 2, NULL);
    xTaskCreate(ControlTask, "Control", 1024, NULL, 2, NULL);
    xTaskCreate(CommTask, "Comm", 1024, NULL, 1, NULL);

    vTaskStartScheduler();

    while(1);
}
