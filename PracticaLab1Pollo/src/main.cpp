/* 
Estudiante: Angel Daniel Gaviria Rendón
            ingeniería electrónica

Incluyendo las librerías necesarias para el código
 ==============================================================================
*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
//Estos campos se reemplazan con las credenciales de red
//=============================================================================
const char* ssid = "xxxx";
const char* password = "xxxxx";
//Asignando un alias a los pines que se utilizan
//=============================================================================
int LEDR = D3;
int LEDB = D4;
String webPage = "";

// instanciación del servidor Web 80 es una valor por defecto
//==============================================================================
ESP8266WebServer server(80);
void prender()
{
  // Enciende el LED
  digitalWrite(LEDR, HIGH);
  digitalWrite(LEDB, LOW);
  server.send(200, "text/plain", "LED Rojo encendido, led azul apagado");
}
void apagar()
{
  // Enciende el LED
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDB, HIGH);
  server.send(200, "text/plain", "LED rojo apagado, led azul encendido");
}

 
void setup(void){
  pinMode(LEDR,OUTPUT);
  pinMode(LEDB,OUTPUT);
  //Build Basic Web Page using HTML
  webPage += "<h1>AMAZING WEB SERVER</h1>";
  webPage += "<p><marquee>######.....IoT Gelan.....######</marquee></p>";
  webPage += "<p><a href=\"/led/on\"><button>Encender Rojo y apagar azul</button></a></p>";
  webPage += "<p><a href=\"/led/off\"><button>Apagar Rojo y encender azul</button></a></p>";
  delay(1000);

  //Serial Comunnication and Wifi Connection kick off
  Serial.begin(9600);
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
  server.on("/", [](){
    server.send(200, "text/html", webPage);
  });
   //Start Web Server and notify via serial comm.
  server.begin();
  Serial.println("HTTP server started");

  server.on("/led/on", prender);
  server.on("/led/off", apagar);

  }

void loop() {

//Fragmento que ejecuta el server
//================================================================================================
   //Handle client requests to web Server using .handleClient() method from ESP8266WebServer class
  server.handleClient();
//================================================================================================

}
