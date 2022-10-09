#include "Motors.h"

//funcs

void Motor::servoAttach(int digPinInput)//Class::Function(param)
{
  myservo.attach(digPinInput);  // attaches the servo on pin 9 or 10 to the servo object
}

void Motor::servoWrite(int angleDeg)
{
myservo.write(angleDeg);
//servoMotor[0].servoWrite(42); EXAMPLE
servoAngleValDEG = angleDeg;//sets current angle as private member angle for motor object
}

void Motor::setAngleLimits(int min, int max)
{
minAngleDeg = min;
maxAngleDeg = max;
}

void Motor::processMotor() //processMotor function is part of class Motor
{
  BUTTONCWstate = digitalRead(BUTTONCW);
  BUTTONCCWstate = digitalRead(BUTTONCCW);
  if (BUTTONCWstate == HIGH && BUTTONCCWstate == LOW)
  {
    servoAngleValDEG+=1;
    if (servoAngleValDEG>maxAngleDeg)//prevents 180+ degrees
    {
      servoAngleValDEG = maxAngleDeg;
    }
    myservo.write(servoAngleValDEG);//writes angle to servo
  } 
  if (BUTTONCCWstate == HIGH && BUTTONCWstate == LOW)
  {
    servoAngleValDEG-=1;
    if (servoAngleValDEG<minAngleDeg)//prevents negative degrees
    {
      servoAngleValDEG = minAngleDeg;
    }
    myservo.write(servoAngleValDEG);//writes angle to servo
  } 
  //Serial.print("angle: ");
  //Serial.println(servoAngleValDEG);
  

}
int Motor::getCurrAngleDeg()
{
return servoAngleValDEG;
}