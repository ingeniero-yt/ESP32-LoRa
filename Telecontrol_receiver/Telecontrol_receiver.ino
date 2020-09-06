/*
 *      -----RECEPTOR LORA TELECONTROL CON ESP32-----
 * 
 * Por "Ingeniero en Casa"
 * https://www.youtube.com/channel/UCurfoG9YbFyQmxCLlxZVArg
 * 
 * La distribución y/o modificación del código es totalmente libre.
 */
 
#include <SPI.h>
#include <LoRa.h>

#define NSS 15
#define RST 22
#define DIO0 36

#define LED1 27
#define LED2 26
#define LED3 33
#define LED4 32

byte numMsg = 0;

void InitLEDs(){
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);

  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);  
}

void onReceive(int packetSize){

  numMsg = LoRa.read();  
}

void setup(){
  Serial.begin(115200);
  Serial.println("LoRa Telecontrol receiver");

  delay(500); 

  InitLEDs();

  LoRa.setPins(NSS, RST, DIO0);       // Importante configurar los pines SS y RESET, además del pin de interrupción D0.
  
  if (!LoRa.begin(868E6)) {
    Serial.println("Starting LoRa failed!");
    while (1);
  }

  LoRa.onReceive(onReceive);          // Activar la interrupción al recibir mensaje.

  LoRa.receive();                     // Poner chip LoRa como receptor.
}

void loop(){

  switch (numMsg){

    case 0: break;
    
    case 1: digitalWrite(LED1, !digitalRead(LED1));
            numMsg = 0;
            break;
            
    case 2: digitalWrite(LED2, !digitalRead(LED2));
            numMsg = 0;
            break;
            
    case 3: digitalWrite(LED3, !digitalRead(LED3));
            numMsg = 0;
            break;
            
    case 4: digitalWrite(LED4, !digitalRead(LED4));
            numMsg = 0;
            break;
            
    default: numMsg = 0;
             break;  
  }
}
