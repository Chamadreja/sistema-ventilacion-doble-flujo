#include <Servo.h>

int mq2SensorPin = A0;
int lm135SensorPin = A3;
int ledPin = 13;
int servo1Pin = 2;
int servo2Pin = 3;
Servo servo1;
Servo servo2;
void setup() {
  pinMode(ledPin, OUTPUT);
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  // Inicializa cualquier otra configuración necesaria.
}
void loop() {
  int ppm = analogRead(mq2SensorPin);
  int temperature = analogRead(lm135SensorPin);
  
  // Convierte las lecturas en valores reales según las especificaciones de los sensores.
  ppm = map(ppm, 0, 1023, 0, 1000); // Ajusta a la escala de ppm.
  temperature = map(temperature, 0, 1023, -50, 150); // Ajusta a la escala de temperatura en °C.
  
  // Lógica para controlar el filtro de aire.
  if (ppm > 600) {
    digitalWrite(7, HIGH); // Enciende el filtro de aire.
  } else {
    digitalWrite(7, LOW); // Apaga el filtro de aire.
  }
  
  // Lógica para controlar el filtro de calor.
  if (temperature < 22) {
    digitalWrite(4, HIGH); // Enciende el filtro de calor.
  } else {
    digitalWrite(4, LOW); // Apaga el filtro de calor.
  }
  
  // Lógica para los servomotores.
  if (temperature < 22) {
    servo1.write(90); // Servomotor en 90°.
  } else {
    servo1.write(0); // Servomotor en 0°.
  }
  
  if (temperature >= 22 && ppm <= 600) {
    servo2.write(0); // Servomotor en 0°.
  } else if (temperature < 22 && ppm <= 600) {
    servo2.write(45); // Servomotor en 45°.
  } else if (temperature >= 22 && ppm > 600) {
    servo2.write(45); // Servomotor en 45°.
  } else {
    servo2.write(90); // Servomotor en 90°.
  }
  
  // Lógica para encender el led indicador.
  digitalWrite(ledPin, HIGH);
  
  // Aquí puedes agregar más lógica según sea necesario.
}
