#include <Sprite.h>  // Sprite before Matrix
#include <Matrix.h>
#include <Wire.h>

volatile byte number[4];
unsigned int x, y;
volatile byte flag5;

//                  DIN, CLK, LOAD, #chips
Matrix myLeds = Matrix(7, 6, 5, 4);

Sprite C = Sprite(8, 8, B00000000, B01111111, B01000001, B01000001, B01000001, B00000000, B00100100, B00000000);
Sprite P = Sprite(8, 8, B00000000, B01111111, B00001001, B00001001, B00001111, B00000000, B00100100, B00000000);
Sprite nula = Sprite(8, 8, B01111111, B01000001, B01111111, B00000000, B01111111, B01000001, B01111111, B00000000);
Sprite jedan = Sprite(8, 8, B01111111, B01000001, B01111111, B00000000, B00000100, B00000010, B01111111, B00000000);
Sprite dva = Sprite(8, 8, B01111111, B01000001, B01111111, B00000000, B01111001, B01001001, B01001111, B00000000);
Sprite tri = Sprite(8, 8, B01111111, B01000001, B01111111, B00000000, B01001001, B01001001, B01111111, B00000000);
Sprite cetiri = Sprite(8, 8, B01111111, B01000001, B01111111, B00000000, B00001111, B00001000, B01111100, B00000000);
Sprite pet = Sprite(8, 8, B01111111, B01000001, B01111111, B00000000, B01001111, B01001001, B01111001, B00000000);
Sprite sest = Sprite(8, 8, B01111111, B01000001, B01111111, B00000000, B01111111, B01001001, B01111001, B00000000);
Sprite sedam = Sprite(8, 8, B01111111, B01000001, B01111111, B00000000, B00000001, B00000001, B01111111, B00000000);
Sprite osam = Sprite(8, 8, B01111111, B01000001, B01111111, B00000000, B01111111, B01001001, B01111111, B00000000);
Sprite devet = Sprite(8, 8, B01111111, B01000001, B01111111, B00000000, B01001111, B01001001, B01111111, B00000000);
Sprite deset = Sprite(8, 8, B00000100, B00000010, B01111111, B00000000, B01111111, B01000001, B01111111, B00000000);
Sprite jedanaest = Sprite(8, 8, B00000100, B00000010, B01111111, B00000000, B00000100, B00000010, B01111111, B00000000);
Sprite dvanaest = Sprite(8, 8, B00000100, B00000010, B01111111, B00000000, B01111001, B01001001, B01001111, B00000000);
Sprite trinaest = Sprite(8, 8, B00000100, B00000010, B01111111, B00000000, B01001001, B01001001, B01111111, B00000000);
Sprite cetrnaest = Sprite(8, 8, B00000100, B00000010, B01111111, B00000000, B00001111, B00001000, B01111100, B00000000);
Sprite petnaest = Sprite(8, 8, B00000100, B00000010, B01111111, B00000000, B01001111, B01001001, B01111001, B00000000);
Sprite sesnaest = Sprite(8, 8, B00000100, B00000010, B01111111, B00000000, B01111111, B01001001, B01111001, B00000000);
Sprite sedamnaest = Sprite(8, 8, B00000100, B00000010, B01111111, B00000000, B00000001, B00000001, B01111111, B00000000);
Sprite osamnaest = Sprite(8, 8, B00000100, B00000010, B01111111, B00000000, B01111111, B01001001, B01111111, B00000000);
Sprite devetnaest = Sprite(8, 8, B00000100, B00000010, B01111111, B00000000, B01001111, B01001001, B01111111, B00000000);
Sprite dvadeset = Sprite(8, 8, B01111001, B01001001, B01001111, B00000000, B01111111, B01000001, B01111111, B00000000);
Sprite dvadesetjedan = Sprite(8, 8, B01111001, B01001001, B01001111, B00000000, B00000100, B00000010, B01111111, B00000000);
Sprite dvadesetdva = Sprite(8, 8, B01111001, B01001001, B01001111, B00000000, B01111001, B01001001, B01001111, B00000000);
Sprite dvadesettri = Sprite(8, 8, B01111001, B01001001, B01001111, B00000000, B01001001, B01001001, B01111111, B00000000);
Sprite dvadesetcetiri = Sprite(8, 8, B01111001, B01001001, B01001111, B00000000, B00001111, B00001000, B01111100, B00000000);
Sprite dvadesetpet = Sprite(8, 8, B01111001, B01001001, B01001111, B00000000, B01001111, B01001001, B01111001, B00000000);


