#ifndef Piezo_h
#define Piezo_h

#include "Arduino.h"

class Piezo{
public:
    Piezo(int piezoPin){
        this->piezoPin = piezoPin;
        this->noiseFloorValue = noiseFloorDetection(piezoPin);
    }
    
    bool isNoiseDetected(){
        int offset = 150;
        int noiseLevel = analogRead(piezoPin);
        Serial.println(noiseLevel);
        bool isNoise = false;
        if (noiseLevel > noiseFloorValue+offset) {
           isNoise = true; 
           return isNoise;  
        } else 
        return isNoise;      
    }

private:   
    int noiseFloorDetection(int piezoPin){
    int value = 0;
    int avgNoise[20];
    int reps = 20;
    for (int i = 0; i < reps; i++){
        avgNoise[i] = analogRead(piezoPin);
        value += avgNoise[i];
    }
    value = value/reps;
    return (int) value;
    }
    int piezoPin = 0;
    int noiseFloorValue;
};

#endif