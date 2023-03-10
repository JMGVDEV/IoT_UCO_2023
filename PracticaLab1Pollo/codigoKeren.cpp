#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);

const int button1Pin = D1;
const int button2Pin = D2;

void setup() {
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  WiFi.begin("your-ssid", "your-password");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("WiFi connected!");

  server.on("/button-state", handleButtonState);

  server.begin();
  Serial.println("Web server started!");
}

void loop() {
  server.handleClient();
}

void handleButtonState() {
  bool button1State = digitalRead(button1Pin);
  bool button2State = digitalRead(button2Pin);

  String response = "{";
  response += "\"button1\": " + String(button1State);
  response += ", ";
  response += "\"button2\": " + String(button2State);
  response += "}";

  server.send(200, "application/json", response);
}
