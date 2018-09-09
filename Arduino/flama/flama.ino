const int sensorPin = A13;
 
void setup() {
   Serial.begin(9600);
   pinMode(3,OUTPUT);
}
 
void loop() 
{
   int measure = analogRead(sensorPin);
   Serial.print(measure);
  
   if(measure < 500)
   {
      digitalWrite(3,1);
   }
   else{
    digitalWrite(3,0);
   }
}
