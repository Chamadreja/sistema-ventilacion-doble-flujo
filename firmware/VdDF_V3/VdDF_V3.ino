#include <Servo.h>

// Definir pines para sensores y actuadores
const int mq2Pin = A0;
const int lm135Pin = A3;
const int filtroAirePin = 7;
const int filtroCalorPin = 4;
const int servoPrimeraInterseccionPin = 2;
const int servoSegundaInterseccionPin = 3;
Servo servoPrimeraInterseccion;
Servo servoSegundaInterseccion;
const int ventiladorEntradaPin = 13; // Ventilador de entrada
const int ventiladorSalidaPin = 12; // Ventilador de salida
const int ledIndicadorPin = 8;

void setup() {
  // Inicialización de pines
  pinMode(filtroAirePin, OUTPUT);
  pinMode(filtroCalorPin, OUTPUT);
  pinMode(ventiladorEntradaPin, OUTPUT);
  pinMode(ventiladorSalidaPin, OUTPUT);
  pinMode(ledIndicadorPin, OUTPUT);

  // Inicialización de servos
  servoPrimeraInterseccion.attach(servoPrimeraInterseccionPin);
  servoSegundaInterseccion.attach(servoSegundaInterseccionPin);
}

void loop() {
  // Leer valores de los sensores
  int ppmAire = analogRead(mq2Pin); // Lee el valor del MQ-2
  int temperatura = analogRead(lm135Pin); // Lee el valor del LM-135

  // Convertir valores analógicos en ppm de aire y temperatura en grados Celsius
  ppmAire = map(ppmAire, 0, 1023, 0, 1000); // Suponiendo una escala de 0-1000 ppm
  float tempCelsius = (temperatura / 10.23) - 50; // Suponiendo una escala de 0-500°C

  // Control de filtro de aire
  if (ppmAire > 600) {
    digitalWrite(filtroAirePin, HIGH); // Encender el filtro de aire
  } else {
    digitalWrite(filtroAirePin, LOW); // Apagar el filtro de aire
  }

  // Control de filtro de calor
  if (tempCelsius < 22) {
    digitalWrite(filtroCalorPin, HIGH); // Encender el filtro de calor
  } else {
    digitalWrite(filtroCalorPin, LOW); // Apagar el filtro de calor
  }

  // Control de servomotor para la primera intersección
  if (tempCelsius >= 22) {
    servoPrimeraInterseccion.write(0); // 0 grados
  } else {
    servoPrimeraInterseccion.write(90); // 90 grados
  }

  // Control de servomotor para la segunda intersección
  if (tempCelsius >= 22 && ppmAire <= 600) {
    servoSegundaInterseccion.write(0); // 0 grados
  } else if (tempCelsius < 22 && ppmAire <= 600) {
    servoSegundaInterseccion.write(45); // 45 grados
  } else if (tempCelsius >= 22 && ppmAire > 600) {
    servoSegundaInterseccion.write(45); // 45 grados
  } else {
    servoSegundaInterseccion.write(90); // 90 grados
  }

  // Encender el ventilador de entrada
  digitalWrite(ventiladorEntradaPin, HIGH);

  // Encender el ventilador de salida
  digitalWrite(ventiladorSalidaPin, HIGH);

  // Encender el indicador LED
  digitalWrite(ledIndicadorPin, HIGH);

  // Retardo (ajusta el tiempo según sea necesario)
  delay(1000);
}
