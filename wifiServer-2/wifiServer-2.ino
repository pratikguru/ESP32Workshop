
#include <WiFi.h>

const char* ssid;
const char* password;


WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println();
  setWiFi("Vent", "pizzasalami");
}

void setWiFi(const char* ssid_, const char* password_) {
  ssid = ssid_;
  password = password_;
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }
  Serial.println("\n\n");
  Serial.println("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}


int value = 0;
void loop() {
  WiFiClient client = server.available();   // listen for incoming clients
  if (client) {
    while (client.connected()) {
      int byteSize = 0;
      char dataPacket[256];
      if (byteSize = client.available()) {
        Serial.print(client.remoteIP());
        Serial.print(" sent: ");
        Serial.print(byteSize);
        Serial.println(" bytes");
        for (int i = 0; i < byteSize; i++) {
          dataPacket[i] = client.read();
        }
        for (int i = 0; i < byteSize; i++) {
          Serial.print(dataPacket[i]);
        }
        Serial.println("\n\n");
        if(dataPacket[0] == '1') {
          client.println('2');
        }
        client.stop();
      }
    }
  }
}

