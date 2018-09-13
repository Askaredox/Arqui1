#include <SoftwareSerial.h>
String ssid="ASKAR";
String password="cshpstp61";
SoftwareSerial esp(10, 11); // RX, TX
String server="http://35.237.204.69";
String contra="larosadeguadalupe123";
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
  esp.println("AT+CIPSTART=\"TCP\",\""+server+"\",80");
  if(esp.find("OK")){
    Serial.println("CONECTADO CON SERVIDOR");
    String peticion="GET /Test/app/Garaje.php?contrasena=";
    peticion+=contra+" HTTP/1.1\r\n";
    peticion+="Host: "+server+"\r\n\r\n";
    esp.print("AT+CIPSEND=");
    esp.println(peticion.length());
    if(esp.find(">")){
      
    }
  }
  else
    Serial.println("No se ha podido conectarse con el servidor");
  
}

void loop() { 
  

}
