/* UV LED Exposure Box - Arduino Code
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
