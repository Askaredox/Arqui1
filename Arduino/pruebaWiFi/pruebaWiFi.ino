#include <SoftwareSerial.h>
const String ssid="ASKAR";
String password="cshpstp61";
SoftwareSerial esp(10, 11); // RX, TX
String server="35.237.204.69";
String contra="1234";
void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(9600);
  esp.begin(9600);
  esp.println("AT+CWLAP");
  esp.println("AT+CWJAP=\""+ssid+"\",\""+password+"\"");
  Serial.println("Conectando...");
  esp.setTimeout(10000);
  if(esp.find("OK")){
    Serial.println("Conectado a "+ssid+"!");
  }
  else
    Serial.println("Error al conectarse!");
  boolean con=true;
  esp.setTimeout(5000);
  while(con){
  esp.println("AT+CIPSTART=\"TCP\",\""+server+"\",80");
  if(esp.find("OK")){
    con=false;
    Serial.println("CONECTADO CON SERVIDOR");
    String peticion="GET /Arqui1/Test/app/Garage.php?contrasena=";
    peticion+=contra+" HTTP/1.1\r\n";
    peticion+="Host: "+server+"\r\n\r\n";
    esp.print("AT+CIPSEND=");
    esp.println(peticion.length());
    if(esp.find(">")){
      Serial.println("Enviando HTTP . . .");
        esp.println(peticion);
        if(esp.find("SEND OK")){
          Serial.println("Peticion HTTP enviada:");
          Serial.println();
          Serial.println(peticion);
          Serial.println("Esperando respuesta...");
          
          boolean fin_respuesta=false; 
          long tiempo_inicio=millis(); 
          String cadena="";
          while(fin_respuesta==false){
            while(esp.available()>0){
              char c=esp.read();
              Serial.write(c);
              cadena.concat(c);  //guardamos la respuesta en el string "cadena"
              if(cadena.indexOf("CLOSED")>0){
                Serial.println(cadena);
                Serial.println("Cadena recibida correctamente, conexion finalizada");         
                fin_respuesta=true;
                break;
              }
            }
            if((millis()-tiempo_inicio)>10000){
              Serial.println("Tiempo de espera agotado");
              esp.println("AT+CIPCLOSE");
              if(esp.find("OK"))
                Serial.println("Conexion finalizada");
              fin_respuesta=true;
            }
            if(cadena.indexOf("CLOSED")>0){
              Serial.println(cadena);
              Serial.println("Cadena recibida correctamente, conexion finalizada");         
              fin_respuesta=true;
            }
          }
        }
        else
          Serial.println("No se ha podido enviar HTTP.....");
    }
  }
  else
    Serial.println("No se ha podido conectarse con el servidor...");
  }
}

void loop() { 
  

}
