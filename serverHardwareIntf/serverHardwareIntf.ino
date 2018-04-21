#include <WiFi.h>

const char* ssid     = "Vent";
const char* password = "pizzasalami";

WiFiServer server(80);
int relay = 32;

void setup(){
  Serial.begin(115200);
  delay(10);
  Serial.println("\n\n");
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  pinMode(relay, OUTPUT);
  while(WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.println(".");
  }

  Serial.println("\n\n");
  Serial.println("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if(client) {
    while(client.connected()) {
      int byteSize = 0;
      uint8_t payload[256];
      if(byteSize = client.available()) {
        Serial.print(client.remoteIP());
        Serial.print("  Sent: ");
        Serial.print(byteSize);
        Serial.print (" bytes.");
        Serial.println();

        uint8_t buffer_[3];
        client.read(buffer_, 2);

        Serial.println("Incoming: " + String(buffer_[0]));
        if((uint8_t)buffer_[0] == '1') {
          Serial.println("Lights on");
          client.println("Lights turned on");
          digitalWrite(relay, 1);
        }
        else if((uint8_t)buffer_[0] == '0') {
          Serial.println("Lights off");
          client.println("Lights turned off");
          digitalWrite(relay, 0);
        }
        else  {
          Serial.println("Unrecog command");
          client.println("unrecog command");
        }
        
      }
    }
  }
}

