// Librerías para conectar LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Objeto LiquidCrystal_I2C, "lcd", con la default screen address I2C 0x27, 16 columnas y 2 filas

// Definición de pines y variables
// Sensor ultrasónico
#define echoPin 12 
#define trigPin 13

// Sensores infrarrojos de izquierda a derecha
#define infrarrojo1 19
#define infrarrojo2 18
#define infrarrojo3 5
#define infrarrojo4 17

// Fotoresistores
#define fotoresistorIzq 34
#define fotoresistorDer 35 

// Motorreductores
#define ENA1 14
#define InB2 27
#define InA2 26
#define InB1 25
#define InA1 33
#define ENA2 32
#define EncA1 4
#define EncA2 15
#define EncB1 2
#define EncB2 16

// Variables
int luzDetectadaIzq;
int luzDetectadaDer;

int duracionUltrasonico;
int distanciaUltrasonico;

bool infra1, infra2, infra3, infra4;
int obstaculo[] = {0, 0, 0, 0};

// Configuración de pines
void setup() {
  Serial.begin(115200);

  pinMode(fotoresistorIzq, INPUT); // Configuración de los fotoresistores como entrada
  pinMode(fotoresistorDer, INPUT); 
  
  pinMode(trigPin, OUTPUT); // Configuración del sensor ultrasónico
  pinMode(echoPin, INPUT);
  
  pinMode(infrarrojo1, INPUT); // Configuración de los sensores infrarrojos
  pinMode(infrarrojo2, INPUT);
  pinMode(infrarrojo3, INPUT);
  pinMode(infrarrojo4, INPUT);
  
  pinMode(ENA1, OUTPUT); // Configuración de los motores
  pinMode(InA1, OUTPUT);  
  pinMode(InB1, OUTPUT); 
  pinMode(ENA2, OUTPUT); 
  pinMode(InA2, OUTPUT); 
  pinMode(InB2, OUTPUT); 
  pinMode(EncA1, INPUT); 
  pinMode(EncB1, INPUT); 
  pinMode(EncA2, INPUT);  
  pinMode(EncB2, INPUT); 
  
  lcd.init();   // Inicializa el LCD 
  lcd.backlight();   // Enciende la retroiluminación del LCD
}

