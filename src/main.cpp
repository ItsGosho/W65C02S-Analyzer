#include <Arduino.h>

int mpAddressPins[16] = {22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52};
int mpDataPins[8] = {31, 33, 35, 37, 39, 41, 43, 45};

template<typename T, size_t N>
void setPinsMode(T (& pinNumbers)[N], const byte& mode) {
    for (size_t i = 0; i < N; i++) {
        pinMode(pinNumbers[i], mode);
    }
}


void setup() {
    Serial.begin(9600);

    setPinsMode(mpAddressPins, INPUT);
    setPinsMode(mpDataPins, INPUT);
}

void loop() {
// write your code here
}