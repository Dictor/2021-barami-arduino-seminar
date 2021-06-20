void setup() {
    pinMode(11, OUTPUT);
}

void loop() {
    bool enable = true;
    unsigned int freq = 100;
    while(enable) {
        digitalWrite(11, HIGH);
        delayMicroseconds(1000000 / (freq * 2));
        digitalWrite(11, LOW);
        delayMicroseconds(1000000 / (freq * 2));
    }
}