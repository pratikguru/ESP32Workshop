#include <WiFi.h>
const char* ssid;
const char* password;
WiFiServer server(80);
#include <Adafruit_NeoPixel.h>
#define PIN            19
#define NUMPIXELS      84
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 500;
IPAddress local_IP(192, 168, 2, 115);
IPAddress gateway(192, 168, 31, 1);
IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8); //optional
IPAddress secondaryDNS(8, 8, 4, 4); //optional


void setup() {
  Serial.begin(115200);
  Serial.println("\n\n");
  connectWiFi("Vent", "pizzasalami");
  pixels.begin();
  for (int i = 0; i < NUMPIXELS; i++) {
          // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(0,0,255)); 
          pixels.show();
          
        }
}


void connectWiFi(const char* ssid_, const char* password_)
{
  Serial.println();
  Serial.println();
  ssid = ssid_;
  password = password_; 
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("STA Failed to configure");
  }
  
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  
}


void loop() {
  WiFiClient client = server.available();
  if (client) {
    while (client.available()) {
      int byteSize = 0;
      uint8_t payload[256];
      if (byteSize = client.available()) {
        Serial.print(client.remoteIP());
        Serial.print(" Sent: ");
        Serial.print(byteSize);
        Serial.println( "bytes.");
        client.readBytes(payload, 3);
        for(int i = 0; i < byteSize; i++) {
          Serial.print(payload[i]);
        }
        Serial.println("\n\n");
        for (int i = 0; i < NUMPIXELS; i++) {
          // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(payload[0], payload[1], payload[2])); 
          pixels.show();
          
        }
        client.stop();
      }
    }
  }
}

