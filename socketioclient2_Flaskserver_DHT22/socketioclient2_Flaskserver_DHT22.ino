/*
 * .ino
 *
 *  Created on: 2023-01-20
 *
 */

#include <Arduino.h>

#include <ESP8266WiFi.h>

#include <ArduinoJson.h>

#include <WebSocketsClient.h>
#include <SocketIOclient.h>

#include <Hash.h>
#include <SoftwareSerial.h> 
SocketIOclient socketIO;


const char* ssid = "";//WiFi network name  
const char* psswd ="";//WiFi password   
#define USE_SERIAL Serial
 
struct string_data {
String inputString; 
String output;
};

struct DHT {
float temp;
float hum;
} ;
//function for handling socketio messages
void socketIOEvent(socketIOmessageType_t type, uint8_t * payload, size_t length) {
    switch(type) {
        case sIOtype_DISCONNECT:
            USE_SERIAL.printf("[IOc] Disconnected!\n");
            break;
        case sIOtype_CONNECT:
            USE_SERIAL.printf("[IOc] Connected to url: %s\n", payload);

            // join default namespace (no auto join in Socket.IO V3)
            socketIO.send(sIOtype_CONNECT, "/");
            break;
        case sIOtype_EVENT:
            USE_SERIAL.printf("[IOc] get event: %s\n", payload);
            break;
        case sIOtype_ERROR:
            USE_SERIAL.printf("[IOc] get error: %u\n", length);
            hexdump(payload, length);
          break;
      
    }
}
// init struct
struct string_data str = {"",""};
struct DHT dht22={0,0};

void setup() {

    USE_SERIAL.begin(9600); //115200 
 
 str.inputString.reserve(15);


    WiFi.begin(ssid,psswd); 
while(WiFi.status() != WL_CONNECTED){
  delay(500); 
  Serial.print(".");
}
Serial.println(""); 
Serial.print("connected to ");Serial.println(ssid); 
Serial.print("IP adress is " ); Serial.println( WiFi.localIP()); 

    // server address, port and URL
    socketIO.begin("_SERVER_IP_ADRESS", 5000);

    // event handler
    socketIO.onEvent(socketIOEvent);
}

unsigned long messageTimestamp = 0;



     
bool stringComplete = false; 
void loop() {


    socketIO.loop();

    uint64_t now = millis();

if(now - messageTimestamp > 2000) {
        messageTimestamp = now;



   if (stringComplete) {

// json doc for recieving incoming data from STM32
// the data is in json formay that's why we need to deserialize 	
   StaticJsonDocument<190> doc;
   DeserializationError err = deserializeJson(doc,str.inputString); 

   dht22.temp=doc[String("temp")];
   dht22.hum=doc[String("hum")]; 
/*
Serial.print(dht22.hum);
Serial.print(" -|(.)|- ");  
Serial.println(dht22.temp);  
*/

//this doc is for sending the data to the flask server 
// the data [temp, hum] should be formatted to json,  
    StaticJsonDocument<190> doc2;
    doc2.add("message");
    JsonObject send = doc2.createNestedObject();
    send["temp"]= dht22.temp ;
    send["hum"]=dht22.hum; 
    serializeJson(doc2,str.output); 
    
    socketIO.sendEVENT(str.output);
    // Print JSON for debugging 
    Serial.println(str.output); 
    str.inputString = "";
    str.output=""; 
    stringComplete = false;
    }

}
}


void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    str.inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
