

#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>

TinyGPSPlus gps;    
SoftwareSerial gps_ss(7, 6);   
SoftwareSerial GSM_UART(8, 9);   

#define sw 2  

void setup(){     
   pinMode(sw, INPUT);   
   GSM_UART.begin(9600);
   gps_ss.begin(9600);
}
 
void loop(){

  if (gps_ss.available()){
    if (gps.encode(gps_ss.read()))
      if (gps.location.isValid()){
         Serial.print(F("Location: ")); 
         Serial.print(gps.location.lat(), 6);
         Serial.print(F(","));
         Serial.println(gps.location.lng(), 6);
         return;        
      }
      else
      {
      Serial.println(F("NO GPS"));
      delay(25);
    }

      if(digitalRead(sw) == 0){ 
          Send_SMS();
      }
  }
}

void Send_SMS(){
     GSM_UART.println("AT+CMGS=+9180xxxxxx79");
     delay(1000);
     GSM_UART.print("This SMS Send BY GPS-SMS Based Tracking SYS");
     String data = "LOC:http://maps.google.com/?q=" + String(gps.location.lat(), 6) + "," + String(gps.location.lng(), 6);
     GSM_UART.println(data);
     delay(1000);
     GSM_UART.println((char)27);
     delay(5000);
}
