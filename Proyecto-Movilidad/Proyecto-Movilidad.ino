// Conexión Bluetooth a nuestra PC
#include "BluetoothSerial.h"

// Librerías para conectar LCD
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Objeto LiquidCrystal_I2C, "lcd", con la default screen address I2C 0x27, 16 columnas y 2 filas

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

BluetoothSerial SerialBT;
char direccion;  // Variable para almacenar la dirección recibida por Bluetooth

// Definición de pines
#define InA1 33 // Motor A
#define InB1 25
#define InA2 26 // Motor B
#define InB2 27
#define ENA1 14 // Velocidad motor A
#define ENA2 32 // Velocidad motor B

void setup() {
  Serial.begin(115200);
  
  // Configuración de pines como salida
  pinMode(InA1, OUTPUT);
  pinMode(InB1, OUTPUT);
  pinMode(InA2, OUTPUT);
  pinMode(InB2, OUTPUT);
  pinMode(ENA1, OUTPUT);
  pinMode(ENA2, OUTPUT);

  // Inicialización de la conexión Bluetooth y de la pantalla LCD
  SerialBT.begin("Robot_Danya_Luis");
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Prueba BT Mov");
}

// Funciones de movimiento
void adelante() {
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, HIGH);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, HIGH);
  digitalWrite(ENA1, HIGH);
  digitalWrite(ENA2, HIGH);
}

void atras() {
  digitalWrite(InA1, HIGH);
  digitalWrite(InB1, LOW);
  digitalWrite(InA2, HIGH);
  digitalWrite(InB2, LOW);
  digitalWrite(ENA1, HIGH);
  digitalWrite(ENA2, HIGH);
}

void derecha() {
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, HIGH);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, LOW);
  digitalWrite(ENA1, HIGH);
  digitalWrite(ENA2, HIGH);
}

void izquierda() {
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, LOW);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, HIGH);
  digitalWrite(ENA1, HIGH);
  digitalWrite(ENA2, HIGH);
}

void detenido() {
  digitalWrite(InA1, LOW);
  digitalWrite(InB1, LOW);
  digitalWrite(InA2, LOW);
  digitalWrite(InB2, LOW);
  digitalWrite(ENA1, LOW);
  digitalWrite(ENA2, LOW);
}

void loop() {
  if (SerialBT.available()) {
    direccion = SerialBT.read();
    Serial.println(direccion);
    lcd.setCursor(0, 0); // Inicializa la posición del texto en la LCD

    if (direccion == '1') { // De acuerdo al valor (caracter) de dirección...
      adelante(); // Llama a la respectiva función de movimiento
      lcd.clear(); // Limpia el texto de la LCD en cada cambio de dirección
      lcd.print("1-Adelante");

    } else if (direccion == '2') {
      atras();
      lcd.clear();
      lcd.print("2-Atras");

    } else if (direccion == '3') {
      derecha();
      lcd.clear();
      lcd.print("3-Derecha");

    } else if (direccion == '4') {
      izquierda();
      lcd.clear();
      lcd.print("4-Izquierda");

    } else if (direccion == '5') { // Cualquier otra dirección lo vuelve a mover
      detenido();
      lcd.clear();
      lcd.print("5-Detenido");
    }
    delay(20);
  }
}
