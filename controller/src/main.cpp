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

void buttonHandler(uint8_t btnID, uint8_t btnSTate) {
    if (btnSTate == BTN_PRESSED) {
        Joystick.pressButton(btnID);
        Serial.print("Button ");
        Serial.print(btnID);
        Serial.println(" pressed");
        digitalWrite(lampPin[1], 1);
    } else {
        Joystick.releaseButton(btnID);
        Serial.print("Button ");
        Serial.print(btnID);
        Serial.println(" released");
        digitalWrite(lampPin[1], 0);
    }
}

Button btnArr[btnCount] = {};

void setup() {
    for (int i = 0; i < btnCount; i++) {
        pinMode(btnPin[i], INPUT_PULLUP);
    }
    for (int i = 0; i < lampCount; i++) {
        pinMode(lampPin[i], OUTPUT);
    }
    for (int i = 0; i < btnCount; i++) {
        const Button tempBtn(i, buttonHandler);
        btnArr[i] = tempBtn;
    }
    digitalWrite(lampPin[2], 1);
    digitalWrite(lampPin[3], 1);

    Serial.begin(9600);
    Joystick.begin();
}

static void pollButtons() {
    for (int i = 0; i < btnCount; i++) {
        int state = digitalRead(btnPin[i]);
        btnArr[i].update(state);
    }
}

void loop() {
    pollButtons();
    delay(1);
}