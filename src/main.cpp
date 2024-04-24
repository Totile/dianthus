#include "Arduino.h"
#include "Joystick.h"
#include "debounce.h"

// Pinout definition
const int PIN_LED1 = 3;
const int PIN_BTN1 = 15;
const int PIN_LED2 = 4;
const int PIN_BTN2 = 14;
const int PIN_LED3 = 5;
const int PIN_BTN3 = 16;

// Joystick initialisation
// TODO try to set it as a Gamepad, not a joystick
Joystick_ Joystick;

void buttonHandler(uint8_t btnID, uint8_t btnSTate) {
    if (btnSTate == BTN_PRESSED) {
        Joystick.pressButton(btnID);
        Serial.print("Button ");
        Serial.print(btnID);
        Serial.println(" pressed");
        digitalWrite(PIN_LED1, 1);
    } else {
        Joystick.releaseButton(btnID);
        Serial.print("Button ");
        Serial.print(btnID);
        Serial.println(" released");
        digitalWrite(PIN_LED1, 0);
    }
}

static Button btn1(0, buttonHandler);
static Button btn2(1, buttonHandler);
static Button btn3(2, buttonHandler);

void setup() {
    pinMode(PIN_BTN1, INPUT_PULLUP);
    pinMode(PIN_BTN2, INPUT_PULLUP);
    pinMode(PIN_BTN3, INPUT_PULLUP);
    pinMode(PIN_LED1, OUTPUT);

    Serial.begin(9600);
    Joystick.begin();
}

static void pollButtons() {
    btn1.update(digitalRead(PIN_BTN1));
    btn2.update(digitalRead(PIN_BTN2));
    btn3.update(digitalRead(PIN_BTN3));
}

void loop() {
    pollButtons();
    delay(10);
}