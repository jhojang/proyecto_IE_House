#include <ESP8266WiFi.h>
#include <AdafruitIO.h>
#include <Adafruit_MQTT.h>
#include <ArduinoHttpClient.h>



const char* ssid = ("NOMBRE_DE_RED");
const char* password = ("");

#include "AdafruitIO_WiFi.h"
AdafruitIO_WiFi io(IOUSUARIO, IOKEY, ssid, password);

int current = 0;
int last = 0;

int estado1;

// set up the 'command' feed
AdafruitIO_Feed *command = io.feed("luces");


String pin4State = "off";
String pin5State = "off";
String pin0State = "off";
String pin2State = "off";

const int output4 = 4;
const int output5 = 5;
const int output0 = 0;

String header;

WiFiServer server(80);

void setup() {
  Serial.begin(9600);

  pinMode(output4, OUTPUT);
  pinMode(output5, OUTPUT);
  pinMode(output0, OUTPUT);

  digitalWrite(output4, LOW);
  digitalWrite(output5, LOW);
  digitalWrite(output0, LOW);



  Serial.println("");
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
    }
  Serial.println("");
  Serial.println("Conectado a WiFi");
  Serial.println("Direccion IP:");
  Serial.println(WiFi.localIP());

  Serial.println("Conectando a Adafruit IO");
  io.connect();

  command->onMessage(handleMessage);

  // wait for a connection
  while(io.status() != AIO_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println();
  Serial.println(io.statusText());

  server.begin();
}


void loop() {

  io.run();

  WiFiClient client = server.available();

  if(client){
    String currentLine = "";
    while (client.connected()){
      if (client.available()){
        char c = client.read();
        Serial.write(c);
        header += c;

        if (c == '\n'){
          if (currentLine.length() == 0){

            client.println("HTTP/1.1 200 OK");
            client.println("conmtent-type:text/html");
            client.println("Connection: close");
            client.println();

            if (header.indexOf("GET /4/on") >=0 ){
              Serial.println("GPIO 4 ON");
              pin4State = "on";
              digitalWrite(output4, HIGH);
            } else if (header.indexOf("GET /4/off") >=0 ){
              Serial.println("GPIO 4 OFF");
              pin4State = "off";
              digitalWrite(output4, LOW);  
            } else if (header.indexOf("GET /5/on") >=0 ){
              Serial.println("GPIO 5 ON");
              pin5State = "on";
              digitalWrite(output5, HIGH);
            } else if (header.indexOf("GET /5/off") >=0 ){
              Serial.println("GPIO 5 OFF");
              pin5State = "off";
              digitalWrite(output5, LOW);
            }  else if (header.indexOf("GET /0/on") >=0 ){
              Serial.println("GPIO 0 ON");
              pin0State = "on";
              digitalWrite(output0, HIGH);
            } else if (header.indexOf("GET /0/off") >=0 ){
              Serial.println("GPIO 0 OFF");
              pin0State = "off";
              digitalWrite(output0, LOW);
            } else if (header.indexOf("GET /2/on") >=0 ){
              pin2State = "on";
              Serial.println("GPIO 4 ON");
              pin4State = "on";
              digitalWrite(output4, HIGH);
              Serial.println("GPIO 5 ON");
              pin5State = "on";
              digitalWrite(output5, HIGH);
              Serial.println("GPIO 0 ON");
              pin0State = "on";
              digitalWrite(output0, HIGH);
            } else if (header.indexOf("GET /2/off") >=0 ){
              pin2State = "off";
              Serial.println("GPIO 4 OFF");
              pin4State = "off";
              digitalWrite(output4, LOW);
              Serial.println("GPIO 5 OFF");
              pin5State = "off";
              digitalWrite(output5, LOW);
              Serial.println("GPIO 0 OFF");
              pin0State = "off";
              digitalWrite(output0, LOW);
            } 
            if ((pin4State == "off") || (pin5State == "off") || (pin0State == "off")){
              pin2State = "off";
            } else if ((pin4State == "on") && (pin5State == "on") && (pin0State == "on")){
              pin2State = "on";
            }

            
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\" charset=\"utf-8\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html {text-align: center; font-family: Helvetica; display: inline-block;}");
            client.println(".button{ border: 0px; margin: 0px 20px 0px 20px;}");
            client.println("ul{list-style: none; text-align: center; border: 0;padding: 0;}");
            client.println("ul li{text-align: center; display: inline-block;}</style>");
            client.println("</head><body><h1>Servidor ESP8266</h1>");
            client.println("<div>");
            client.println("<ul>");

            if (pin4State == "off"){
              client.println("<li><p><a class=\"button\" href=\"/4/on\"><img src=\"https://i.imgur.com/qbR7c1U.png\" height=\"100px\" width=\"100px\"/></a></p></li>");
            } else {
              client.println("<li><p><a class=\"button\" href=\"/4/off\"><img src=\"https://i.imgur.com/g1a1w8r.png\" height=\"100px\" width=\"100px\"/></a></p></li>");
            }
            if (pin5State == "off"){
              client.println("<li<p><a class=\"button\" href=\"/5/on\"><img src=\"https://i.imgur.com/UGUVmYK.png\" height=\"100px\" width=\"100px\"/></a></p></li>");
            } else {
              client.println("<li<p><a class=\"button\" href=\"/5/off\"><img src=\"https://i.imgur.com/Y0ijpgN.png\" height=\"100px\" width=\"100px\"/></a></p></li>");
            }
            if (pin0State == "off"){
              client.println("<li<p><a class=\"button\" href=\"/0/on\"><img src=\"https://i.imgur.com/c4IeiP0.png\" height=\"100px\" width=\"100px\"/></a></p></li>");
            } else {
              client.println("<li<p><a class=\"button\" href=\"/0/off\"><img src=\"https://i.imgur.com/Rn2UQs9.png\" height=\"100px\" width=\"100px\"/></a></p></li>");
            }
            if (pin2State == "off"){
              client.println("<li<p><a class=\"button\" href=\"/2/on\"><img src=\"https://i.imgur.com/9jnPjds.png\" height=\"100px\" width=\"100px\"/></a></p></li>");
            } else {
              client.println("<li<p><a class=\"button\" href=\"/2/off\"><img src=\"https://i.imgur.com/gNwDEMA.png\" height=\"100px\" width=\"100px\"/></a></p></li>");
            }
            client.println("</ul>");
            client.println("</div>");
            
            client.println("</body>");
            client.println("</HTML>");


            Serial.println();
            break;
            
           } else {
            currentLine = "";
            }
         } else if (c != '\r'){
          currentLine += c;
          }
        }
      } 

      header = "";
      client.stop();
      Serial.println("Cliente descnectado.");
      Serial.println("");
    }


 if(Serial.available() > 0){
    estado1 = Serial.read();
    if (estado1 == '1'){
    Serial.println("GPIO 4 ON");
    pin4State = "on";
    digitalWrite(output4, HIGH);
    }
    if (estado1 == '2'){
    Serial.println("GPIO 4 OFF");
    pin4State = "off";
    digitalWrite(output4, LOW);
    } 
    if (estado1 == '3'){
    Serial.println("GPIO 5 ON");
    pin5State = "on";
    digitalWrite(output5, HIGH);
    }
    if (estado1 == '4'){
    Serial.println("GPIO 5 OFF");
    pin5State = "off";
    digitalWrite(output5, LOW);
    }
    if (estado1 == '5'){
    Serial.println("GPIO 0 ON");
    pin0State = "on";
    digitalWrite(output0, HIGH);
    }
    if (estado1 == '6'){
    Serial.println("GPIO 0 OFF");
    pin0State = "off";
    digitalWrite(output0, LOW);
    }
    if (estado1 == '7'){
    Serial.println("GPIO 4 ON");
    pin4State = "on";
    digitalWrite(output4, HIGH);

    Serial.println("GPIO 5 ON");
    pin5State = "on";
    digitalWrite(output5, HIGH);
    
    Serial.println("GPIO 0 ON");
    pin0State = "on";
    digitalWrite(output0, HIGH);
    }
    if (estado1 == '8'){
    Serial.println("GPIO 4 OFF");
    pin4State = "off";
    digitalWrite(output4, LOW);

    Serial.println("GPIO 5 OFF");
    pin5State = "off";
    digitalWrite(output5, LOW);
    
    Serial.println("GPIO 0 OFF");
    pin0State = "off";
    digitalWrite(output0, LOW);
    }
  }
}

