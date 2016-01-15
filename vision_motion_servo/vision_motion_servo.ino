// Sweep
// by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 

Servo myservo;

int pos = 0;
int dtheta_sign = 1;

void setup() 
{ 
  Serial.begin(9600);
  pinMode(10, OUTPUT);
  digitalWrite(10, HIGH);
  myservo.attach(9);
  myservo.write(0);
} 


void loop() 
{ 
  int a = analogRead(A0);

  int dtheta = dtheta_sign * a * 180.0 / 1023.0;
  Serial.println(dtheta);
  pos += dtheta;

  if (pos > 180)
  {
    pos = 180;
    dtheta_sign = -1 * dtheta_sign;
  }
  else if (pos < 0)
  {
    pos = 0;
    dtheta_sign = -1 * dtheta_sign;
  }
  
  myservo.write(pos);
  delay(30);
} 

