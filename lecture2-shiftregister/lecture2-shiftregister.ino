const int latchPin = 8;
const int clockPin = 12;
const int dataPin = 11;

void setup()
{
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
    Serial.begin(9600);
    Serial.println("reset");
}
void loop()
{
    if (Serial.available() > 0)
    {
        int bitToSet = Serial.read() - 48;
        registerWrite(bitToSet, HIGH);
    }
}

void registerWrite(int whichPin, int whichState)
{
    byte bitsToSend = 0;
    digitalWrite(latchPin, LOW);
    bitWrite(bitsToSend, whichPin, whichState);
    shiftOut(dataPin, clockPin, MSBFIRST, bitsToSend);
    digitalWrite(latchPin, HIGH);
    delay(1000);
}