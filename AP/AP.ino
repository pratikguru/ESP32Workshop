#include <WiFi.h>
#include <WiFiMulti.h>

const char* ssid;
const char* password;
WiFiServer server(4242);
WiFiMulti WiFiMulti;


const char* clientList = "10.0.0.11";

void setWiFi(const char* ssid, const char* password);
IPAddress local_IP(10, 0, 0, 1);
IPAddress gateway(10, 0, 0, 1);
IPAddress subnet(255, 255, 255, 0);
long long timer;

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n");
  setWiFi("cthings.co", "lawl123456");
}


void setWiFi(const char* Name, const char* Password)
{
  ssid      = Name;
  password  = Password;
  if (! WiFi.softAPConfig(local_IP, gateway, subnet)) {
    Serial.println("Allocation Error");
  }
  while (!WiFi.softAP(ssid, password)) {
    Serial.print(".");
    delay(200);
  }
  Serial.println("WIFI < " + String(ssid) + " > ... Started");
  Serial.println(WiFi.softAPIP());
  server.begin();
  Serial.println("Server Started");

}

void loop() {

  if ((long long)millis() - (long long)timer >= 1500) {
    Serial.print("Station connected: ");
    Serial.println(WiFi.softAPgetStationNum());
    timer = millis();
  
}
}


  





