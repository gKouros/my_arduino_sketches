/******************************************************************************
Copyright (c) 2016, George Kouros
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of my_arduino_sketches nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/*
 * UV LED Exposure Box - Arduino Code
 * LCD + TIMER + UV LED matrix Control +
 * + Piezo Buzzer + INC,DEC,RESET time button
 */
// libraries
#include <LiquidCrystal.h>

//PIN definitions
#define buzzerPin 9 //PWM PIN D9
#define incButton 2
#define decButton 3
#define basePin 8

// Global Variables Declaration
int seconds = 0;
//                RS,rw, E,  D4, D5, D6, D7
LiquidCrystal lcd(10, 7, 11, 12, 13, A0, A1);

void setup()
{
  noInterrupts();
  // setup IO pins
  pinMode(buzzerPin, OUTPUT);
  pinMode(basePin, OUTPUT);
  digitalWrite(basePin, LOW); // initialize base pin of transistor to 0V
  pinMode(incButton, INPUT);
  pinMode(decButton, INPUT);

  // initialize variables
  seconds = 0;

  //Setup LCD
  lcd.begin(16,2);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("UV Exposure Box");
  lcd.setCursor(0,1);
  lcd.print("Time: 00:00");

  // setup interrupts
  attachInterrupt(0, incTime, FALLING);
  attachInterrupt(1, decTime, FALLING);
  interrupts();
}

void loop()
{
  if (seconds != 0){
    if (digitalRead(basePin) != HIGH)
      digitalWrite(basePin, HIGH);
    stopwatch();
  }
}

void stopwatch()
{
  lcdPrint(seconds/60, seconds%60);
  while (seconds>0){
    delay(1000);
    seconds = seconds - 1;
    lcdPrint(seconds/60, seconds%60);
  }
  lcdPrint(0,0);
  seconds = 0;
  digitalWrite(basePin, LOW);
  beep(3);
}

void lcdPrint(int mins, int secs)
{
   lcd.setCursor(6,1);
   int mins1 = abs(mins/10);
   int mins0 = abs(mins%10);
   int secs1 = abs(secs/10);
   int secs0 = abs(secs%10);
   lcd.print(String(mins1)+String(mins0)+":"+String(secs1)+String(secs0));
}

void beep(int beeps)
{
  for (int i=0; i<beeps; i++){
    analogWrite(buzzerPin,100);
    delay(300);
    analogWrite(buzzerPin,0);
    delay(200);
  }
}

void incTime(){
  //debounce interrupt
  while(digitalRead(incButton)==LOW);
  delay(20);
  while(true){
    if(digitalRead(incButton) == HIGH){ //sw released
      delay(20);
      break;
    }
  }
  seconds += 30;
  seconds = seconds % 5940; // in case of 2-digit-minutes overflow
  // time_left = seconds/60 [min] : seconds%60 [sec]
}

void decTime(){
   //debounce interrupt
  while(digitalRead(decButton)==LOW);
  delay(20);
  while(true)
  {
    if(digitalRead(decButton) == HIGH) //sw released
    {
      delay(20);
      break;
    }
  }
  if (seconds>30)
    seconds -= 30;
  else
    seconds = 0;
}
