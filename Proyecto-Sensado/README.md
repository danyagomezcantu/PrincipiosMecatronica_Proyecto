# Proyecto-Sensado

Este proyecto tiene como objetivo probar los sensores del robot. Se utilizan diferentes tipos de sensores para medir la luz, detectar obstáculos y medir distancias.

### Componentes utilizados
* LCD: Se utiliza un LCD de 16x2 para mostrar los valores de los sensores.
* Sensor ultrasónico: Se utiliza un sensor ultrasónico para medir distancias.
* Sensores infrarrojos: Se utilizan sensores infrarrojos para detectar obstáculos.
* Fotoresistores: Se utilizan fotoresistores para medir la intensidad de luz.

En el código puede consultarse la configuración de los pines.

### Funciones principales

* monitorSerialPulsos(): Esta función muestra en el monitor serial la cantidad de pulsos registrados por los encoders izquierdo y derecho.
* Fotoresistor(): Esta función lee los valores de los fotoresistores y los muestra en el LCD y en el monitor serial.
* Ultrasonico(): Esta función realiza la lectura del sensor ultrasónico y calcula la distancia. Luego, muestra la distancia en el LCD y en el monitor serial.
* Obstaculos(): Esta función lee los valores de los sensores infrarrojos y determina si hay obstáculos. Luego, muestra los resultados en el LCD y en el monitor serial.

### Funciones de los encoders

* Encoder_izquierdo(): Esta función se ejecuta cuando se detecta un pulso en el encoder izquierdo. Incrementa o decrementa la cantidad de pulsos dependiendo del estado del pin B del encoder.
* Encoder_derecho(): Esta función se ejecuta cuando se detecta un pulso en el encoder derecho. Incrementa o decrementa la cantidad de pulsos dependiendo del estado del pin B del encoder.
