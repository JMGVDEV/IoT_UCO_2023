#include <Arduino.h>
#include <iostream>
#include <ESP8266HTTPClient.h>
#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <ArduinoJson.h>

const char* ssid = "XXXXXXXxx";
const char* password = "XXXXXXXx";

const char * mqtt_server = "XXXXXx";//name of the mqtt broker
const char * MQTT_user = "X";//username to access to the broker
const char * MQTT_password = "XXXXXXXX";//password to access to the broker
 
const char* input = "/input_tz";
const char* output = "/publish_tz";
const char* alive = "/alive";
const char* StatusRequest = "/StatusRequest";
const char* Json = "/JsonStatus";



WiFiClient espClient; 
PubSubClient client(espClient); 
 

void wifi_setup(){ 
  WiFi.begin(ssid, password);
  Serial.print ("Connecting to AP");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
void reconnect() { 
  while (!client.connected()) {
    // Attempt to connect
    
    if (client.connect("ESP8266Client", MQTT_user, MQTT_password)) {
      Serial.println("Connected to MQTT broker");
      client.subscribe(input);
    } else {
      Serial.println("Failed with state ");
      Serial.print(client.state());
      Serial.println("Retrying...");
      delay(100);
    }
  }
}

void printing_format(const int day_of_week, const char* datetime){ 
    String day = "";
    switch (day_of_week)
    {
    case 1:
      day = "Lunes";
      break;
    case 2:
      day = "Martes";
      break;
    case 3:
      day = "Miércoles";
      break;
    case 4:
      day = "Jueves";
      break;
    case 5:
      day = "Viernes";
      break;
    case 6:
      day = "Sábado";
      break;
    case 0:
      day = "Domingo";
      break;
    default:
      break;
    }
    
    char dtyear[5]={0x00};
    for(int i=0;i<4;i++)
      dtyear[i]=(char)datetime[i];
    dtyear[4]=0x00;

    char dtmonth[1]={0x00};
    for(int i=0;i<1;i++)
      dtmonth[0]=(char)datetime[i+6];
    dtmonth[1] = 0x00;  

    String month = "";
    switch (int(dtmonth[0]))
    {
    case 49:
      month = "Enero";
      break;
    case 50:
      month = "Febrero";
      break;
    case 51:
      month = "Marzo";
      break;
    case 52:
      month = "Abril";
      break;
    case 53:
      month = "Mayo";
      break;
    case 54:
      month = "Junio";
      break;
    case 55:
      month = "Julio";
      break;
    default:
      break;
    }

    char dtday[5]={0x00};
    for(int i=0;i<2;i++)
      dtday[i]=(char)datetime[i+8];
    dtday[2]=0x00;       

    char dthour[6]={0x00};
    for(int i=0;i<5;i++)
      dthour[i]=(char)datetime[i+11];
    dthour[5]=0x00;

    reconnect();
    client.publish(Json, "Trama Json procesada :D"); 

    String publish_form = day;
    publish_form += ", ";
    publish_form += dtday;
    publish_form += " de ";
    publish_form += month;
    publish_form += " de ";
    publish_form += dtyear;
    publish_form += " -- ";
    publish_form += dthour;
    Serial.println(publish_form);

    reconnect();
    client.publish(output, publish_form.c_str());
       
}

void http_get_API(byte* payload, unsigned int length){
  // Make a GET request to the World Time API
  HTTPClient http;

  char message[5]={0x00};
  for(int i=0;i<length;i++)
    message[i]=(char)payload[i];
  message[length]=0x00;

  String apiUrl = "http://worldtimeapi.org/api/timezone/";
  apiUrl += String(message);

  if(http.begin(espClient, apiUrl)){

    int httpCode = http.GET(); 
    if (httpCode > 0 || httpCode == HTTP_CODE_OK) { 
      String response = http.getString(); 

      reconnect();
      client.publish(StatusRequest, "HTTP Response Sucessful"); 
      Serial.println("Response Sucessful OK");
      
      // Parse the JSON response (AGREGAR PUBLISH STATUSREQUEST)
      DynamicJsonDocument doc(1024); 
      deserializeJson(doc, response);

      

      const char* datetime = doc["datetime"];
      const int day_of_week = doc["day_of_week"];
    
      printing_format(day_of_week, datetime);
      
      
    }else {
      const String error = http.errorToString(httpCode);
      Serial.println("Error making API call");
      Serial.printf("[HTTP] GET... failed, error: %s", error.c_str());
      Serial.println("");
      String error_mqtt = "HTTP Response Failed";
      error_mqtt += error;
      reconnect();
      client.publish(StatusRequest, error_mqtt.c_str());

    }
    
  }
  http.end();
}

void CB_input(char* topic, byte* payload, unsigned int length) { 
  Serial.print("Incomming message from: ");
  Serial.println(topic);
  http_get_API(payload,length);
  Serial.print("API DONE: ");
}


void setup() {
  Serial.begin(115200); 
  wifi_setup();

  client.setServer(mqtt_server, 1883); 
  client.setCallback(CB_input);
  
  reconnect();

  client.subscribe(input);
  client.publish(alive, "Mosquitto Broker Alive");
}

void loop() {
  reconnect();
  client.loop();

}