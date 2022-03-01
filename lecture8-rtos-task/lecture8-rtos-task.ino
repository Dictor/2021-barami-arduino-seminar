#include "src/DueFreeRTOS/FreeRTOS.h"
#include "src/DueFreeRTOS/task.h"

void setup()
{
    Serial.begin(9600);
    xTaskCreate(tskCheckCore, "CheckCore", configMINIMAL_STACK_SIZE, NULL, 1, NULL);
    xTaskCreate(tskPump, "Pump", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(tskControl, "Control", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    vTaskStartScheduler();
    Serial.println("OS failure");
}

void loop()
{
}

void tskCheckCore(void *params)
{
    while (1)
    {
        Serial.println("[tskCheckCore] Check core");
        Serial.println("[tskCheckCore] Control core");
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

void tskPump(void *params)
{
    while (1)
    {
        Serial.println("[tskPump] Check pump status");
        Serial.println("[tskPump] Control pump");
        vTaskDelay(pdMS_TO_TICKS(3000));
    }
}

void tskControl(void *params)
{
    while (1)
    {
        Serial.println("[tskControl] Check input");
        Serial.println("[tskControl] Control UI");
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}