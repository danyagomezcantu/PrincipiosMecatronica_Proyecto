# Proyecto-Movilidad

Esta parte del proyecto consistió en probar la movilidad del robot a través de Bluetooth. El código se encarga de establecer una conexión Bluetooth con una PC y recibir comandos de dirección. Estos comandos se utilizan para controlar los motores del robot y moverlo en diferentes direcciones.

### Requisitos
* Placa ESP32 compatible
* Módulo Bluetooth
* Pantalla LCD I2C
* Motores y controladores de motor

### Configuración
Conecta el módulo Bluetooth y la pantalla LCD I2C a la ESP32, así como los motorreductores.

### Instalación
Se utilizaron las bibliotecas BluetoothSerial y LiquidCrystal_I2C.

### Uso
Una vez cargado el código en la placa ESP32, se abre el monitor serial y se conecta la PC al módulo Bluetooth (en nuestro caso, se llama "Robot_Danya_Luis"). Los comandos de dirección se envían desde la PC al robot a través de la conexión Bluetooth. El robot se mueve en la dirección especificada y muestra el estado en la pantalla LCD.

### Comandos de dirección
'1': Adelante
'2': Atrás
'3': Derecha
'4': Izquierda
'5': Detenido
