#include <SPI.h>
#include <Wire.h>
#include <EEPROM.h>
String readString;

 int relay_1 = 2;
 int relay_2 = 3;
 int relay_3 = 9;
 int relay_4 = 10;


const int mswitch_1 = 5;
const int mswitch_2 = 6;
const int mswitch_3 = 7;
const int mswitch_4 = 8;



int toggleState_1 = 0; 
int toggleState_2 = 0; 
int toggleState_3 = 0; 
int toggleState_4 = 0;

void setup() {
 
  Serial.begin(9600);
  
  pinMode(relay_1, OUTPUT);
  pinMode(relay_2, OUTPUT);
  pinMode(relay_3, OUTPUT);
  pinMode(relay_4, OUTPUT);

  pinMode(mswitch_1, INPUT);
  pinMode(mswitch_2, INPUT);
  pinMode(mswitch_3, INPUT);
  pinMode(mswitch_4, INPUT);

  eepromcheckstate();
}

void relayOnOff(int relay){

switch(relay){
      case 1: 
             if(toggleState_1 == 0){
              digitalWrite(relay_1, HIGH); // turn on relay 1
              EEPROM.update(0,HIGH);
              toggleState_1 = 1;
              }
             else{
              digitalWrite(relay_1, LOW); // turn off relay 1
              EEPROM.update(0,LOW);
              toggleState_1 = 0;
              }
             delay(100);
      break;
      case 2: 
             if(toggleState_2 == 0){
              digitalWrite(relay_2, HIGH); // turn on relay 2
              EEPROM.update(1,HIGH);
              toggleState_2 = 1;
              }
             else{
              digitalWrite(relay_2, LOW); // turn off relay 2
              EEPROM.update(1,LOW);
              toggleState_2 = 0;
              }
             delay(100);
      break;
      case 3: 
             if(toggleState_3 == 0){
              digitalWrite(relay_3, HIGH); // turn on relay 3
              EEPROM.update(2,HIGH);
              toggleState_3 = 1;
              }else{
              digitalWrite(relay_3, LOW); // turn off relay 3
              EEPROM.update(2,LOW);
              toggleState_3 = 0;
              }
             delay(100);
      break;
      case 4: 
             if(toggleState_4 == 0){
              digitalWrite(relay_4, HIGH); // turn on relay 4
              EEPROM.update(3,HIGH);
              toggleState_4 = 1;
              }
             else{
              digitalWrite(relay_4, LOW); // turn off relay 4
              EEPROM.update(3,LOW);
              toggleState_4 = 0;
              }
             delay(100);
      break;
           
      default : break;      
      }
  
}

void eepromcheckstate()
{

  toggleState_1 = EEPROM.read(0);
  if(toggleState_1 == HIGH) {
    digitalWrite(relay_1, HIGH);
   }   
   if(toggleState_1 == LOW) {
    digitalWrite(relay_1, LOW);
   }   
   
  toggleState_2 = EEPROM.read(1); 
  if(toggleState_2 == HIGH) {
    digitalWrite(relay_2, HIGH);
   }   
   if(toggleState_2 == LOW) {
    digitalWrite(relay_2, LOW);
   }
     
  toggleState_3 = EEPROM.read(2);
  if(toggleState_3 == HIGH) {
    digitalWrite(relay_3, HIGH);
   }   
   if(toggleState_3 == LOW) {
    digitalWrite(relay_3, LOW);
   }

  toggleState_4 = EEPROM.read(3);
  if(toggleState_4 == HIGH) {
    digitalWrite(relay_4, HIGH);
   }   
   if(toggleState_4 == LOW) {
    digitalWrite(relay_4, LOW);
   }

}


void loop() {     
     
    if (digitalRead(mswitch_1) == LOW){
      delay(200);
      relayOnOff(1);      
    }
    else if (digitalRead(mswitch_2) == LOW){
      delay(200);
      relayOnOff(2);
    }
    else if (digitalRead(mswitch_3) == LOW){
      delay(200);
      relayOnOff(3);
    }
    else if (digitalRead(mswitch_4) == LOW){
      delay(200);
      relayOnOff(4);
    }

      while(Serial.available())    //Check if there are available bytes to read
  {
    delay(10);                 //Delay to make it stable
    char c = Serial.read();    //Conduct a serial read
    if (c == '#'){
      break;                   //Stop the loop once # is detected after a word
    }
    readString += c;                //Means readString = readString + c
  }
    if (readString.length() >0)
    {
      Serial.println(readString);
                  
      if(readString == "RELAY1"){   
        relayOnOff(1);
      }
      else if(readString == "RELAY2"){   
        relayOnOff(2);
      }
      else if(readString == "RELAY3"){   
        relayOnOff(3);
      }
      else if(readString == "RELAY4"){   
        relayOnOff(4);
      }
      readString="";
    }
  }
