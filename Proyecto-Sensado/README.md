# Proyecto-Sensado

Este proyecto tiene como objetivo probar los sensores del robot. Se utilizan diferentes tipos de sensores para medir la luz, detectar obstáculos y medir distancias.

### Componentes utilizados
* LCD: Se utiliza un LCD de 16x2 para mostrar los valores de los sensores.
* Sensor ultrasónico: Se utiliza un sensor ultrasónico para medir distancias.
* Sensores infrarrojos: Se utilizan sensores infrarrojos para detectar obstáculos.
* Fotoresistores: Se utilizan fotoresistores para medir la intensidad de luz.

### Configuración del hardware
* LCD: se conecta a través de la interfaz I2C.
* Sensor ultrasónico: se conecta a los pines echoPin y trigPin.
* Sensores infrarrojos: se conectan a los pines infrarrojo1, infrarrojo2, infrarrojo3 y infrarrojo4.
* Fotoresistores: se conectan a los pines fotoresistorIzq y fotoresistorDer.
* Motorreductores: se conectan a los pines ENA1, InA1, InB1, ENA2, InA2 e InB2.
* Encoders: se conectan a los pines EncA1, EncA2, EncB1 y EncB2.

### Funciones principales

* monitorSerialPulsos(): Esta función muestra en el monitor serial la cantidad de pulsos registrados por los encoders izquierdo y derecho.
* Fotoresistor(): Esta función lee los valores de los fotoresistores y los muestra en el LCD y en el monitor serial.
* Ultrasonico(): Esta función realiza la lectura del sensor ultrasónico y calcula la distancia. Luego, muestra la distancia en el LCD y en el monitor serial.
* Obstaculos(): Esta función lee los valores de los sensores infrarrojos y determina si hay obstáculos. Luego, muestra los resultados en el LCD y en el monitor serial.

### Funciones de los encoders

* Encoder_izquierdo(): Esta función se ejecuta cuando se detecta un pulso en el encoder izquierdo. Incrementa o decrementa la cantidad de pulsos dependiendo del estado del pin B del encoder.
* Encoder_derecho(): Esta función se ejecuta cuando se detecta un pulso en el encoder derecho. Incrementa o decrementa la cantidad de pulsos dependiendo del estado del pin B del encoder.
