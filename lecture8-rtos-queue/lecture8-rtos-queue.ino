#include "src/DueFreeRTOS/FreeRTOS.h"
#include "src/DueFreeRTOS/task.h"
#include "src/DueFreeRTOS/queue.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct _Message
{
    char ID;
    char Data[20];
} Message;

QueueHandle_t MessageQueue;

void setup()
{
    Serial.begin(9600);
    MessageQueue = xQueueCreate(10, sizeof(Message *));
    if (MessageQueue == NULL)
    {
        Serial.println("Queue failure");
        return;
    }

    xTaskCreate(tskSensor, "Sensor", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(tskHeartbeat, "Heartbeat", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(tskSendMessage, "SendMessage", 200, NULL, 1, NULL);
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
        transmitMessage(createMessage("Value: 123"));
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void tskHeartbeat(void *params)
{
    while (1)
    {
        // check system
        transmitMessage(createMessage("Status: OK"));
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void tskSendMessage(void *params)
{
    Message *msg;
    char string[30];
    while (1)
    {
        xQueueReceive(MessageQueue, &msg, portMAX_DELAY);
        sprintf(string, "ID: %d, Data: %s", msg->ID, msg->Data);
        Serial.println(string);
        free(msg);
    }
}

Message *createMessage(const char *str)
{
    static unsigned int count;
    Message *handle = (Message *)malloc(sizeof(Message));
    handle->ID = count;
    strcpy(handle->Data, str);
    count++;
    return handle;
}

void transmitMessage(Message *msg)
{
    xQueueSendToBack(MessageQueue, msg, portMAX_DELAY);
}