#include <GSM.h>
#include <LiquidCrystal.h>
#include <DHT.h>
#define DHTTYPE DHT11
#define humtemp 6
DHT dht(humtemp, DHTTYPE);

//Variables//
int moisture_sensorPin = A0;
float analog;
float voltage;
int motorPin=7;
float temp;
float hum;
float moisturevalue;
float avg_temp=25;
float avg_hum=45;
int Start=9;
int Stop=8;

const int RS=12, E=11, D4=5, D5=4, D6=3, D7=2;
LiquidCrystal lcd(RS, E, D4, D5, D6, D7);

const float avg_moisture =0.875;


void setup()
{  
   pinMode(Start,INPUT);
   pinMode(Stop,INPUT);
   Serial.begin(9600);
   dht.begin();
   pinMode(moisture_sensorPin,INPUT);
  
   
   lcd.begin(16,2);
   lcd.print("WELCOME");
   delay(1000);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("TO EVERGREEN");
   delay(1000);
   lcd.clear();
   lcd.setCursor(0,0);
   lcd.print("FARMS");
   delay(1000);
   lcd.clear();
   lcd.setCursor(0,0);
   delay(1000);
   lcd.print("SYSTEM READY");
  
   pinMode(moisture_sensorPin,INPUT);
   pinMode(motorPin,OUTPUT);
  
}


void loop() 
{ 
  //Moisture Sensor //
 analog =analogRead(moisture_sensorPin);
 voltage= (analog/1023.0)*5;
 moisturevalue = (voltage/2);
  
 
 //Temperature and Humidity//
 temp = dht.readTemperature();
 hum  = dht.readHumidity();

 Serial.print("TEMPERATURE="); 
 Serial.print(temp);
 Serial.println(" Degrees_celsius");
 Serial.println("");
 delay(500);

 Serial.print("HUMIDITY=");
 Serial.print(hum);
 Serial.println("Percent");
 Serial.println("");
 delay(500);

 Serial.print("SOIL_MOISTURE=");
 Serial.print(moisturevalue);
 Serial.print("Volts");
 Serial.println("");

  
while((moisturevalue > avg_moisture)&&(temp < avg_temp)&&(hum < avg_hum)) { 
     
     if(digitalRead(Stop)==HIGH) {  
      digitalWrite(motorPin,LOW);
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("MOTOR OFF");
      delay(100);  
      SendMessage();
      }
     
     else {
      digitalWrite(motorPin,HIGH);
      lcd.setCursor(0,0);
      lcd.clear();
      lcd.print("MOTOR ON");
     SendMessage();
     }
    
    }

    while(!(moisturevalue > avg_moisture)&&(temp < avg_temp)&&(hum < avg_hum)){
      SendMessageHIGH();
      }
}  
        
     void SendMessage()
    {
     Serial.println("AT+CMGF=1");
     delay(50);
     Serial.println("AT+CMGS=+233203693218""\r");
     delay(50);
    
     Serial.println("ALL CONDITIONS ARE SUITABLE FOR IRRIGATION");
     Serial.println("");
     Serial.println("MOTOR IS ON");
     
     Serial.print("TEMPERATURE="); 
     Serial.print(temp);
     Serial.println(" Degrees_celsius");
     Serial.println("");
     delay(500);

     Serial.print("HUMIDITY=");
     Serial.print(hum);
     Serial.println(" Percent");
     Serial.println("");
     delay(500);

     Serial.print("SOIL_MOISTURE=");
     Serial.print(moisturevalue);
     Serial.print(" Volts");
     Serial.println("");
     delay(50);
     Serial.println((char)26);
     delay(50);
    }
    
     void SendMessageHIGH()
    {
     Serial.println("AT+CMGF=1");
     delay(50);
     Serial.println("AT+CMGS=+233203693218""\r");
     delay(50);
     
     Serial.println("A CONDITION IS UNSUITABLE FOR IRRIGATION");
     Serial.println("");
     Serial.println("MOTOR OFF");
     delay(50);
     
     Serial.print("TEMPERATURE="); 
     Serial.print(temp);
     Serial.println(" Degrees_celsius");
     Serial.println("");
     delay(500);

     Serial.print("HUMIDITY=");
     Serial.print(hum);
     Serial.println(" Percent");
     Serial.println("");
     delay(500);

     Serial.print("SOIL_MOISTURE=");
     Serial.print(moisturevalue);
     Serial.print(" Volts");
     Serial.println("");
     Serial.println((char)26);
     delay(50);

    }
 
     void DialCall()
     {  
       Serial.println("ATD+233203693218;");
       delay(50);
     }

   
     



