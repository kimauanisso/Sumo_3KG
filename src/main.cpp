#include "Arduino.h"

const int ledPin = 13, btnPin = 2;
bool ledState = false;

void changeLed() { ledState != ledState; }

void setup() {
    attachInterrupt(digitalPinToInterrupt(btnPin), changeLed, RISING);
    pinMode(ledPin, OUTPUT);
}

void loop() { digitalWrite(ledPin, ledState); }