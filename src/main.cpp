#include <Arduino.h>
#include <Joystick.h>
#include <Piezo.h>
#include "WiFi.h"
#include "AsyncUDP.h"

const char * ssid = "iPhone";
const char * password = "grimhund";

AsyncUDP udp;
// Instantiate objects
Joystick joystick1 = Joystick(39, 34, 33); 
Joystick joystick2 = Joystick(32, 35, 13);
Button buttonBlue = Button(21);
Button buttonRed = Button(5);
Piezo piezo = Piezo(36);
IPAddress IP = IPAddress(172,20,10,7);
int toPort = 6000;


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
// Method for sending udp packages
void sendToDrone(char actionInfo[]){
  //calculates lenght of value in char array
  int letterAmount = strlen(actionInfo);
  //casts value in char array to uint8_t
  const uint8_t* action = (const uint8_t*) actionInfo;
  // built in function that takes (uint8_t* data, lenght of the data, an IP address and a port)
  udp.writeTo(action, letterAmount, IP, toPort);
  delay(300);
}

void command (Button &button){
  if (button.isPressed() == 1){
  char commandCommand[] = "command";
  sendToDrone(commandCommand); 
   }
}

void takeOff (Button &button){
  if (button.isPressed() == 1){
  char takeOffCommand[] = "takeoff";
  sendToDrone(takeOffCommand);
  }
}

void land (Piezo &piezo){
  if (piezo.isNoiseDetected()){
  char landCommand[] = "land";
  sendToDrone(landCommand);
  delay(5000);
  }

}

// joystick movement commands 
void actionsJoystick1(Joystick &joystick){
  if (joystick.isButtonPressed()){
     char flipLCommand[] = "flip l";
     sendToDrone(flipLCommand);
  }
  while (!joystick.isInDeadzone()){
    if (joystick.getJoystickValues().first == 0){
        char downCommand[] = "down 40";
        sendToDrone(downCommand); 
    } else if (joystick.getJoystickValues().first == 4095){
        char upCommand[] = "up 40";
        sendToDrone(upCommand);
    } else if (joystick.getJoystickValues().second == 0){
        char leftCommand[] = "left 40";
        sendToDrone(leftCommand);
    } else if (joystick.getJoystickValues().second == 4095){
        char rightCommand[] = "right 40"; 
        sendToDrone(rightCommand);
    }  
  } 
}
void actionsJoystick2(Joystick &joystick){
  if (joystick.isButtonPressed()){
     char flipRCommand[] = "flip r";
     sendToDrone(flipRCommand);
  }
  while (!joystick.isInDeadzone()){
    if (joystick.getJoystickValues().first == 0){
        char backCommand[] = "back 40";
        sendToDrone(backCommand); 
    } else if (joystick.getJoystickValues().first == 4095){
        char forwardCommand[] = "forward 40";
        sendToDrone(forwardCommand);
    } else if (joystick.getJoystickValues().second == 0){
        char rotateLCommand[] = "ccw 45";
        sendToDrone(rotateLCommand);
    } else if (joystick.getJoystickValues().second == 4095){
        char rotateRCommand[] = "cw 45"; 
        sendToDrone(rotateRCommand);
    } 
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
  takeOff(buttonRed);
  land(piezo);
  actionsJoystick1(joystick1);
  actionsJoystick2(joystick2);
  //printJoystickValues(joystick1);
  //printJoystickValues(joystick2); 
}