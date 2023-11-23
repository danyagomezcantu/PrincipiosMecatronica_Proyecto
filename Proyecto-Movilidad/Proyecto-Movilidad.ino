//Conexión Bluetooth a nuestra PC
#include "BluetoothSerial.h"

// Pantalla LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
char direccion;

//Puertos
#define ENA1 14
#define InB2 27 //MB
#define InA2 26 //MA
#define InB1 25 //MB
#define InA1 33 //MA
#define ENA2 32

void setup() {
  Serial.begin(115200);
  pinMode(ENA1, OUTPUT);
  pinMode(InA1, OUTPUT);
  pinMode(InB1, OUTPUT);
  pinMode(ENA2, OUTPUT);
  pinMode(InA2, OUTPUT);
  pinMode(InB2, OUTPUT);

  SerialBT.begin("Robot_Luis_Danya");
  lcd.init();   // Inicializa el LCD
  lcd.backlight();   // Enciende la retroiluminación del LCD
  lcd.setCursor(0,0);   // Establece la posición del cursor en la columna 0, fila 1
  lcd.print("Prueba BT Mov");
}
void loop() {
  if (SerialBT.available()) {
    direccion = SerialBT.read();
    Serial.println(direccion);
    lcd.setCursor(0,0);   

    if(direccion=='1'){
      adelante();
      lcd.clear();
      lcd.print("1-Adelante");
      
    } else if(direccion=='2'){
      atras();
      lcd.clear();
      lcd.print("2-Atras"); 

    } else if(direccion=='3'){
      derecha();
      lcd.clear();
      lcd.print("3-Derecha"); 

    } else if(direccion=='4'){
      izquierda();
      lcd.clear();
      lcd.print("4-Izquierda"); 

    } else if (direccion=='5' ) { // Cualquier otra indicación lo vuelve a mover
      detenido();
      lcd.clear(); 
      lcd.print("5-Detenido"); 
    }
    delay(20);
  } 
}

void adelante()
{
  digitalWrite(ENA1,HIGH);
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, HIGH);
  digitalWrite(ENA2,HIGH);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, HIGH);
}

 void atras()
 {
   digitalWrite(ENA1,HIGH);
   digitalWrite(InA1, HIGH);
   digitalWrite(InB1, LOW);
   digitalWrite(ENA2,HIGH);
   digitalWrite(InA2, HIGH);
   digitalWrite(InB2, LOW);
 }

 void derecha(){
   digitalWrite(ENA1, HIGH);
   digitalWrite(InA1, LOW);
   digitalWrite(InB1, HIGH);
   digitalWrite(ENA2, HIGH);
   digitalWrite(InA2, LOW);
   digitalWrite(InB2, LOW);
}

void izquierda()
{
  digitalWrite(ENA1, HIGH);
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, LOW);
  digitalWrite(ENA2, HIGH);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, HIGH);
}

void detenido()
{
  digitalWrite(ENA1, LOW);
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, LOW);
  digitalWrite(ENA2,LOW);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, LOW);
}
