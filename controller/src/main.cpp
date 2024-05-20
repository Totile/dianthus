#include "Arduino.h"
#include "Joystick.h"
#include "debounce.h"

// Pinout definition
constexpr int lampCount = 6;
constexpr int btnCount = 8;
const int lampPin[lampCount] = {10, 14, A0, A2, 9, 4};
const int btnPin[btnCount] = {16, 15, A1, A3, 8, 7, 6, 5};

// Joystick initialisation
// TODO try to set it as a Gamepad, not a joystick
Joystick_ Joystick;

Button btnArr[btnCount] = {};

void setup() {
    for (int i = 0; i < btnCount; i++) {
        pinMode(btnPin[i], INPUT_PULLUP);
    }
    for (int i = 0; i < lampCount; i++) {
        pinMode(lampPin[i], OUTPUT);
    }

    Serial.begin(9600);
    Joystick.begin();
}

void loop() {
    for (int i = 0; i < btnCount; i++) {
        if (!digitalRead(btnPin[i])) {
            Joystick.pressButton(i);
            Serial.print(i);
            Serial.println(" button pressed");
        } else {
            Joystick.releaseButton(i);
        }
    }
    delay(25);
}