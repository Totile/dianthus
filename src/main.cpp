#include "Arduino.h"
#include "Joystick.h"
#include "debounce.h"

// Pinout definition
const int PIN_LED1 = 3;
const int PIN_BTN1 = 15;
const int PIN_LED2 = 4;
const int PIN_BTN2 = 16;
const int PIN_LED3 = 5;
const int PIN_BTN3 = 17;

// Joystick initialisation
// TODO try to set it as a Gamepad, not a joystick
Joystick_ Joystick;

void setup() {
    pinMode(PIN_BTN1, INPUT_PULLUP);
    pinMode(PIN_LED1, OUTPUT);

    Serial.begin(9600);
    Joystick.begin();
}

int lastStateBTN1 = 0;

void loop() {
    // rising edge detector
    int currentStateBTN1 = !digitalRead(PIN_BTN1);
    if (currentStateBTN1 != lastStateBTN1) {
        if (currentStateBTN1 == 1) {
            Serial.println("Button 1 pressed");
            digitalWrite(PIN_LED1, 1);
            Joystick.pressButton(0);
            lastStateBTN1 = 1;
        } else if (currentStateBTN1 == 0) {
            Serial.println("Button 1 released");
            digitalWrite(PIN_LED1, 0);
            Joystick.releaseButton(0);
            lastStateBTN1 = 0;
        }
    }
}