void setup() {
  Wire.begin(0);
  myLeds.clear();
  myLeds.setBrightness(5);
  myLeds.write(0, 0, C);
  myLeds.write(16, 0, P);
  Serial.begin(9600);
}
void loop() {
  Wire.requestFrom(1,5); // s adrese 1 prima 4 byte-a
  while (Wire.available()) {
    number[0] = Wire.read();
    number[1] = Wire.read();
    number[2] = Wire.read();
    number[3] = Wire.read();
    flag5 = Wire.read();
  }
  x = number[0] * 10 + number[1];
  y = number[2] * 10 + number[3];

  if (flag5 == 1){
    Serial.print("Crveni:");
    Serial.println(x);
    Serial.print("Plavi:");
    Serial.println(y); 
}
    delay (500);  

  //CRVENI------------------------------------
  if (x == 0) {myLeds.write(8, 0, nula);}
  if (x == 1) {myLeds.write(8, 0, jedan);}
  if (x == 2) {myLeds.write(8, 0, dva);}
  if (x == 3) {myLeds.write(8, 0, tri);}
  if (x == 4) {myLeds.write(8, 0, cetiri);}
  if (x == 5) {myLeds.write(8, 0, pet);}
  if (x == 6) {myLeds.write(8, 0, sest);}
  if (x == 7) {myLeds.write(8, 0, sedam);}
  if (x == 8) {myLeds.write(8, 0, osam);}
  if (x == 9) {myLeds.write(8, 0, devet);}
  if (x == 10) {myLeds.write(8, 0, deset);}
  if (x == 11) {myLeds.write(8, 0, jedanaest);}
  if (x == 12) {myLeds.write(8, 0, dvanaest);}
  if (x == 13) {myLeds.write(8, 0, trinaest);}
  if (x == 14) {myLeds.write(8, 0, cetrnaest);}
  if (x == 15) {myLeds.write(8, 0, petnaest);}
  if (x == 16) {myLeds.write(8, 0, sesnaest);}
  if (x == 17) {myLeds.write(8, 0, sedamnaest);}
  if (x == 18) {myLeds.write(8, 0, osamnaest);}
  if (x == 19) {myLeds.write(8, 0, devetnaest);}
  if (x == 20) {myLeds.write(8, 0, dvadeset);}
  if (x == 21) {myLeds.write(8, 0, dvadesetjedan);}
  if (x == 22) {myLeds.write(8, 0, dvadesetdva);}
  if (x == 23) {myLeds.write(8, 0, dvadesettri);}
  if (x == 24) {myLeds.write(8, 0, dvadesetcetiri);}
  if (x == 25) {myLeds.write(8, 0, dvadesetpet);}
  //PLAVI-----------------------------------------
  if (y == 0) {myLeds.write(24, 0, nula);}
  if (y == 1) {myLeds.write(24, 0, jedan);}
  if (y == 2) {myLeds.write(24, 0, dva);}
  if (y == 3) {myLeds.write(24, 0, tri);}
  if (y == 4) {myLeds.write(24, 0, cetiri);}
  if (y == 5) {myLeds.write(24, 0, pet);}
  if (y == 6) {myLeds.write(24, 0, sest);}
  if (y == 7) {myLeds.write(24, 0, sedam);}
  if (y == 8) {myLeds.write(24, 0, osam);}
  if (y == 9) {myLeds.write(24, 0, devet);}
  if (y == 10) {myLeds.write(24, 0, deset);}
  if (y == 11) {myLeds.write(24, 0, jedanaest);}
  if (y == 12) {myLeds.write(24, 0, dvanaest);}
  if (y == 13) {myLeds.write(24, 0, trinaest);}
  if (y == 14) {myLeds.write(24, 0, cetrnaest);}
  if (y == 15) {myLeds.write(24, 0, petnaest);}
  if (y == 16) {myLeds.write(24, 0, sesnaest);}
  if (y == 17) {myLeds.write(24, 0, sedamnaest);}
  if (y == 18) {myLeds.write(24, 0, osamnaest);}
  if (y == 19) {myLeds.write(24, 0, devetnaest);}
  if (y == 20) {myLeds.write(24, 0, dvadeset);}
  if (y == 21) {myLeds.write(24, 0, dvadesetjedan);}
  if (y == 22) {myLeds.write(24, 0, dvadesetdva);}
  if (y == 23) {myLeds.write(24, 0, dvadesettri);}
  if (y == 24) {myLeds.write(24, 0, dvadesetcetiri);}
  if (y == 25) {myLeds.write(24, 0, dvadesetpet);}

  delay(100); 

}
//void ispis(){
//  
//  }

