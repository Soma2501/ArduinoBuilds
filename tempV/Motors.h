#pragma once
#include <Arduino.h>
#include <Servo.h>

//declaration of Class/initializations
class Motor
{
  public://use outside of class(internal)
    void processMotor();
    void servoAttach(int digPinInput);// func with parameter to use any motor 
    void servoWrite(int angleDeg);
    void setAngleLimits(int min, int max);
    int getCurrAngleDeg();
    int BUTTONCW;//port
    int BUTTONCCW;//port
    
  private://can only be seen by func in "Motor" class
    Servo myservo;//created object "myservo"
    int servoAngleValDEG;//var
    int BUTTONCWstate = 0;//var
    int BUTTONCCWstate = 0;
    int minAngleDeg;
    int maxAngleDeg;
};

