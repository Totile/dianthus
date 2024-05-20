#include "Arduino.h"
#include "Joystick.h"
#include "debounce.h"

// Pinout definition
constexpr int lampCount = 6;
constexpr int btnCount = 8;
const int lampPin[lampCount] = {10, 14, A0, A2, 9, 4};
const int btnPin[btnCount] = {16, 15, A1, A3, 8, 7, 6, 5};
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
static Button btn4(3, buttonHandler);
static Button btn5(4, buttonHandler);
static Button btn6(5, buttonHandler);
static Button btn7(6, buttonHandler);
static Button btn8(7, buttonHandler);
static Button btnArr[btnCount] = {btn1, btn2, btn3, btn4,
                                  btn5, btn6, btn7, btn8};

void setup() {
    pinMode(btnPin[0], INPUT_PULLUP);
    pinMode(btnPin[1], INPUT_PULLUP);
    pinMode(btnPin[2], INPUT_PULLUP);
    pinMode(btnPin[3], INPUT_PULLUP);
    pinMode(btnPin[4], INPUT_PULLUP);
    pinMode(btnPin[5], INPUT_PULLUP);
    pinMode(btnPin[6], INPUT_PULLUP);
    pinMode(btnPin[7], INPUT_PULLUP);
    pinMode(PIN_LED1, OUTPUT);

    Serial.begin(9600);
    Joystick.begin();
}

static void pollButtons() {
    btn1.update(digitalRead(btnPin[0]));
    btn2.update(digitalRead(btnPin[1]));
    btn3.update(digitalRead(btnPin[2]));
    btn4.update(digitalRead(btnPin[3]));
    btn5.update(digitalRead(btnPin[4]));
    btn6.update(digitalRead(btnPin[5]));
    btn7.update(digitalRead(btnPin[6]));
    btn8.update(digitalRead(btnPin[7]));
}

void loop() {
    pollButtons();
    delay(25);
}