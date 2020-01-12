#include <DS1302.h>
// DS1302:  CE pin   - RST -> Arduino Digital 2
//          I/O pin  - DAT -> Arduino Digital 3
//          SCLK pin - CLK -> Arduino Digital 4
DS1302 rtc(2, 3, 4);

int PirPin = 5; // sensor
int SirPin = 7; // sirene
int LedPin = 13;//led sensor

void setup()
{
  
  rtc.halt(false);
  rtc.writeProtect(false);
  

  Serial.begin(9600);
  pinMode(PirPin, INPUT);
  pinMode(LedPin,OUTPUT);
  pinMode(SirPin,OUTPUT);
  delay (120000);//2min
}


void loop()
{
  String s;
  int pirVal;
  s = rtc.getTimeStr();
  
  if ( s.substring(0,2).toInt() >= 19 ||  s.substring(0,2).toInt() <= 5 ){
      
      pirVal = digitalRead(PirPin);
      if(pirVal == HIGH){ //quando não houver movimentação
        digitalWrite(LedPin,HIGH); // Led acesso
        dispara_sirene();
      }
      else 
      {
        digitalWrite(LedPin,LOW); // led apagado
      }
  }
  
  
  delay (1000);
}

void dispara_sirene() {
  digitalWrite(SirPin, HIGH); // sirene acesso
  Serial.println("Sirene ativa");
  delay (120000);//2min
  digitalWrite(SirPin, LOW); // sirene apagado
  Serial.println("Sirene desativada");
}
