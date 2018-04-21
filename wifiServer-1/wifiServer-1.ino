
#include <WiFi.h>

const char* ssid     = "Vent";
const char* password = "pizzasalami";


WiFiServer server(80);

void setup()
{
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
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
        client.println("ACK from server"); //Feedack to the client
        client.stop();
      }
    }
  }
}