void loop() {

  // Lectura de los encoders
  attachInterrupt(digitalPinToInterrupt(EncA1), Encoder_izquierdo, RISING);
  attachInterrupt(digitalPinToInterrupt(EncA2), Encoder_derecho, RISING);

  // Lectura de los sensores
  Fotoresistor();
  Ultrasonico();
  Obstaculos();
  Serial.println();

  // Movimiento del robot
  if (luzDetectadaIzq < 4000 & luzDetectadaDer < 4000) {
    if (distanciaUltrasonico>15) {
      if((obstaculo[0]==1 & obstaculo[1]==0 & obstaculo[2]==1 & obstaculo[3]==0)
      ||(obstaculo[0]==0 & obstaculo[1]==1 & obstaculo[2]==1 & obstaculo[3]==0)
      ||(obstaculo[0]==1 & obstaculo[1]==1 & obstaculo[2]==1 & obstaculo[3]==0)
      ||(obstaculo[0]==0 & obstaculo[1]==1 & obstaculo[2]==0 & obstaculo[3]==1)
      ||(obstaculo[0]==1 & obstaculo[1]==1 & obstaculo[2]==0 & obstaculo[3]==1)
      ||(obstaculo[0]==1 & obstaculo[1]==0 & obstaculo[2]==1 & obstaculo[3]==1)
      ||(obstaculo[0]==0 & obstaculo[1]==1 & obstaculo[2]==1 & obstaculo[3]==1)
      ||(obstaculo[0]==1 & obstaculo[1]==1 & obstaculo[2]==1 & obstaculo[3]==1)){
        atras(); 
      } else {
        if((obstaculo[1]==0 & obstaculo[2]==0)&((obstaculo[0]==0 & obstaculo[3]==0)||(obstaculo[0]==1 & obstaculo[3]==0)||(obstaculo[0]==1 & obstaculo[3]==1))){
          adelante();
        }
        else if((obstaculo[2]==0 & obstaculo[3]==0)&((obstaculo[0]==0 & obstaculo[1]==1)||(obstaculo[0]==1 & obstaculo[1]==1))){
          derecha();
        }
        else if((obstaculo[0]==0 & obstaculo[1]==0)&((obstaculo[2]==0 & obstaculo[3]==1)||(obstaculo[2]==1 & obstaculo[3]==0)||(obstaculo[2]==1 & obstaculo[3]==1))){
          izquierda();
        }
      }
    }
    else if (distanciaUltrasonico<15){
      detenido();
      delay(500);
      if((obstaculo[0]==0 & obstaculo[1]==0 & obstaculo[2]==0 & obstaculo[3]==0)
      ||(obstaculo[0]==1 & obstaculo[1]==0 & obstaculo[2]==0 & obstaculo[3]==0)
      ||(obstaculo[0]==0 & obstaculo[1]==1 & obstaculo[2]==0 & obstaculo[3]==0)
      ||(obstaculo[0]==1 & obstaculo[1]==1 & obstaculo[2]==0 & obstaculo[3]==0)
      ||(obstaculo[0]==0 & obstaculo[1]==0 & obstaculo[2]==1 & obstaculo[3]==0)
      ||(obstaculo[0]==1 & obstaculo[1]==0 & obstaculo[2]==1 & obstaculo[3]==0)
      ||(obstaculo[0]==0 & obstaculo[1]==1 & obstaculo[2]==1 & obstaculo[3]==0)
      ||(obstaculo[0]==1 & obstaculo[1]==1 & obstaculo[2]==1 & obstaculo[3]==0)
      ||(obstaculo[0]==0 & obstaculo[1]==0 & obstaculo[2]==0 & obstaculo[3]==1)
      ||(obstaculo[0]==1 & obstaculo[1]==0 & obstaculo[2]==0 & obstaculo[3]==1)
      ||(obstaculo[0]==0 & obstaculo[1]==1 & obstaculo[2]==0 & obstaculo[3]==1)
      ||(obstaculo[0]==1 & obstaculo[1]==1 & obstaculo[2]==0 & obstaculo[3]==1)
      ||(obstaculo[0]==0 & obstaculo[1]==0 & obstaculo[2]==1 & obstaculo[3]==1)
      ||(obstaculo[0]==1 & obstaculo[1]==0 & obstaculo[2]==1 & obstaculo[3]==1)
      ||(obstaculo[0]==0 & obstaculo[1]==1 & obstaculo[2]==1 & obstaculo[3]==1)
      ||(obstaculo[0]==1 & obstaculo[1]==1 & obstaculo[2]==1 & obstaculo[3]==1)){
        atras();   
      }
    }
  } else {
    detenido();
    if(luzDetectadaIzq > luzDetectadaDer) {
      while(luzDetectadaIzq > luzDetectadaDer){
        izquierda();
      }
    } else if(luzDetectadaIzq < luzDetectadaDer){
      while(luzDetectadaIzq < luzDetectadaDer){
        derecha();
      }
    }
  }
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

// Funciones de sensado
void Fotoresistor(){
  luzDetectadaIzq = analogRead(fotoresistorIzq);
  luzDetectadaDer = analogRead(fotoresistorDer);
  lcd.setCursor(0,1);
  lcd.print("I:" + String(luzDetectadaIzq) + " | D:" + String(luzDetectadaDer));
  delay(1000);
}

void Ultrasonico(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracionUltrasonico = pulseIn(echoPin,HIGH);
  distanciaUltrasonico = 0.0343 * duracionUltrasonico * 0.5;

  lcd.setCursor(11,0); 
  lcd.print("L:"+String(distanciaUltrasonico));
}

void Obstaculos(){
  infra1 = digitalRead(infrarojo1);
  infra2 = digitalRead(infrarojo2);
  infra3 = digitalRead(infrarojo3);
  infra4 = digitalRead(infrarojo4);

  bool infra[] = {infra1, infra2, infra3, infra4};

  for(int i=0;i<4;i++){
    if(!infra[i]){
      obstaculo[i] = 1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print(String(obstaculo[0])+" "+String(obstaculo[1])+" "+String(obstaculo[2])+" "+String(obstaculo[3]));
}
