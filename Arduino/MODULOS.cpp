//----------DISTANCIA POR US----------//
#define UST 2
#define USE 3
void setup(){
  Serial.begin(9600);
  pinMode(UST,OUTPUT);
  pinMode(USE,INPUT);
  
}
void loop(){
  long duration,distance;
  digitalWrite(UST,LOW);
  delayMicroseconds(2);
  digitalWrite(UST,HIGH);
  delayMicroseconds(10);
  digitalWrite(UST,LOW);
  duration=pulseIn(USE,HIGH);
  distance=(duration-34.667)/50.114;
  Serial.print(duration);
  Serial.print(" - ");
  Serial.println(distance);
}
//----------SENSOR DE MOVIMIENTO----------//
int led = 13; //PIN usado para lED
 int PIR = 8; //PIN usado para Sensor
 int valor; //Variable para el valor del Sensor.

void setup() {
  pinMode(led,OUTPUT); 
  pinMode(PIR,INPUT); 
}

void loop() {
  valor = digitalRead(PIR); 
  if(valor == HIGH){ 
    digitalWrite(led,HIGH); 
  }
  else{
    digitalWrite(led,LOW); 
  }
}
//----------GARAJE-----INCENDIO----------//
#include <TimedAction.h>
#include<Keypad.h>
#include<Servo.h>
byte pinesF[4] = {22,24,26,28};
byte pinesC[4] = {23,25,27,29};
char teclas[4][4] = {
  {'1','2','3','A'}, 
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}};
Keypad teclado = Keypad(makeKeymap(teclas), pinesF, pinesC, 4, 4);
Servo puerta;
char tecla;
char data[4]={'0','0','0','0'};
char pass[4]={'1','2','3','4'};
unsigned long antes;
unsigned long desp;
boolean abierto=false;
TimedAction garaje=TimedAction(10,Garaje);
TimedAction incendio=TimedAction(10,Incendio);
void setup(){
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
  //BUZZER
  pinMode(3,OUTPUT);
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
void loop(){
  incendio.check();
  garaje.check();
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
  if(tecla=='#'&&data[3]==pass[0]&&data[2]==pass[1]&&data[1]==pass[2]&&data[0]==pass[3]){//contraseña de usuario
        digitalWrite(A14,255);
        digitalWrite(A15,0);
        getInt('0',0);
        getInt('0',1);
        getInt('0',2);
        getInt('0',3);
        data[0]='0';
        data[1]='0';
        data[2]='0';
        data[3]='0';
        puerta.write(180);
        antes=millis();
        abierto=true;
    }
    else if(tecla=='*'&&data[3]=='2'&&data[2]=='5'&&data[1]=='0'&&data[0]=='8'){//contraseña de administrador
        digitalWrite(A14,255);
        digitalWrite(A15,255);
        getInt('0',0);
        getInt('0',1);
        getInt('0',2);
        getInt('0',3);
        data[0]='0';
        data[1]='0';
        data[2]='0';
        data[3]='0';
        bool ex=true;
        while(ex){
          tecla = teclado.getKey();
          if(tecla=='*'){
            pass[0]=data[3];
            pass[1]=data[2];
            pass[2]=data[1];
            pass[3]=data[0];
            data[0]='0';
            data[1]='0';
            data[2]='0';
            data[3]='0';
            getInt('0',0);
            getInt('0',1);
            getInt('0',2);
            getInt('0',3);
            ex=false;
            break;
          }
          if(tecla!=0){
            data[3]=data[2];
            data[2]=data[1];
            data[1]=data[0];
            data[0]=tecla;
            for(int i=0;i<4;i++){
              getInt(data[i],i);  
            }
          }
        }
        digitalWrite(A14,0);
        digitalWrite(A15,255);
    }
    else if(tecla=='#'){
      getInt('0',0);
      getInt('0',1);
      getInt('0',2);
      getInt('0',3);
      data[0]='0';
      data[1]='0';
      data[2]='0';
      data[3]='0';
      digitalWrite(14,0);
      digitalWrite(15,255);
    }
    else{
      data[3]=data[2];
      data[2]=data[1];
      data[1]=data[0];
      data[0]=tecla;
      for(int i=0;i<4;i++){
        getInt(data[i],i);  
      }
    }
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
  } 
  return i;
}