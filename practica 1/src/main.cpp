#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
// incluyendo las librerías necesarias para el código
// ==================================================
// Replace with your network credentials
const char* ssid = "Galaxy_mzm";
const char* password = "barriomaderos";

// WebServer Instantiation
ESP8266WebServer server(80);

int ledUno = D1;
int ledDos = D2;


void handleRoot() {
  // Muestra una página HTML básica con un botón para encender y apagar un LED
  String html = "<html><body>";
  html += "<h1 class=titulo>Automatizacion Encendido</h1>";

  html += "<div class=caja>";
  html += "<p><a href=\"/led/on1\"><button class=button0>EncenderLed1</button></a></p>";  // (html += para concatenar cadenas de texto)
  html += "<p><a href=\"/led/off1\"><button class=button1>ApagarLed1</button></a></p>";
  html += "<p><a href=\"/led/on2\"><button class=button2>EncenderLed2</button></a></p>";
  html += "<p><a href=\"/led/off2\"><button class=button3>ApagarLed2</button></a></p>";
  html += "</div>";
  html += "<style>";
  html += "body {";
  html += "background-color: rgb(191, 221, 237)";
  html +=  "}";

  html += ".titulo {";
  html += "text-align: center;";
  html += "font-family: arial black;";
  html += "font-weight: bold;";
  html += "font-size: 30px;";
  html += "text-shadow: -1px 0 #000, 0 1px #000, 1px #000, 0 -1px #000;";
  html += "color:#0ba437;";
  html += "}";

  html += ".caja {";
  html += "background-color:rgb(148, 184, 245) ;";
  html += "width: 340px;";
  html += "margin: auto;";
  html += "text-align: center;";
  html += "border:rgb(148, 178, 235) 5px outset;";
  html += "border-radius: 5px;";
  html += "}";

  html += ".button0 {";
  html += "background-color:rgb(58, 208, 58);";
  html += "color:white;";
  html += "width: 200px;";
  html += "height: 50;";
  html += "font-family:fantasy;";
  html += "font-size: 30px;";
  html += "border-radius: 5px;";
  html += "transition-duration: 0.4s;";
  html += "}";

  html += ".button0:hover {";
  html += "background-color: #226e25; /* Green */";
  html += "color: white;";
  html += "}";

  html += ".button1 {";
  html += "background-color:rgb(204, 74, 74);";
  html += "color:white;";
  html += "width: 200px;";
  html += "height: 50;";
  html += "font-family:fantasy;";
  html += "font-size: 30px;";
  html += "border-radius: 5px;";
  html += "transition-duration: 0.4s;";
  html += "}";

  html += ".button1:hover {";
  html += "background-color: #95291b; /* Green */";
  html += "color: white;";
  html += "}";

html += ".button2 {";
  html += "background-color:rgb(58, 208, 58);";
  html += "color:white;";
  html += "width: 200px;";
  html += "height: 50;";
  html += "font-family:fantasy;";
  html += "font-size: 30px;";
  html += "border-radius: 5px;";
  html += "transition-duration: 0.4s;";
  html += "}";
 
  html += ".button2:hover {";
  html += "background-color: #226e25; /* Green */";
  html += "color: white;";
  html += "}";

  html += ".button3 {";
  html += "background-color:rgb(204, 74, 74);";
  html += "color:white;";
  html += "width: 200px;";
  html += "height: 50;";
  html += "font-family:fantasy;";
  html += "font-size: 30px;";
  html += "border-radius: 5px;";
  html += "transition-duration: 0.4s;";
  html += "}";

  html += ".button3:hover {";
  html += "background-color: #95291b; /* Green */";
  html += "color: white;";
  html += "}";

  html += "</style>";
  html += "</body></html>";
  server.send(200, "text/html", html);     // funcion que se utiliza para enviar una respuesta HTTP al cliente que realiza una solicitud al servidor web
}

void encenderLedUno() {
  // Enciende el LED
  digitalWrite(ledUno, HIGH);
  server.send(200, "text/plain", "LED encendido");  //sintaxis server.send(client,data,context)
}

void apagarLedUno() {
  // Apaga el LED
  digitalWrite(ledUno, LOW);
  server.send(200, "text/plain", "LED apagado");
}

void encenderLedDos() {
  // Enciende el LED
  digitalWrite(ledDos, HIGH);
  server.send(200, "text/plain", "LED encendido");  //sintaxis server.send(client,data,context)
}

void apagarLedDos() {
  // Apaga el LED
  digitalWrite(ledDos, LOW);
  server.send(200, "text/plain", "LED apagado");
}

void setup() {

  pinMode(ledUno, OUTPUT);

  // Configura las rutas del servidor web
  server.on("/", handleRoot);
  server.on("/led/on1", encenderLedUno);
  server.on("/led/off1", apagarLedUno);

  pinMode(ledDos, OUTPUT);

  // Configura las rutas del servidor web
  server.on("/", handleRoot);
  server.on("/led/on2", encenderLedDos);
  server.on("/led/off2", apagarLedDos);

  // Inicia el servidor
  server.begin();
  Serial.println("Servidor iniciado");
  //Serial Comunnication and Wifi Connection kick off
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  Serial.println(""); 

  // Inicializa la conexión WiFi
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

//Fragmento que ejecuta el server
//================================================================================================
   //Handle client requests to web Server using .handleClient() method from ESP8266WebServer class
  server.handleClient();
//================================================================================================
}

