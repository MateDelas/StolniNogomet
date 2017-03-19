#include <Wire.h>
#include <TimerOne.h>

//Reset rezultata--------------------
float milliSeconds = 0;
int counter_time = 1;
int restart_time = 3000;  
int counter = 0;
//----------------------------------
volatile bool bCrveniInt, bPlaviInt;
int t;
volatile int iDigit=0;
volatile byte number[]={0,1,1,0}; // int=2Byte,signed; byte=1Byte, unsigned; char=1Byte, signed
bool  flag1 = 0, flag2 = 0, flag3 = 0, flag4 = 0;
volatile byte flag5;

volatile byte segments[]={
  0b00111111, // 0
  0b00000110, // 1
  0b01011011, // 2
  0b01001111, // 3
  0b01100110, // 4
  0b01101101, // 5
  0b01111101, // 6
  0b00000111, // 7
  0b01111111, // 8
  0b01101111, // 9
  0b00000000, // ugasi sve
};
// FUNKCIJE
void ispis() {
  digitalWrite(iDigit+4, HIGH); // gasi sve digite
  iDigit++;
  if(iDigit>3){ iDigit=0; }
  for(int i=0; i<8; i++) {
                                                      //00000110 segmenti za znak '1'
    bool state = (~segments[number[iDigit]]) & (1<<i);//00000001 (i=0)
                                                      //00000010 (i=1)
                                                      //   ...
                                                      //10000000 (i=7)
    digitalWrite(i+8, state); // LOW=false=0
  }
  digitalWrite(iDigit+4, LOW);
}

void Crveni() {
  bCrveniInt=true;
  noInterrupts();
}
void Plavi() {
  bPlaviInt=true;
  noInterrupts();
}
void saljiRezultat() {
  Wire.write(number[0]);
  Wire.write(number[1]);
  Wire.write(number[2]);
  Wire.write(number[3]);
  Wire.write(flag5);
}
// KRAJ FUNKCIJA
void setup() {
  // 7 segment display
  for(int i=4; i<=7; i++) {
    pinMode(i,OUTPUT); // 4...7 digits
    digitalWrite(i, HIGH); // upali sve digite
  }
  for(int i=8; i<=15; i++) {
    pinMode(i,OUTPUT); // 8...15 segments
  }
  Timer1.initialize(1000);       // svakih 1000us ...
  Timer1.attachInterrupt(ispis); // ... pozovi digit()

  // tipkala
  pinMode( 0, INPUT_PULLUP); // c+
  pinMode( 1, INPUT_PULLUP); // c-
  pinMode(16, INPUT_PULLUP); // p+
  pinMode(17, INPUT_PULLUP); // p-

  attachInterrupt(digitalPinToInterrupt(2),Crveni,RISING);
  attachInterrupt(digitalPinToInterrupt(3),Plavi,RISING);
  
  Wire.begin(1);
  Wire.onRequest(saljiRezultat);

  Serial.begin(9600);
}
int x = 0, y = 0;
void loop() {  
  if(bCrveniInt) {
    bCrveniInt = false;
    x++;
    interrupts(); // enable interrupts
  }
  if(bPlaviInt) {
    bPlaviInt = false;
    y++;
    interrupts(); // enable interrupts
  }
  //K1 TIPKA----------------------------------
  if(digitalRead( 0)== HIGH && flag1 == 0) 
  { 
    delay(100);
    x++; 
    flag1 = 1;
  }
  if(digitalRead( 0)== LOW && flag1 == 1)
  {
    delay(100);
    flag1 = 0;
  }
  //K2 TIPKA-----------------------------------
  if(digitalRead( 1)== HIGH && flag2 == 0) 
  {
    delay(100);
    x--; 
    flag2 = 1;
  }
  if(digitalRead( 1)== LOW && flag2 == 1)
  {
    flag2 = 0;
  }
  //K3 TIPKA------------------------------------
  if(analogRead(A2)> 1000 && flag3 == 0)
  { 
    delay(100);
    y++; 
    flag3 = 1;
  }
  if(analogRead(A2)< 100 && flag3 == 1) 
  { 
    flag3 = 0;
  }
  //K4 TIPKA-------------------------------------
  if(analogRead(A3)> 1000 && flag4 == 0)
  { 
    delay(100);
    y--; 
    flag4 = 1;
  }
  if(analogRead(A3)< 100 && flag4 == 1) 
  { 
    flag4 = 0;
  }
  
  if(x>99) { x=99; }
  if(x< 0) { x= 0; }
  if(y>99) { y=99; }
  if(y< 0) { y= 0; }
  number[0] = x/10;
  number[1] = x%10;
  number[2] = y/10;
  number[3] = y%10;
 
  delay(250);
//Reset rezultata--------------------------------------
  while (digitalRead(1) == LOW ){ 
    delay(100);  
    milliSeconds = milliSeconds + 100;   
    }

  if (milliSeconds >= restart_time){
    x=0;
    y=0;   
    flag5=0;
  } 

  else if(milliSeconds >= counter_time){
    x--;
  }
  milliSeconds = 0;

//milliSeconds = 0;
//slanje rezultata--------------------------------------
while (digitalRead(0) == LOW ){ 
    delay(100);  
    milliSeconds = milliSeconds + 100;   
    }

  if (milliSeconds >= restart_time){ 
    flag5 = 1;
  } 

  else if(milliSeconds >= counter_time){
    x++;
  }
  milliSeconds = 0;

}

