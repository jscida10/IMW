#include <U8g2lib.h>
#include <Wire.h>

#define MedI A7
#define Bat A6
#define Corr A0
#define Vin A1
#define Vout A2
#define Alim5 A3
#define Enc 3
#define Alim12 4
#define Penc 13


extern uint8_t logo[];


// Inicializa la pantalla con el controlador SSH1106, usando la dirección I2C
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

float var = 0;
long tiempo = 0;

void setup()
{
  u8g2.begin();  // Iniciar la pantalla
  analogReference(INTERNAL);

  // Configuración inicial
  pinMode(Enc, OUTPUT);
  pinMode(Alim5, OUTPUT);
  pinMode(Alim12, OUTPUT);
  pinMode(MedI, OUTPUT);

  digitalWrite(Enc, LOW);
  digitalWrite(Alim5, LOW);
  digitalWrite(Alim12, LOW);
  digitalWrite(MedI, LOW);

  tiempo = millis();
  
  // Mostrar el logo al inicio
  u8g2.clearBuffer();
  u8g2.drawXBMP(15, 14, 97, 36, logo);  // Aquí puedes definir tu bitmap/logo
  u8g2.sendBuffer();
  delay(300);  // Mostrar el logo durante 1 segundo
  //https://github.com/bnielsen1965/oled-sh1106/blob/master/lib/constants.js
  u8g2.sendF("c", 0x0a7);
  delay(100);  // Mostrar el logo durante 1 segundo
  u8g2.sendF("c", 0x0a6);
  delay(300);  // Mostrar el logo durante 1 segundo
  u8g2.sendF("c", 0x0a7);
  delay(100);  // Mostrar el logo durante 1 segundo
  u8g2.sendF("c", 0x0a6);
  delay(300);  // Mostrar el logo durante 1 segundo
  u8g2.sendF("c", 0x0a7);
  delay(100);  // Mostrar el logo durante 1 segundo
  u8g2.sendF("c", 0x0a6);
//  u8g2.clearBuffer();
//  u8g2.setFont(u8g2_font_helvR08_tr);
//  u8g2.drawButtonUTF8(62, 20, U8G2_BTN_BW2, 0,  2,  2, "Btn" );
//  u8g2.sendBuffer();
//  delay(1000);
}

void loop()
{
  u8g2.clearBuffer();  // Limpiar el buffer de la pantalla
  
  u8g2.setFont(u8g2_font_ncenB08_tr);  // Fuente de texto pequeña
  u8g2.drawStr(0, 12, "Vin:");
  u8g2.drawStr(0, 32, "Vout:");
  u8g2.drawStr(50, 32, "I[mA]");
  u8g2.drawStr(90, 32, "Bat:");
  
  // Medición y visualización de voltajes/corrientes
  // Vin
  digitalWrite(MedI, HIGH);
  digitalWrite(Alim5, LOW);
  delay(50);
  var = (float)analogRead(Vin) / 51.8072289;
  u8g2.setFont(u8g2_font_ncenB14_tr);  // Fuente más grande
  u8g2.setCursor(50, 14);
  u8g2.print(var, 2);

  u8g2.setFont(u8g2_font_ncenB08_tr);  // Fuente de texto pequeña
  
  // Vout
  var = 5.0; // Medición simulada
  u8g2.setCursor(0, 54);
  u8g2.print(var, 2);

  // Corriente
  digitalWrite(MedI, LOW);
  var = ((float)analogRead(Corr)) * 2.45098;
  u8g2.setCursor(50, 54);
  u8g2.print(var, 1);

  // Batería
  var = (float)analogRead(Bat) / 100;
  u8g2.setCursor(90, 54);
  u8g2.print(var, 2);

  // Actualizar la pantalla
  u8g2.sendBuffer();

  // Control de tiempo de inactividad
  if (digitalRead(Penc) == 0) {
    tiempo = millis();
  }
  delay(250);
  if (millis() > (tiempo + 30000)) {
    digitalWrite(Enc, HIGH);
    while (1);
  }
}
