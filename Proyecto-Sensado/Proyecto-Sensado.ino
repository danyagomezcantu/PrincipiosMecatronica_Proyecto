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

volatile long pulsesDer = 0;
volatile long pulsesIzq = 0;

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
  monitorSerialPulsos();
  Fotoresistor();
  Ultrasonico();
  Obstaculos();
  Serial.println();
}

// Funciones de sensado
void monitorSerialPulsos() {
  Serial.print("Pulsos_Enc_Izq:" + String(pulsesIzq) + " | Pulsos_Enc_Der:" + String(pulsesDer) + " | ");  
}

void Fotoresistor() {
  // Lectura de los fotoresistores
  luzDetectadaIzq = analogRead(fotoresistorIzq);
  luzDetectadaDer = analogRead(fotoresistorDer);

  // Impresión de los valores en el LCD
  lcd.setCursor(0,1);
  lcd.print("I:" + String(luzDetectadaIzq) + " | D:" + String(luzDetectadaDer));
  delay(1000);

  // Impresión de los valores en el monitor serial
  Serial.print("LDR_Izq:" + String(luzDetectadaIzq) + " | LDR_Der:" + String(luzDetectadaDer) + " |");
  delay(250);
}

void Ultrasonico() {

  // Lectura del sensor ultrasónico
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2); 

  // Envío de pulso
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Lectura de la duración del pulso, cálculo de distancia
  duracionUltrasonico = pulseIn(echoPin, HIGH);
  distanciaUltrasonico = 0.0343 * duracionUltrasonico * 0.5;

  // Envío de datos al LCD
  lcd.setCursor(11,0); 
  lcd.print("L:" + String(distanciaUltrasonico));
  Serial.print(" Distancia:" + String(distanciaUltrasonico) + " | ");
}

void Obstaculos() {
  // Lectura de sensores infrarrojos
  infra1 = digitalRead(infrarrojo1);
  infra2 = digitalRead(infrarrojo2);
  infra3 = digitalRead(infrarrojo3);
  infra4 = digitalRead(infrarrojo4);

  // Impresión de los valores en el LCD
  bool infra[] = {infra1, infra2, infra3, infra4};
  int obstaculo[] = {0, 0, 0, 0};

  for(int i = 0; i < 4; i++) {
    if(!infra[i]) {
      obstaculo[i] = 1;
    }
  }
  
  // Impresión de los valores en el monitor serial
  Serial.print("Obst:" + String(obstaculo[0]) + " " + String(obstaculo[1]) + " " + String(obstaculo[2]) + " " + String(obstaculo[3]) + " | ");
  
  // Impresión de los valores en el LCD
  lcd.setCursor(0,0);  
  lcd.print(String(obstaculo[0]) + " " + String(obstaculo[1]) + " " + String(obstaculo[2]) + " " + String(obstaculo[3]));
}

// Funciones de los pulsos de los encoders
void Encoder_izquierdo() {
  if(digitalRead(EncB1) == HIGH) {
    pulsesIzq++;
  } else {
    pulsesIzq--;
  }  
}

void Encoder_derecho() {
  if(digitalRead(EncB2) == HIGH) {
    pulsesDer++;
  } else {
    pulsesDer--;
  }
}
