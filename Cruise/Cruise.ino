#include <Servo.h>
Servo servo;
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 8, 7, 5, 4);
volatile int rev = 0;
volatile int rpm = 0;
int motorPin = 11;
int motorspeed = 0;
int sensorValue = 0;
int time1 = 0;
int time2 = 0;
int period = 0;
int cruisepin = 0;
volatile int compare = 1400;
int servopos = 0;
int servopin=9;
void isr()
{
  rev++;
}

void cruz()
{
  detachInterrupt(0);
  compare=rpm; 
  if(cruisepin==0)
  cruisepin=1;
  else if(cruisepin==1)
  cruisepin=0;
  attachInterrupt(0,cruz,FALLING);
  
  }
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("CC:");
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(2,  INPUT);
  servo.write(50);
  servo.attach(servopin);
  delay(500);
  servo.detach();
  attachInterrupt(1, isr, FALLING);
  attachInterrupt(0,cruz,FALLING);
}

void loop() {delay(2000);
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.print("CC:");
  lcd.setCursor(4,0);
  if(cruisepin==1)
    lcd.print("EN");
  
  else if(cruisepin==0)
    lcd.print("DE");

    lcd.setCursor(7,0);
    lcd.print("SS:");
    
    lcd.setCursor(10,0);
    lcd.print(compare);
    
 lcd.setCursor(0,1);
  lcd.print("Speed"); 
  lcd.setCursor(6,1);
  lcd.print(rpm);
  
  sensorValue = analogRead(A0);
  servopos = map(sensorValue, 104, 312, 0, 90);
  
  motorspeed = map(sensorValue, 60, 300, 0, 100);
  analogWrite(motorPin, motorspeed);
  Serial.println(compare);
  
  time1 = millis();
  
  while (rev < 600)
  {}
  detachInterrupt(1);

  period = time1 - time2;

  

  rpm = (6000000) / period;
   time2 = time1;
  delay(100);
  rev = 0;

  if(cruisepin==1)
  {
    
    if(rpm>compare+100)
  { servopos=servopos-10;  
    servo.write(servopos);
  servo.attach(servopin);
  delay(500);
  servo.detach();
  
    
  }
  else if (rpm<compare-100)
   {servopos=servopos+7;  
    servo.write(servopos);
  servo.attach(servopin);
  delay(500);
  servo.detach();
   
    
  }
    
    
    
    
    }
  attachInterrupt(1, isr, FALLING);
}
