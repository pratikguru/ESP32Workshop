#include <WiFi.h>
#include <WiFiMulti.h>
const char* ssid;
const char* password;
WiFiMulti WiFiMulti;

void setup() {
  Serial.begin(115200);
  Serial.println("\n\n");
  connectWiFi("Vent", "pizzasalami");
}

void connectWiFi(const char* ssid_, const char* password_) {
  ssid = ssid_;
  password = password_;

//  WiFiMulti.addAP(ssid, password);
//  WiFi.mode(WIFI_STA);
//
//  Serial.println("Connecting to: " + String(ssid));
//  while(WiFiMulti.run() != WL_CONNECTED) {
//    Serial.print(".");
//    delay(100);
//  }
//  Serial.println("");
//  Serial.println("WiFi Connected");
//  Serial.print("IP Address: ");;
//  Serial.println(WiFi.localIP());
//  delay(10);

WiFi.begin(ssid, password);
Serial.println("Connecting: " + String(ssid));
while(WiFi.status() != WL_CONNECTED) {
  Serial.print(".");
  delay(100);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  delay(10);
  
}

void loop() {
  
}

