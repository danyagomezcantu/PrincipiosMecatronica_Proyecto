// Pantalla LCD
#include <Wire.h> // Incluye la librería Wire, que permite la comunicación I2C
#include <LiquidCrystal_I2C.h> // Incluye la librería LiquidCrystal_I2C, que permite controlar pantallas LCD con interfaz I2C

LiquidCrystal_I2C lcd(0x27, 16, 2); // Crea un objeto lcd de la clase LiquidCrystal_I2C, con la dirección I2C 0x27 y especifica que la pantalla tiene 16 columnas y 2 filas

//Para definir la izquierda y la derecha es viendo el robot desde atrás de la pila
//Puertos
#define fotoresistorIzq 34 //Fotoresistores
#define fotoresistorDer 35 
#define echoPin 12 //Ultrasonico
#define trigPin 13
#define infrarojo1 19 //Infrarojos de izquierda a derecha
#define infrarojo2 18
#define infrarojo3 5
#define infrarojo4 17
#define ENA1 14 //Encoder (2 derecha, 1 izquierda)
#define InB2 27 //MB
#define InA2 26 //MA
#define InB1 25 //MB
#define InA1 33 //MA
#define ENA2 32
#define EncA1 4 // Pin A del encoder 1
#define EncA2 15 // Pin A del encoder 2
#define EncB1 2 // Pin B del encoder 1
#define EncB2 16 // Pin B del encoder 2

//Variables
int luzDetectadaIzq;
int luzDetectadaDer;
int duracionUltrasonico;
int distanciaUltrasonico;
bool infra1, infra2, infra3, infra4;
volatile long pulsesDer = 0;
volatile long pulsesIzq = 0;

void setup() {
  Serial.begin(115200);

  pinMode(fotoresistorIzq, INPUT); // Configuracion fotoresistencias como entrada
  pinMode(fotoresistorDer, INPUT); 
  pinMode(trigPin, OUTPUT); // Configuracion del utrasonico
  pinMode(echoPin, INPUT);
  pinMode (infrarojo1, INPUT); // Configuracion de sensores infrarojos
  pinMode (infrarojo2, INPUT);
  pinMode (infrarojo3, INPUT);
  pinMode (infrarojo4, INPUT);
  pinMode(ENA1, OUTPUT);
  pinMode(InA1, OUTPUT);
  pinMode(InB1, OUTPUT);
  pinMode(ENA2, OUTPUT);
  pinMode(InA2, OUTPUT);
  pinMode(InB2, OUTPUT);
  pinMode(EncA1, INPUT); // Configuración del encoder
  pinMode(EncB1, INPUT);
  pinMode(EncA2, INPUT); 
  pinMode(EncB2, INPUT);
  lcd.init();   // Inicializa el LCD
  lcd.backlight();   // Enciende la retroiluminación del LCD
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
  attachInterrupt(digitalPinToInterrupt(EncA1), Encoder_izquierdo, RISING);
  attachInterrupt(digitalPinToInterrupt(EncA2), Encoder_derecho, RISING);

  monitorSerialPulsos();
  Fotoresistor();
  Ultrasonico();
  Obstaculos();
  Serial.println();

  if (luzDetectadaIzq < 4095 & luzDetectadaDer < 4095) {
    if (distanciaUltrasonico>20) {
      if (obstaculo[0]==0 & obstaculo[1]==0 & obstaculo[2]==0 & obstaculo[3]==0) {
        if(luzDetectadaIzq > luzDetectadaDer) {
          izquierda();
        }else if(luzDetectadaIzq < luzDetectadaDer){
          derecha();
        }else if(luzDetectadaIzq == luzDetectadaDer){
          adelante();
        }
//      } else if (obstaculo[0]==0 & obstaculo[1]==1 & obstaculo[2]==0 & obstaculo[3]==0) {
//        derecha();
//      } else if (direccion == '3') {
//        derecha();
//        lcd.clear();
//        lcd.print("3-Derecha");
//
//      } else if (direccion == '4') {
//        izquierda();
//        lcd.clear();
//        lcd.print("4-Izquierda");
//
//      } else if (direccion == '5') { // Cualquier otra dirección lo vuelve a mover
//        detenido();
//        lcd.clear();
//        lcd.print("5-Detenido");
//      }
      delay(20);
    }
    else {
      detenido();
    }
  }
}

void monitorSerialPulsos(){
  Serial.print("Pulsos_Enc_Izq:"+String(pulsesIzq)+" | Pulsos_Enc_Der:"+String(pulsesDer)+" | ");  
}

void Fotoresistor(){
  luzDetectadaIzq = analogRead(fotoresistorIzq);
  luzDetectadaDer = analogRead(fotoresistorDer);
  lcd.setCursor(0,1);
  lcd.print("I:" + String(luzDetectadaIzq) + " | D:" + String(luzDetectadaDer));
  delay(1000);

  Serial.print("LDR_Izq:"+String(luzDetectadaIzq)+" | LDR_Der:"+String(luzDetectadaDer)+" |");

  delay(250);
}

void Ultrasonico(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); // decía 1000

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  duracionUltrasonico = pulseIn(echoPin,HIGH);

  distanciaUltrasonico = 0.0343 * duracionUltrasonico * 0.5;

  lcd.setCursor(11,0); 
  lcd.print("L:"+String(distanciaUltrasonico));
  Serial.print(" Distancia:"+String(distanciaUltrasonico)+" | ");
}

void Obstaculos(){
  //lectura de sensores inflarojos
  infra1 = digitalRead(infrarojo1);
  infra2 = digitalRead(infrarojo2);
  infra3 = digitalRead(infrarojo3);
  infra4 = digitalRead(infrarojo4);

  bool infra[] = {infra1, infra2, infra3, infra4};
  int obstaculo[] = {0, 0, 0, 0};

  for(int i=0;i<4;i++){
    if(!infra[i]){
      obstaculo[i] = 1;
    }
  }
  
  Serial.print("Obst:"+String(obstaculo[0])+" "+String(obstaculo[1])+" "+String(obstaculo[2])+" "+String(obstaculo[3])+" | ");
  lcd.setCursor(0,0);   // Establece la posición del cursor en la columna 0, fila 0
  lcd.print(String(obstaculo[0])+" "+String(obstaculo[1])+" "+String(obstaculo[2])+" "+String(obstaculo[3]));
}

void Encoder_izquierdo(){
  if(digitalRead(EncB1)==HIGH){
      pulsesIzq++;
  } else {
    pulsesIzq--;
  }  
}

void Encoder_derecho(){
  if(digitalRead(EncB2)==HIGH){
    pulsesDer++;
  } else {
    pulsesDer--;
  }

}
