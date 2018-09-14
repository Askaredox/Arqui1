#include <TimedAction.h>
#include  <Keypad.h>
#include  <Servo.h>
#include <SoftwareSerial.h>

//-------------------------------------------------START WIFI PART
SoftwareSerial esp(10, 11); // RX, TX
const String ssid="ASKAR";
String password="cshpstp61";
boolean con=false;
String server="35.237.204.69";
//---------------------------------------------------END WIFI PART

//-----------------------------------------------START GARAJE PART
byte pinesF[4] = {22,24,26,28};
byte pinesC[4] = {23,25,27,29};
char teclas[4][4] = {
  {'1','2','3','A'}, 
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}};
Keypad teclado = Keypad(makeKeymap(teclas), pinesF, pinesC, 4, 4);
char data[4]={'0','0','0','0'};
char tecla;
unsigned long antes;
unsigned long desp;
Servo puerta;
boolean abierto=false;
TimedAction garaje=TimedAction(10,Garaje);
//-------------------------------------------------END GARAJE PART

TimedAction incendio=TimedAction(10,Incendio);
void setup() {
  Serial.begin(9600);
  //DISPLAY1
  pinMode(30,OUTPUT);
  pinMode(31,OUTPUT);
  pinMode(32,OUTPUT);
  pinMode(33,OUTPUT);
  //DISPLAY2
  pinMode(34,OUTPUT);
  pinMode(35,OUTPUT);
  pinMode(36,OUTPUT);
  pinMode(37,OUTPUT);
  //DISPLAY3
  pinMode(38,OUTPUT);
  pinMode(39,OUTPUT);
  pinMode(40,OUTPUT);
  pinMode(41,OUTPUT);
  //DISPLAY4
  pinMode(42,OUTPUT);
  pinMode(43,OUTPUT);
  pinMode(44,OUTPUT);
  pinMode(45,OUTPUT);
  //LEDS DE PERMISO
  pinMode(A14,OUTPUT);
  pinMode(A15,OUTPUT);
  pinMode(A12,OUTPUT);
  //BUZZER
  pinMode(3,OUTPUT);
  
  //CONEXION A INTERNET
  esp.begin(9600);
  esp.println("AT+CWLAP");
  esp.println("AT+CWJAP=\""+ssid+"\",\""+password+"\"");
  Serial.println("Conectando a red WiFi...");
  esp.setTimeout(10000);
  if(esp.find("OK")){
    Serial.println("Conectado a "+ssid+"!");
    con=true;
  }
  else
    Serial.println("Error al conectarse con red WiFi!");
  while(!con){
    for(int i=0;i<4;i++)
      getInt('e',i);
  }
  //DISPLAYS EN 0000
  getInt('0',0);
  getInt('0',1);
  getInt('0',2);
  getInt('0',3);
  //LED VERDE
  analogWrite(A14,0);
  //LED ROJO
  analogWrite(A15,255);
  //SERVO
  puerta.attach(2);
  puerta.write(0);
}
void loop() {
  incendio.check();
  //garaje.check();

}
void Incendio(){
  int measure = analogRead(A13);
  if(measure < 500)
    digitalWrite(3,1);
  else
    digitalWrite(3,0);
}
void Garaje(){
  tecla = teclado.getKey();
  if (!abierto && tecla != 0){
    key(tecla);
  }
  if(abierto){
    desp=millis();
    if((desp-antes)>5000){//10 segundos
      abierto=false;
      digitalWrite(A14,0);
      digitalWrite(A15,255);
      puerta.write(0);
      
    }
  }
}
void key(char tecla){
  if(tecla=='#'){
    String contrasena="";
    for(int i=3;i>=0;i--)
      contrasena.concat(data[i]);
    analogWrite(A12,255);
    abierto=getPermiso(contrasena);
    analogWrite(A12,0);
    for(int i=0;i<4;i++){
      data[i]='0';
      getInt(data[i],i);  
    }
    
  }
  else if(tecla!=0){//componer los datos en el array
    data[3]=data[2];
    data[2]=data[1];
    data[1]=data[0];
    data[0]=tecla;
    for(int i=0;i<4;i++)
      getInt(data[i],i);
  }
}
boolean getPermiso(String contra){
  while(con){
    esp.println("AT+CIPSTART=\"TCP\",\""+server+"\",80");
    if(esp.find("OK")){
      
      Serial.println("CONECTADO CON SERVIDOR");
      String peticion="GET /Arqui1/Test/app/Garage.php?contrasena=";
      peticion+=contra+" HTTP/1.1\r\n";
      peticion+="Host: "+server+"\r\n\r\n";
      esp.print("AT+CIPSEND=");
      esp.println(peticion.length());
      Serial.println(peticion.length());
      if(esp.find(">")){
        //Serial.println("Enviando HTTP . . .");
          esp.println(peticion);
          if(esp.find("SEND OK")){
            Serial.println("Peticion HTTP enviada:");
            //Serial.println();
            //Serial.println(peticion);
            //Serial.println("Esperando respuesta...");
            boolean fin_respuesta=false; 
            long tiempo_inicio=millis(); 
            String cadena="";
            con=false;
            while(!fin_respuesta){
              while(esp.available()>0){
                char c=esp.read();
                //Serial.write(c);
                cadena.concat(c);  //guardamos la respuesta en el string "cadena"
              }
              int num;
              if((num=cadena.indexOf("CLOSED"))>0){
                //Serial.println(cadena[num-1]);
                if(cadena[num-1]=='1'){
                  digitalWrite(A14,255);
                  digitalWrite(A15,0);
                  puerta.write(180);
                  antes=millis();
                  abierto=true;
                  return true;
                }
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
  con =true;
  return false;
}
char getInt(char i,int t){//CONVERSOR DE CHAR A DISPLAY Y A CUÁL
  int g=4*t+30;
  switch(i){
    case '0':
      digitalWrite(g,0);
      digitalWrite(g+1,0);
      digitalWrite(g+2,0);
      digitalWrite(g+3,0);
      break;
    case '1':
      digitalWrite(g,1);
      digitalWrite(g+1,0);
      digitalWrite(g+2,0);
      digitalWrite(g+3,0);
      break;
    case '2':
      digitalWrite(g,0);
      digitalWrite(g+1,1);
      digitalWrite(g+2,0);
      digitalWrite(g+3,0);
      break;
    case '3':
      digitalWrite(g,1);
      digitalWrite(g+1,1);
      digitalWrite(g+2,0);
      digitalWrite(g+3,0);
      break;
    case '4':
      digitalWrite(g,0);
      digitalWrite(g+1,0);
      digitalWrite(g+2,1);
      digitalWrite(g+3,0);
      break;
    case '5':
      digitalWrite(g,1);
      digitalWrite(g+1,0);
      digitalWrite(g+2,1);
      digitalWrite(g+3,0);
      break;
    case '6':
      digitalWrite(g,0);
      digitalWrite(g+1,1);
      digitalWrite(g+2,1);
      digitalWrite(g+3,0);
      break;
    case '7':
      digitalWrite(g,1);
      digitalWrite(g+1,1);
      digitalWrite(g+2,1);
      digitalWrite(g+3,0);
      break;
    case '8':
      digitalWrite(g,0);
      digitalWrite(g+1,0);
      digitalWrite(g+2,0);
      digitalWrite(g+3,1);
      break;
    case '9':
      digitalWrite(g,1);
      digitalWrite(g+1,0);
      digitalWrite(g+2,0);
      digitalWrite(g+3,1);
      break;
    case 'e':
      digitalWrite(g,1);
      digitalWrite(g+1,0);
      digitalWrite(g+2,1);
      digitalWrite(g+3,1);
      break;
  } 
  return i;
}
