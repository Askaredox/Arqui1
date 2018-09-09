#include <SoftwareSerial.h>
String ssid="Askaredox";
String password="del uno al ocho";
SoftwareSerial esp(10, 11); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  esp.begin(9600);
  esp.println("AT+CWJAP=\""+ssid+"\",\""+password+"\"");
  Serial.println("Conectando...");
  esp.setTimeout(10000);
  if(esp.find("OK")){
    Serial.println("Conectado a "+ssid+"!");
  }
  else
    Serial.println("Error al conectarse!");
  
}

void loop() { 
  

}
