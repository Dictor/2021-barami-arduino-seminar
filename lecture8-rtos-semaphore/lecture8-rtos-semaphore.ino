#include "src/DueFreeRTOS/FreeRTOS.h"
#include "src/DueFreeRTOS/task.h"
#include "src/DueFreeRTOS/semphr.h"

SemaphoreHandle_t UartSemaphore;

void setup()
{
    Serial.begin(9600);
    UartSemaphore = xSemaphoreCreateBinary();
    if (UartSemaphore == NULL)
    {
        Serial.println("Semaphore failure");
        return;
    }

    xTaskCreate(tskSensor, "Sensor", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(tskHeartbeat, "Heartbeat", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    vTaskStartScheduler();
    Serial.println("OS failure");
}

void loop()
{
}

void tskSensor(void *params)
{
    // init sensor io
    while (1)
    {
        // read and process sensor value
        transmitUART("Value: 123");
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void tskHeartbeat(void *params)
{
    while (1)
    {
        // check system
        transmitUART("Status: OK");
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void transmitUART(const char *str)
{
    if (xSemaphoreTake(UartSemaphore, portMAX_DELAY) == pdTRUE)
    {
        Serial.println("Acquire semaphore");
        Serial.println(str);
    }
    xSemaphoreGive(UartSemaphore);
    Serial.println("Release semaphore");
}