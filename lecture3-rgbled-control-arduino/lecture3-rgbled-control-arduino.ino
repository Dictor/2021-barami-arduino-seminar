int r, g, b = 0;
int color = 0;

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (Serial.available()) {
        int v = Serial.parseInt();
        if (color == 0) {
            r = v;
            color++;
        } else if (color == 1) {
            g = v;
            color++;
        } else if (color == 2) {
            b = v;
            color = 0;
        }
        Serial.print("r=");
        Serial.print(r);
        Serial.print(" g=");
        Serial.print(g);
        Serial.print(" b=");
        Serial.println(b);

        analogWrite(11, r);
        analogWrite(12, g);
        analogWrite(13, b);
    }
}