void handleMessage(AdafruitIO_Data *data) {

  int comando = data->toInt();

  if (comando == 1){
    Serial.println("");
    Serial.print("Comando recibido");
    Serial.println("GPIO 4 ON");
    pin4State = "on";
    digitalWrite(output4, HIGH);     
  } else if (comando == 0){
    Serial.println("");
    Serial.print("Comando recibido");
    Serial.println("GPIO 4 OFF");
    pin4State = "off";
    digitalWrite(output4 , LOW);
  } else if (comando == 2){
    Serial.println("");
    Serial.print("Comando recibido");
    Serial.println("GPIO 5 ON");
    pin5State = "on";
    digitalWrite(output5, HIGH);     
  } else if (comando == 3){
    Serial.println("");
    Serial.print("Comando recibido");
    Serial.println("GPIO 5 OFF");
    pin5State = "off";
    digitalWrite(output5 , LOW);
  } else if (comando == 4){
    Serial.println("");
    Serial.print("Comando recibido");
    Serial.println("GPIO 0 ON");
    pin0State = "on";
    digitalWrite(output0, HIGH);     
  } else if (comando == 5){
    Serial.println("");
    Serial.print("Comando recibido");
    Serial.println("GPIO 0 OFF");
    pin0State = "off";
    digitalWrite(output0 , LOW);
  } else if (comando == 6){ 
    Serial.print("Comando recibido");
    Serial.println("");
    Serial.println("GPIO 4 ON");
    Serial.println("GPIO 5 ON");
    Serial.println("GPIO 0 ON");
    pin4State = "on";
    pin5State = "on";
    pin0State = "on";
    digitalWrite(output4, HIGH);
    digitalWrite(output5, HIGH);
    digitalWrite(output0, HIGH);   
  } else if (comando == 7){
    Serial.print("Comando recibido");
    Serial.println("");
    Serial.println("GPIO 4 OFF");
    Serial.println("GPIO 5 OFF");
    Serial.println("GPIO 0 OFF");
    pin4State = "off";
    pin5State = "off";
    pin0State = "off";
    digitalWrite(output4, LOW);
    digitalWrite(output5, LOW);
    digitalWrite(output0, LOW); 
  }

}