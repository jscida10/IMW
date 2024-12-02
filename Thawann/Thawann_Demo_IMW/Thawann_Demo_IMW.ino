// OLED_I2C_Graph_Demo
// Copyright (C)2018 Rinky-Dink Electronics, Henning Karlsen. All right reserved
// web: http://www.RinkyDinkElectronics.com/
//
// **********************************************
// *** This demo is for 128x64 pixel displays ***
// **********************************************
//
// A quick demo of how to use my OLED_I2C library.
//
// To use the hardware I2C (TWI) interface of the Arduino you must connect
// the pins as follows:
//
// Arduino Uno/2009:
// ----------------------
// Display:  SDA pin   -> Arduino Analog 4 or the dedicated SDA pin
//           SCL pin   -> Arduino Analog 5 or the dedicated SCL pin
//
// Arduino Leonardo:
// ----------------------
// Display:  SDA pin   -> Arduino Digital 2 or the dedicated SDA pin
//           SCL pin   -> Arduino Digital 3 or the dedicated SCL pin
//
// Arduino Mega:
// ----------------------
// Display:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA pin
//           SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL pin
//
// Arduino Due:
// ----------------------
// Display:  SDA pin   -> Arduino Digital 20 (SDA) or the dedicated SDA1 (Digital 70) pin
//           SCL pin   -> Arduino Digital 21 (SCL) or the dedicated SCL1 (Digital 71) pin
//
// The internal pull-up resistors will be activated when using the 
// hardware I2C interfaces.
//
// You can connect the OLED display to any available pin but if you use 
// any other than what is described above the library will fall back to
// a software-based, TWI-like protocol which will require exclusive access 
// to the pins used, and you will also have to use appropriate, external
// pull-up resistors on the data and clock signals.
//

#include <OLED_I2C.h>

#define MedI A7
#define Bat A6
#define Corr A0
#define Vin A1
#define Vout A2
#define Alim5 A3
#define Enc 3
#define Alim12 4
#define Penc 13 

OLED  myOLED(SDA, SCL); // Remember to add the RESET pin if your display requires it...

extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
extern uint8_t BigNumbers[];
extern uint8_t logo[];

float var=0;
long tiempo=0;

void setup()
{
  if(!myOLED.begin(SSD1306_128X64))
    while(1);   // In case the library failed to allocate enough RAM for the display buffer...

  myOLED.setFont(SmallFont);
//  randomSeed(analogRead(7));
  analogReference(INTERNAL);
  
  // LOGO ////////////
  myOLED.clrScr();
  myOLED.drawBitmap(15, 14, logo, 97, 36);
  myOLED.update();

  delay(250);
  for (int i=0; i<5; i++)
  {
    myOLED.invert(true);
    delay(100);
    myOLED.invert(false);
    delay(250);
  }
 // Fin LOGO //////////
  pinMode(Enc, OUTPUT);
  pinMode(Alim5, OUTPUT);
  pinMode(Alim12, OUTPUT);
  pinMode(MedI, OUTPUT);

  digitalWrite(Enc,LOW);
  digitalWrite(Alim5,LOW);
  digitalWrite(Alim12,LOW);
  digitalWrite(MedI, LOW);

  tiempo=millis();
  
}

