#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>


// incluyendo las librerías necesarias para el código
// ==================================================
// Replace with your network credentials
const char* ssid = ":p:p:p";
const char* password = ":D:D:D:D";

// WebServer Instantiation
ESP8266WebServer server(80);

void handleRoot(){
  //Muestra una página HTML básica con un botón para encender y apagar un LED
  String html = "<html><head>";
  html += "<title>IoT Practice 1</title>";
  html += "<style>button {";
  html += "background-color: #931616;";
  html += "border: none;";
  html += "color: white;";
  html += "padding: 15px 32px;";
  html += "text-align: center;";
  html += "text-decoration: none;";
  html += "display: inline-block;";
  html += "font-size: 16px;";
  html += "margin: 4px 2px;";
  html += "cursor: pointer;";
  html += "}";
  html += "h1 {";
  html += "font-family: Arial, sans-serif;";
  html += "font-size: 24px;";
  html += "font-weight: bold;";
  html += "color: #333;";
  html += "text-align: center;";
  html += "margin-top: 20px;";
  html += "}";
  html += "</style>";
  html += "<center>";
  html += "</head><body>";
  html += "<h1>2 Leds Control</h1>";
  html += "<p><a href = \"/6c65642f6f6e\"><button>Encender Led 1</button></a></p>";
  html += "<p><a href=\"/6c65642f6f6666\"><button>Apagar Led 1</button></a></p>";
  html += "<p><a href=\"/6c6564322f6f6e\"><button>Encender Led 2</button></a></p>";
  html += "<p><a href=\"/6c6564322f6f6666\"><button>Apagar Led 2</button></a></p>";
  html += "</body></html>"; 
  server.send(200, "text/html", html);
}

void handleLed1On() {
  //Enciende el LED
  digitalWrite(D1, HIGH);
  server.send(200, "text/plain", "LED 1 ON");
}

void handleLed1Off() {
  // Apaga el LED
  digitalWrite(D1, LOW);
  server.send(200, "text/plain", "LED 1 OFF");
}
void handleLed2On() {
  // Enciende el LED
  digitalWrite(D2, HIGH);
  server.send(200, "text/plain", "LED 2 ON");
}

void handleLed2Off() {
  // Apaga el LED
  digitalWrite(D2, LOW);
  server.send(200, "text/plain", "LED 2 OFF");
}

void setup() {

  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);

  //Web Server Routs config.
  server.on("/", handleRoot);
  server.on("/6c65642f6f6e", handleLed1On);  //led 1 on 
  server.on("/6c65642f6f6666", handleLed1Off);//led 1 off
  server.on("/6c6564322f6f6e", handleLed2On);  //led 2 on 
  server.on("/6c6564322f6f6666", handleLed2Off);//led 2 off

  //Server Starts
  server.begin();
  Serial.println("Server Started");

  //Serial Comunnication and Wifi Connection 
  Serial.begin(9600);
  WiFi.begin(ssid, password);

  //Wifi Conection Start
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());

}

void loop() {
//Handle client requests to web Server method from ESP8266WebServer class
  server.handleClient();
}
