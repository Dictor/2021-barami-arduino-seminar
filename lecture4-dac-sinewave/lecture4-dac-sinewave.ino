#include <math.h>

void setup() {
    analogWriteResolution(12);
}

void loop() {
    for (float x; x < M_PI; x += 0.05f) {
        analogWrite(DAC0, (int)((1 + sinf(x)) * 2048));
    }
}