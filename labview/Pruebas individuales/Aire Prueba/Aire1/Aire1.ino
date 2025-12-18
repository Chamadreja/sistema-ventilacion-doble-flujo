#include <Servo.h> 
 
Servo myservo;            // Crea un objeto "myservo"
 
int adc = 0;               // Variable para el dato del ADC
char val=0;                // Variable para el puerto serial
char comando = 0;          // Guarda comando recibido

void setup() { 
  myservo.attach(9);      // Asignar el pin 9 el servomotor
  Serial.begin(9600);     // Inicializar el serial 
  
  pinMode(13, OUTPUT);    // Usar el pin 13 como referencia para el pot
  digitalWrite(13,HIGH);  // de 5V con un estado alto.
} 
 
void loop() { 
  if (Serial.available() == 2) {     // Si hay mas de 2 datos disponibles en el serial
    
     comando = Serial.read();        // Guarda el comando
     val = Serial.read();            // Guarda el canal
  
  if (comando == 'L'){    
      //val = map(val, 0, 255, 0, 179);    // Escalar los valores de 0 a 180 
      myservo.write(val);                  // Asignar la posicion del servo con el nuevo valor escalado 
      Serial.write(val);                   // Esperar un momento para que el servo llegue a la posicion deseada 
  }
  else if (comando == 'A'){
      adc = analogRead(A0);                // Leer del ADC
      adc = map(adc, 0, 1024, 0, 180);     // Escalar los valores de 0 a 180 
      myservo.write(adc);                  // Escribir el servo con el valor del ADC escalado
      Serial.print(adc);
  }
  else{
    Serial.write("Error");
  }

delay(15); 
  } 
} 