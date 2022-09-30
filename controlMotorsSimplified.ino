#include <Servo.h>
#include <LiquidCrystal_I2C.h>
//global variables
int counter = 0;
int BUTTONSWITCHMOTOR = 5;//port
int BUTTONSwitchstate = 0;
LiquidCrystal_I2C lcd(0x27,20,4);

class Motor
{
  public://use outside of class(internal)
    void processMotor();
    void servoAttach(int digPinInput);// func with parameter to use any motor 
    void servoWrite(int angleDeg);
    int BUTTONCW = 2;//port
    int BUTTONCCW = 3;//port
  private://can only be seen by func in "Motor" class
    Servo myservo;//created object "myservo"
    int servoAngleValDEG;//var
    int BUTTONCWstate = 0;//var
    int BUTTONCCWstate = 0;
};

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

void Motor::processMotor() //processMotor function is part of class Motor
{
  
  BUTTONCWstate = digitalRead(BUTTONCW);
  BUTTONCCWstate = digitalRead(BUTTONCCW);
  if (BUTTONCWstate == HIGH && BUTTONCCWstate == LOW)
  {
    lcd.clear();
    servoAngleValDEG+=1;
    if (servoAngleValDEG>180)//prevents 180+ degrees
    {
      servoAngleValDEG = 180;
    }
    myservo.write(servoAngleValDEG);//writes angle to servo
  } 
  if (BUTTONCCWstate == HIGH && BUTTONCWstate == LOW)
  {
    lcd.clear();
    servoAngleValDEG-=1;
    if (servoAngleValDEG<0)//prevents negative degrees
    {
      servoAngleValDEG = 0;
    }
    myservo.write(servoAngleValDEG);//writes angle to servo
  } 
  Serial.print("angle: ");
  Serial.println(servoAngleValDEG);
  
  lcd.setCursor(0,1);
  lcd.print("angle: ");
  lcd.print(servoAngleValDEG);
  lcd.print(" degrees");
  //sda: data, scl: clock
}

Motor servoMotor[4]= {}; //init object with 1x4 array

void setup()
{
  Serial.begin(9600);//serial comms

  lcd.init(); 
  lcd.backlight(); 
  lcd.setCursor(0,0);
  //lcd.print("Hello, world!");
  
  servoMotor[0].servoAttach(9);//attach servo var to pin
  servoMotor[1].servoAttach(10);
  servoMotor[2].servoAttach(11);

  servoMotor[0].servoWrite(0);//9--> mid arm
  servoMotor[1].servoWrite(106);//10--> left arm
  servoMotor[2].servoWrite(0);//11--> rotate base
  servoMotor[3].servoWrite(0);//.. --> end effector
for (int i = 0;i<4;i++)//itterate through array
{
  //servoMotor[i].servoWrite(0);//starting all motors at angle 0 deg
  servoMotor[i].BUTTONCW = 2;//all motors use same CW and CCW buttons
  servoMotor[i].BUTTONCCW = 3;
  pinMode(servoMotor[i].BUTTONCW, INPUT);//init all button members as input for each motor
  pinMode(servoMotor[i].BUTTONCCW, INPUT);
}
  pinMode(BUTTONSWITCHMOTOR, INPUT);

}

void processAllMotors() 
{
  BUTTONSwitchstate = digitalRead(BUTTONSWITCHMOTOR);//Checks button3(BUTTONSWITCHMOTOR)
  
  if (BUTTONSwitchstate == HIGH)//If button3 HIGH, switch to next motor
  {
    counter+=1;
    delay(200);
  }
  
  switch (counter) {  //Switch to specific motor and go to func for CW and CCW
    case 1:
      Serial.println("1");
      servoMotor[0].processMotor();//Object[specific array].func
      lcd.setCursor(0,0);
      lcd.print("Motor 0");
      break;
    case 2:
      Serial.println("2");
      servoMotor[1].processMotor();
      lcd.setCursor(0,0);
      lcd.print("Motor 1");
      break;
    case 3:
      Serial.println("3");
      servoMotor[2].processMotor();
      lcd.setCursor(0,0);
      lcd.print("Motor 2");
      break;
    default:
      Serial.println("default");
      counter = 1;//reset
      break;
  }
}


void loop()
{
  processAllMotors(); //func decides which motor to use and then processes specific motor

  delay(15);
}