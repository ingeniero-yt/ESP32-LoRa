/*
 *        -------------- Ejemplo básico emisor LoRa. RFM95W y ESP32. --------------
 * 
 * Conexiones entre el ESP32 y RFM95W (SPI):
 * MISO -> 19
 * MOSI -> 22
 * SCK  -> 18
 * 
 * Por "Ingeniero en Casa"
 * https://www.youtube.com/channel/UCurfoG9YbFyQmxCLlxZVArg
 * 
 * La distribución y/o modificación del código es totalmente libre.
 * 
 */

#include <SPI.h>
#include <LoRa.h>                             // https://github.com/sandeepmistry/arduino-LoRa

#define led 15                                // LED utilizado para notificar la emisión de un mensaje.
int counter = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("LoRa Sender");

  LoRa.setPins(17,16,22);                     // NSS, RESET y DIO0.
  if (!LoRa.begin(868E6)) {                   // Frecuencia de la banda libre ISM en Europa. (868MHz) Si hay algun fallo de conexiones muestra el error.
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  pinMode(led,OUTPUT);
}
void loop() {
  Serial.print("Sending packet: ");
  Serial.println(counter);

  // send packet
  LoRa.beginPacket();                       // Crear nuevo mensaje.
  LoRa.print("hello ");                     // Contenido del mensaje.
  LoRa.print(counter);                      // Contenido del mensaje.
  LoRa.endPacket();                         // Enviar mensaje.
  
  digitalWrite(led,HIGH);                   // Parpadear LED al enviar el mensaje.
  delay(100);
  digitalWrite(led,LOW);

  counter++;                                // Aumentar contador para el siguiente mensaje.
  delay(5000);
}
