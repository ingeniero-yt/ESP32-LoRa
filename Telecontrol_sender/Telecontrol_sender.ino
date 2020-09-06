/*
 *      -----EMISOR LORA TELECONTROL CON ESP32-----
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

#define BT1 27
#define BT2 25
#define BT3 35
#define BT4 36

#define DELAY_BTN 500  // 500 ms

byte pressedBtn = 0;
long timelast = 0;

void InitButtons(){

  pinMode(BT1, INPUT_PULLUP);
  pinMode(BT2, INPUT_PULLUP);
  pinMode(BT3, INPUT_PULLUP);
  pinMode(BT4, INPUT_PULLUP);
  
  attachInterrupt(BT1, ISR, FALLING);
  attachInterrupt(BT2, ISR, FALLING);
  attachInterrupt(BT3, ISR, FALLING);
  attachInterrupt(BT4, ISR, FALLING);  
}

void ISR(){
  
  if (!digitalRead(BT1)) pressedBtn = 1;
  else if (!digitalRead(BT2)) pressedBtn = 2;
  else if (!digitalRead(BT3)) pressedBtn = 3;
  else if (!digitalRead(BT4)) pressedBtn = 4;
  else pressedBtn = 0;
}

void setup(){
  
  Serial.begin(115200);
  Serial.println("LoRa Telecontrol sender");

  delay(500);
  
  InitButtons();
  
  LoRa.setPins(NSS, RST);       // Importante configurar los pines SS y RESET.
  
  if (!LoRa.begin(868E6)){
    Serial.println("Starting LoRa failed!");
    while (1);
  }
  LoRa.setTxPower(10);          // Seleccionar potencia de transmisión. [2dB - 20dB] 
}

void loop(){

  if (pressedBtn > 0){
    
    if (millis() - timelast > DELAY_BTN){
       
      LoRa.beginPacket();
      LoRa.print(pressedBtn);
      LoRa.endPacket();
      timelast = millis();  
    }
    pressedBtn = 0;
  }
}
