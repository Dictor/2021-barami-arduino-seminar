#include "src/DueTimer/DueTimer.h"

void setup()
{
    Serial.begin(9600);
    DueTimer myTimer = Timer.getAvailable();
    myTimer.attachInterrupt(tick);
    myTimer.start(1000000);
}

void loop()
{
    Serial.println("loop task!");
    delay(500);
}

void tick()
{
    Serial.println("timer task!");
}