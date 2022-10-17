#include <Arduino.h>

#define MP_RWB_PIN 31

#define MP_A0_PIN 22
#define MP_A1_PIN 24
#define MP_A2_PIN 26
#define MP_A3_PIN 28
#define MP_A4_PIN 30
#define MP_A5_PIN 32
#define MP_A6_PIN 34
#define MP_A7_PIN 36
#define MP_A8_PIN 38
#define MP_A9_PIN 40
#define MP_A10_PIN 42
#define MP_A11_PIN 44
#define MP_A12_PIN 46
#define MP_A13_PIN 48
#define MP_A14_PIN 50
#define MP_A15_PIN 52

#define MP_D0_PIN 33
#define MP_D1_PIN 35
#define MP_D2_PIN 37
#define MP_D3_PIN 39
#define MP_D4_PIN 41
#define MP_D5_PIN 43
#define MP_D6_PIN 45
#define MP_D7_PIN 47

int mpAddressPins[16] = {MP_A0_PIN, MP_A1_PIN, MP_A2_PIN, MP_A3_PIN, MP_A4_PIN, MP_A5_PIN, MP_A6_PIN, MP_A7_PIN, MP_A8_PIN, MP_A9_PIN, MP_A10_PIN, MP_A11_PIN, MP_A12_PIN, MP_A13_PIN, MP_A14_PIN, MP_A15_PIN};
int mpDataPins[8] = {MP_D0_PIN, MP_D1_PIN, MP_D2_PIN, MP_D3_PIN, MP_D4_PIN, MP_D5_PIN, MP_D6_PIN, MP_D7_PIN};

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