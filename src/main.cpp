#include <Arduino.h>
#include <Joystick.h>
#include "WiFi.h"
#include "AsyncUDP.h"

const char * ssid = "TELLO-59FC3F";
const char * password = "";

AsyncUDP udp;

Joystick joystick1 = Joystick(32, 35, 5); // Instantiate object
Joystick joystick2 = Joystick(23, 22, 17); // Instantiate object
Button buttonBlue = Button(21);

void setup() {
  Serial.begin(9600);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        while(1) {
            delay(1000);
        }
    udp.writeTo((const uint8_t*)"command", 7, IPAddress(192,168,10,1), 8889);
  }
}
void command (Button &button){
  if (button.isPressed() == 1){
    Serial.println("yo");
  udp.writeTo((const uint8_t*)"command", 7, IPAddress(192,168,10,1), 8889);
  }
}
void takeOff (Joystick &joystick){
  if (joystick.isButtonPressed()){
    Serial.println("yo");
  udp.writeTo((const uint8_t*)"takeoff", 7, IPAddress(192,168,10,1), 8889);
  }
}
void land (Joystick &joystick){
  if (joystick.isButtonPressed()){
    Serial.println("yo");
    udp.writeTo((const uint8_t*)"land", 4, IPAddress(192,168,10,1), 8889);
  }
}
void movement(Joystick &joystick){
   if (joystick.isInDeadzone() == false && joystick.getJoystickValues().first == 0){
     udp.writeTo((const uint8_t*)"down 20", 7, IPAddress(192,168,10,1), 8889);

   }
   if (joystick.isInDeadzone() == false && joystick.getJoystickValues().first == 4095){
     udp.writeTo((const uint8_t*)"up 20", 5, IPAddress(192,168,10,1), 8889);

   }
    if (joystick.isInDeadzone() == false && joystick.getJoystickValues().second == 0){
     udp.writeTo((const uint8_t*)"left 20", 7 , IPAddress(192,168,10,1), 8889);

   }
   if (joystick.isInDeadzone() == false && joystick.getJoystickValues().second == 4095){
     udp.writeTo((const uint8_t*)"right 20", 8, IPAddress(192,168,10,1), 8889);
   }
}

void printJoystickValues(Joystick &joystick) {
  if (joystick.isInDeadzone() == false) {
    Serial.print("X ");
    Serial.print(joystick.getJoystickValues().first);
    Serial.print(" , y ");
    Serial.println(joystick.getJoystickValues().second);
  }
}

void loop() {
  command(buttonBlue);
  takeOff(joystick1);
  land(joystick2);
  movement(joystick1);
  printJoystickValues(joystick1);
}