void loop()
{
//while(1);
  
  myOLED.clrScr();
  myOLED.setFont(SmallFont);
  myOLED.print("Vin:", LEFT, 8);
  myOLED.print("Vout", LEFT, 30);
  myOLED.print("I[mA]", CENTER, 30);
  myOLED.print("Bat", RIGHT, 30);
  
  myOLED.setFont(BigNumbers);//MediumNumbers);
//entrada
  digitalWrite(MedI, HIGH);
  digitalWrite(Alim5,LOW);
  delay(50);
  var=(float)analogRead(Vin)/51.8072289;//10.6;
  myOLED.printNumF(var,2, CENTER, 0);

  myOLED.setFont(SmallFont);//myOLED.setFont(MediumNumbers);
//salida
  var=5;//(float)analogRead(Vout)*6.253164556962/51.8072289;//10.6;
  myOLED.printNumF(var,2, LEFT,40);
//corriente
  digitalWrite(MedI, LOW);
  var=((float)analogRead(Corr))*2.45098;//1023)*1.1/0.47;
  myOLED.printNumF(var,1, CENTER,40);
//batería
  var=(float)analogRead(Bat)/100;
  myOLED.printNumF(var,2, RIGHT, 40);



  
  myOLED.update();
  if (digitalRead(Penc)==0){
    tiempo=millis();
  }
  delay(250);
  if (millis()>(tiempo+30000)){
    digitalWrite(Enc,HIGH);
    while(1);
  }
  
//  myOLED.clrScr();
//  for (int i=0; i<64; i+=2)
//  {
//    myOLED.drawLine(0, i, 127, 63-i);
//    myOLED.update();
//  }
//  for (int i=127; i>=0; i-=2)
//  {
//    myOLED.drawLine(i, 0, 127-i, 63);
//    myOLED.update();
//  }
//
//  delay(2000);
  
//  myOLED.clrScr();
//  myOLED.drawRect(0, 0, 127, 63);
//  for (int i=0; i<64; i+=4)
//  {
//    myOLED.drawLine(0, i, i*2, 63);
//    myOLED.update();
//  }
//  for (int i=0; i<64; i+=4)
//  {
//    myOLED.drawLine(127, 63-i, 127-(i*2), 0);
//    myOLED.update();
//  }
//
//  delay(2000);
  
//  myOLED.clrScr();
//  for (int i=0; i<10; i++)
//  {
//    myOLED.drawRoundRect(i*3, i*3, 127-(i*3), 63-(i*3));
//    myOLED.update();
//  }
//
//  delay(2000);
  
//  myOLED.clrScr();
//  for (int i=0; i<25; i++)
//  {
//    myOLED.drawCircle(64, 32, i*3);
//    myOLED.update();
//  }
//
//  delay(2000);
  
//  myOLED.clrScr();
//  myOLED.drawRect(0, 0, 127, 63);
//  myOLED.drawLine(0, 31, 127, 31);
//  myOLED.drawLine(63, 0, 63, 63);
//  for (int c=0; c<4; c++)
//  {
//    for (int i=0; i<128; i++)
//    {
//      y=i*0.04974188368183839294232518690191;
//      myOLED.invPixel(i, (sin(y)*28)+31);
//      myOLED.update();
//      delay(10);
//    }
//  }
//
//  delay(2000);

//  for (int pc=0; pc<3; pc++)
//  {
//    pacy=random(0, 44);
//  
//    for (int i=-20; i<132; i++)
//    {
//      myOLED.clrScr();
//      for (int p=6; p>((i+20)/20); p--)
//        myOLED.drawBitmap(p*20-8, pacy+7, pill, 5, 5);
//      switch(((i+20)/3) % 4)
//      {
//        case 0: bm=pacman1;
//                break;
//        case 1: bm=pacman2;
//                break;
//        case 2: bm=pacman3;
//                break;
//        case 3: bm=pacman2;
//                break;
//      }
//      myOLED.drawBitmap(i, pacy, bm, 20, 20);
//      myOLED.update();
//      delay(10);
//    }
//  }
//
//  for (int i=0; i<41; i++)
//  {
//    myOLED.clrScr();
//    myOLED.drawBitmap(22, i-24, The_End, 84, 24);
//    myOLED.update();
//    delay(50);
//  }
//  myOLED.print("Runtime (ms):", CENTER, 48);
//  myOLED.printNumI(millis(), CENTER, 56);
//  myOLED.update();
//  for (int i=0; i<5; i++)
//  {
//    myOLED.invert(true);
//    delay(1000);
//    myOLED.invert(false);
//    delay(1000);
//  }
}
