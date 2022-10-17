#include <Arduino.h>

#define MP_RWB_PIN 31


int mpAddressPins[16] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52};
int mpDataPins[8] = {33, 35, 37, 39, 41, 43, 45, 47};

template<typename T, size_t N>
void pinModes(T (& pinNumbers)[N], const byte& mode) {
    for (size_t i = 0; i < N; i++) {
        pinMode(pinNumbers[i], mode);
    }
}


void setup() {
    Serial.begin(9600);

    pinMode(MP_RWB_PIN, INPUT);
    pinModes(mpAddressPins, INPUT);
    pinModes(mpDataPins, INPUT);
}

void loop() {
// write your code here
}