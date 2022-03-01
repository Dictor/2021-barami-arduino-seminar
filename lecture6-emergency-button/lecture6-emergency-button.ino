volatile int state = 0;

void setup()
{
    attachInterrupt(3, emergency, RISING);
    Serial.begin(9600);
    state = 1;
}

void loop()
{
    if (state == 0)
    {
        Serial.println("on");
    }
    else
    {
        Serial.println("off");
    }
    delay(200);
}

void emergency()
{
    state = 0;
}