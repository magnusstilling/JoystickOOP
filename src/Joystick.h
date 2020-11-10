#ifndef Joystick_h
#define Joystick_h

#include "Arduino.h"
#include "Button.h"

class Joystick {
public:
  Joystick(int xPin, int yPin, int buttonPin) {
    // Assign values for potentiometers and buttons
    this->xPin = xPin;
    this->yPin = yPin;
    detectCenterPosition();

    button = new Button(buttonPin);
  };

// function for setting object name
  void setName(String s) { this->name = s; }

// make potionmeters values into a pair
  std::pair<int, int> getJoystickValues() {
    int xVal = analogRead(this->xPin);
    int yVal = analogRead(this->yPin);
    return std::make_pair(xVal, yVal);
  }

// checking, deadzone
  bool isInDeadzone() {
    int offset = 1000;
    auto joystick = getJoystickValues();

    return std::abs(joystick.first - joyXCenterVal) < offset &&
           std::abs(joystick.second - joyYCenterVal) < offset;
  }

// see if button on joystick is pressed
  bool isButtonPressed() { 
    return button->isPressed(); 
    };

//  calculating and setting deadzone
private:
  void detectCenterPosition() {
    auto joystick = getJoystickValues();
    joyXCenterVal = joystick.first;
    joyYCenterVal = joystick.second;
  };


  Button *button;
  int xPin = 0;
  int yPin = 0;
  int buttonPin = 0;
  int joyXCenterVal = 0;
  int joyYCenterVal = 0;
  String name = "";
};

#endif