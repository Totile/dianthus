#include <seesaw_neopixel.h>

#include "Adafruit_MCP23X08.h"
#include "Adafruit_MCP23X17.h"
#include "Adafruit_seesaw.h"
#include "Arduino.h"
#include "Joystick.h"
#include "SPI.h"
#include "debounce.h"

// Pinout definition
constexpr int lampCount = 6;
constexpr int btnCount = 8;
constexpr int lampPin[lampCount] = {10, 14, A0, A2, 9, 4};
constexpr int btnPin[btnCount] = {16, 15, A1, A3, 8, 7, 6, 5};
constexpr int ss_switch = 24;
constexpr int ss_addr = 0x36;

// Joystick initialisation
// TODO try to set it as a Gamepad, not a joystick
Joystick_ Joystick;
Adafruit_seesaw ss;
int32_t encoder_position;
int16_t axis_position;
constexpr int step_factor = 4;

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
    Serial.begin(9600);

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
    Joystick.begin();
    // Joystick.setXAxisRange(-1, 1);
    // Joystick.setXAxisRange(-127, 127);
    // Joystick.setXAxisRange(-0x7FFFFFFF, 0x7FFFFFFF);
    // Joystick.setYAxisRange(-0xFFFFFFF, 0xFFFFFFF);

    if (!ss.begin(ss_addr)) {
        Serial.println("Couldn't finde seesaw on default address");
    }
    uint32_t version = ((ss.getVersion() >> 16) & 0xFFFF);
    if (version != 4991) {
        Serial.println("Wrong firmware loaded ?");
    }
    Serial.println("Found seesaw on default adress");
    encoder_position = ss.getEncoderPosition();
    Joystick.setXAxis(0.5);
}

static void pollButtons() {
    for (int i = 0; i < btnCount; i++) {
        int state = digitalRead(btnPin[i]);
        btnArr[i].update(state);
    }
}

void loop() {
    pollButtons();

    int32_t current_position = ss.getEncoderPosition();
    if (encoder_position != current_position) {
        Serial.print("Encoder position ");
        Serial.println(current_position);
        encoder_position = current_position;
        axis_position = map(encoder_position, -128, 127, 0, 1023);
        Serial.print("Axis position ");
        Serial.println(axis_position);
        Serial.println("---");
        Joystick.setXAxis(axis_position);
    }

    delay(1);
}