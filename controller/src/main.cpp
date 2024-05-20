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
        digitalWrite(lampPin[0], 1);
    } else {
        Joystick.releaseButton(btnID);
        Serial.print("Button ");
        Serial.print(btnID);
        Serial.println(" released");
        digitalWrite(lampPin[0], 0);
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
    for (int i = 0; i < btnCount; i++) {
        pinMode(btnPin[i], INPUT_PULLUP);
    }
    for (int i = 0; i < lampCount; i++) {
        pinMode(lampPin[i], OUTPUT);
    }
<<<<<<< Updated upstream
=======
    for (int i = 0; i < btnCount; i++) {
        const Button tempBtn(i, buttonHandler);
        btnArr[i] = tempBtn;
    }
    digitalWrite(lampPin[2], 1);
>>>>>>> Stashed changes

    Serial.begin(9600);
    Joystick.begin();
}

static void pollButtons() {
    for (int i = 0; i < btnCount; i++) {
        btnArr[i].update(digitalRead(btnPin[i]));
    }
}

void loop() {
    pollButtons();
    delay(1);
}