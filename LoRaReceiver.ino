/*
 *        -------------- Ejemplo básico receptor LoRa. RFM95W y ESP32. --------------
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
#include <LoRa.h>                               // https://github.com/sandeepmistry/arduino-LoRa

#define led 15                                  // LED utilizado para notificar la recepción de un mensaje.

void setup() {
  Serial.begin(115200);
  Serial.println("LoRa Receiver");

  LoRa.setPins(17,16,22);                       // NSS, RESET y DIO0.
  if (!LoRa.begin(868E6)) {                     // Frecuencia de la banda libre ISM en Europa. (868MHz) Si hay algun fallo de conexiones muestra el error.
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  pinMode(led,OUTPUT);
}
void loop() {

  int packetSize = LoRa.parsePacket();
  if (packetSize) {                             // Se ha recibido un paquete.
    
    Serial.print("Received packet '");

    digitalWrite(led,HIGH);                     // Parpadear LED al recibir el mensaje.
    delay(100);
    digitalWrite(led,LOW);

    while (LoRa.available()) {
      Serial.print((char)LoRa.read());
    }
    
    Serial.print("' with RSSI ");
    Serial.println(LoRa.packetRssi());
  }
}
