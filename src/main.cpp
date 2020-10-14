#include <Arduino.h>
#include <Joystick.h>
#include "WiFi.h"
#include "AsyncUDP.h"

const char * ssid = "TELLO-59FC3F";
const char * password = "";

AsyncUDP udp;
// Instantiate objects
Joystick joystick1 = Joystick(39, 36, 5); 
Joystick joystick2 = Joystick(32, 35, 17);
Button buttonBlue = Button(21);

// setup function for connecting to the drone
void setup() {
  Serial.begin(9600);
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    if (WiFi.waitForConnectResult() != WL_CONNECTED) {
        Serial.println("WiFi Failed");
        while(1) {
            delay(1000);
        }
    }
}

// button for setting drone in command mode
void command (Button &button){
  if (button.isPressed() == 1){
  udp.writeTo((const uint8_t*)"command", 7, IPAddress(192,168,10,1), 8889);
  }
}

// joystick button to send "takeoff" command packet
void takeOff (Joystick &joystick){
  if (joystick.isButtonPressed()){
  udp.writeTo((const uint8_t*)"takeoff", 7, IPAddress(192,168,10,1), 8889);
  }
}

// joystick button to send "land" command packet
void land (Joystick &joystick){
  if (joystick.isButtonPressed()){
    udp.writeTo((const uint8_t*)"land", 4, IPAddress(192,168,10,1), 8889);
  }
}

// joystick movement commands 
void movement1(Joystick &joystick){
   if (joystick.isInDeadzone() == false && joystick.getJoystickValues().first == 0){
     udp.writeTo((const uint8_t*)"down 30", 7, IPAddress(192,168,10,1), 8889);

   }
   if (joystick.isInDeadzone() == false && joystick.getJoystickValues().first == 4095){
     udp.writeTo((const uint8_t*)"up 30", 5, IPAddress(192,168,10,1), 8889);

   }
    if (joystick.isInDeadzone() == false && joystick.getJoystickValues().second == 0){
     udp.writeTo((const uint8_t*)"left 40", 7 , IPAddress(192,168,10,1), 8889);

   }
   if (joystick.isInDeadzone() == false && joystick.getJoystickValues().second == 4095){
     udp.writeTo((const uint8_t*)"right 40", 8, IPAddress(192,168,10,1), 8889);
   }
}
void movement2(Joystick &joystick){
   if (joystick.isInDeadzone() == false && joystick.getJoystickValues().first == 0){
     udp.writeTo((const uint8_t*)"back 100", 8, IPAddress(192,168,10,1), 8889);

   }
   if (joystick.isInDeadzone() == false && joystick.getJoystickValues().first == 4095){
     udp.writeTo((const uint8_t*)"forward 100", 11, IPAddress(192,168,10,1), 8889);

   }
    if (joystick.isInDeadzone() == false && joystick.getJoystickValues().second == 0){
     udp.writeTo((const uint8_t*)"flip l", 6 , IPAddress(192,168,10,1), 8889);

   }
   if (joystick.isInDeadzone() == false && joystick.getJoystickValues().second == 4095){
     udp.writeTo((const uint8_t*)"flip r", 8, IPAddress(192,168,10,1), 8889);
   }
}

// prints x and y for a joystick object if moved out of deadzone
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
  movement1(joystick1);
  movement2(joystick2);
  printJoystickValues(joystick1);
  printJoystickValues(joystick2);
}