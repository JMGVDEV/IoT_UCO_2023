#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

// Replace with your network credentials
const char* ssid = "HOGAR 2";
const char* password = "GATO182K";

// WebServer Instantiation
ESP8266WebServer server(80);

//Web Page Variable
String webPage = "";
int led = 5;
 
void handlePost(){
  String LedState;
  LedState = server.arg("LED");
  Serial.print("Argumentos Recibidos");
  Serial.print(LedState);
  if (LedState == "on")  {
      digitalWrite(led, HIGH);
  } else if (LedState == "off")  {
      digitalWrite(led, LOW); 
  }
  server.sendHeader("Location", "/");
  server.send(303);
}

void setup(void){

 //Build Basic Web Page using HTML
  webPage += "<html>";
  webPage +=    "<head>";
  webPage +=        "<title>Encender y Apagar Led</title>";
  webPage +=    "</head>";
  webPage +=    "<body>";
  webPage +=        "<h1>Encender y Apagar Led</h1>";
  webPage +=        "<div>";
  webPage +=            "<form method='POST' action='/'>";
  webPage +=                "<button id='on' name='LED' value='on'>ON</button>";
  webPage +=                "<button id='off' name='LED' value='off'>OFF</button>";
  webPage +=            "</form>";
  webPage +=        "</div>";
  webPage +=    "</body>";
  webPage += "</html>";
  delay(500);
  //Serial Comunnication and Wifi Connection kick off
  Serial.begin(115200);
  pinMode(led, OUTPUT); 
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  //Web Page handler on root "/" using .send() method from ESP8266WebServer class
  //server.send(200, "text/html", webPage);
  server.on("/", HTTP_POST, handlePost);
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
  
  //Start Web Server and notify via serial comm.
  server.begin();
  Serial.println("HTTP server started");
}

void loop(void){
  //Handle client requests to web Server using .handleClient() method from ESP8266WebServer class
  server.handleClient();
}
