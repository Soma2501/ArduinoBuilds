#include "Motors.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);
//global variables

int BUTTONSWITCHMOTOR = 5;//port
String Str = "Hello World, Goodbye";
int pos = 0, len =0;
int cursor = 20;

Motor servoMotor[4]= {}; //init object with 1x4 array

void setup()
{
  Serial.begin(9600);//serial comms

  lcd.init(); 
  lcd.backlight(); 
  
  
  servoMotor[0].servoAttach(9);//attach servo var to pin
  servoMotor[1].servoAttach(10);
  servoMotor[2].servoAttach(11);

  servoMotor[0].servoWrite(0);//9--> mid arm
  servoMotor[1].servoWrite(106);//10--> left arm
  servoMotor[2].servoWrite(0);//11--> rotate base
  servoMotor[3].servoWrite(0);//.. --> end effector

  servoMotor[0].setAngleLimits(0,60); //ROM(min, max)
  servoMotor[1].setAngleLimits(0,106);
  servoMotor[2].setAngleLimits(0,180);
  servoMotor[3].setAngleLimits(0,180);

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
  static int BUTTONSwitchstate = 0;
  static int cidx = 0;//only initialized once throughout runtime
  static int prevCidx = -1;
  static int currMotorAng[4];
  static int prevMotorAng[4];
  BUTTONSwitchstate = digitalRead(BUTTONSWITCHMOTOR);//Checks button3(BUTTONSWITCHMOTOR)
 
  if (BUTTONSwitchstate == HIGH)//If button3 HIGH, switch to next motor
  {
    while (BUTTONSwitchstate)
    {
      if ((millis() % 400)==0)
      {
        cidx+=1;
        BUTTONSwitchstate = LOW;
      }
    }
  }
  if (cidx >3)
  {
    cidx = 0;
  }
  
 // Serial.print("Motor: " + String(cidx) + " ");
  servoMotor[cidx].processMotor();//Object[specific array].func
  currMotorAng[cidx]=servoMotor[cidx].getCurrAngleDeg();

  if ((cidx != prevCidx) || (prevMotorAng[cidx] != currMotorAng[cidx]))
  {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Motor " + String(cidx));
    lcd.setCursor(0,1);
    lcd.print("angle: " + String(currMotorAng[cidx]) + char(223));
  }
  prevCidx = cidx;
  prevMotorAng[cidx]=currMotorAng[cidx];
}

void loop()
{
  static int time = 0;
  if ((millis() % 15)==0)
  {
    processAllMotors(); //func decides which motor to use and then processes specific motor
  }
  if ((millis() % 90)==0)
  {
    message();
  }
  if ((millis() % 400)==0)  //need delay before clearing and reprinting
  {
    msgCond();
  }
}

void message()
{
  //static char asc = 97;

  lcd.setCursor(cursor, 3);//inputCharAt(column,row)
  lcd.print(Str.substring(pos,len));
}
void msgCond()
{  
  lcd.setCursor(0, 3);//inputCharAt(column,row)
  lcd.print("                    ");
  if (pos==0 && cursor >0)//(1)start begining of string (pos=0) and print until cursor ends up on left
  {
    cursor--;//reduce cursor from 19 to 0
    len++;//increase len from 0 to 19 to include full sentence and space after    
  }
  else if (pos ==Str.length())//start over
  {
  cursor = 20;
  pos = 0;
  len = 0;
  }
  else if (pos<=Str.length() && cursor==0)//at left and len ==11)
  {
    pos++;//as len same, will print from pos onward until 
  }
  else//once at left, prints out of screen
  {
    pos++;//space after line
    len++;//inc. string to see space
  }
}
/*
  static int i=0;
  if (i<=19)
  {
    lcd.setCursor(i,2);
    lcd.print(asc);
    lcd.setCursor(i-1,2);
    lcd.print(" ");
    Serial.println(i);
  }
  i++;
  */  
/*
    if (i<=20)
    {
      lcd.setCursor(i,2);
      lcd.print(asc);
      lcd.setCursor(i-1,2);
      lcd.print(" ");
      Serial.println(i);
      
      if (i>= 21-inputLength) 
      {
        lcd.setCursor(i-20,3);
        lcd.print(Str);
        lcd.setCursor(i-20,3);
        lcd.print(" ");
      }
      else
      {
        lcd.setCursor(i,3);
        lcd.print(Str);
        lcd.setCursor(i-1,3);
        lcd.print(" ");
      }
      i++;
    }
    */


//in lcd: print ascii char at bottom row and have slide into and out of that row

//implement touch screen
//implement wifi iot w/ ESP
//be able to move mult motors at once (when i have better controller or touch screen) --> threads, 

//implement emg control
//switch to arduino mega
//Have simulation runing through code at same time
//Have arduinos work together?
//Raspberry Pi implement for computer vision eventually

//Notes:
//sda: data, scl: clock