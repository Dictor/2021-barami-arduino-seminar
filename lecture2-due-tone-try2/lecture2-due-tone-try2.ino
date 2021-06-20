long now, last;
int status;

void setup() {
    pinMode(11, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    now = micros();
    if (now - last > 5000) {
        status = status == HIGH ? LOW : HIGH;
        digitalWrite(11, status);
        last = now;
    } else {
    // other task
        Serial.println(status);
    } 
}
