# Proyecto-Final

Este proyecto consiste en un robot (controlado por la ESP32 Dev Kit V1) que utiliza diferentes sensores para moverse de manera automatizada. El código fuente se encuentra en el archivo Proyecto-Final.ino.

### Descripción del proyecto
El objetivo de este proyecto es construir un robot capaz de moverse de manera autónoma y realizar acciones en función de los datos recopilados por sus sensores. El robot utiliza los siguientes componentes:

* Sensor ultrasónico: se utiliza para medir la distancia entre el robot y los objetos cercanos.
* Sensores infrarrojos (de obstáculos): se utilizan para detectar obstáculos en diferentes direcciones.
* Fotoresistores: se utilizan para medir la intensidad de la luz en dos direcciones.
* Motorreductores: se utilizan para controlar los movimientos del robot.

El robot está programado para realizar las siguientes acciones:

* Lectura de los sensores: el robot lee los valores de los fotoresistores, el sensor ultrasónico y los sensores infrarrojos.
* Movimiento del robot: en función de los datos de los sensores, el robot decide cómo moverse. Si no hay obstáculos y la luz es adecuada, el robot avanza. Si hay obstáculos, el robot puede moverse hacia atrás, girar a la derecha o girar a la izquierda para evitarlos. Si la distancia medida por el sensor ultrasónico es menor a 15 cm, el robot se detiene temporalmente y luego decide cómo moverse.
* Visualización en el LCD: el robot muestra información en una pantalla LCD, como la intensidad de la luz detectada por los fotoresistores y la distancia medida por el sensor ultrasónico.

### Configuración del hardware

El proyecto requiere la conexión de los siguientes componentes a la ESP32:

* LCD: se conecta a través de la interfaz I2C.
* Sensor ultrasónico: se conecta a los pines echoPin y trigPin.
* Sensores infrarrojos: se conectan a los pines infrarrojo1, infrarrojo2, infrarrojo3 y infrarrojo4.
* Fotoresistores: se conectan a los pines fotoresistorIzq y fotoresistorDer.
* Motorreductores: se conectan a los pines ENA1, InA1, InB1, ENA2, InA2 e InB2.
* Encoders: se conectan a los pines EncA1, EncA2, EncB1 y EncB2.

### Configuración del software

El código fuente proporciona las funciones necesarias para controlar el movimiento del robot y leer los valores de los sensores. El bucle principal del programa se encarga de leer los sensores, tomar decisiones de movimiento y mostrar información en el LCD.

Para compilar y cargar el código en la IDE de Arduino, se requiere la instalación de las siguientes bibliotecas:
* Wire.h: biblioteca para la comunicación I2C.
* LiquidCrystal_I2C.h: biblioteca para controlar el LCD.
Una vez cargado el código en la ESP32, el robot está listo para funcionar.
