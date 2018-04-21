
#include <WiFi.h>
#include <WiFiMulti.h>
WiFiMulti WiFiMulti;

const char* ssid;
const char* password;
void setWiFi(const char* ssid_, const char* password_);

void setup() {
  Serial.begin(115200);
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
  while (WiFi.status() != WL_CONNECTED) {
    delay(400);
    Serial.print(".");
  }
  Serial.println("\n\n");
  Serial.println("WiFi connected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());  
}

void loop() {

  const uint16_t port = 80;
  const char * host = "192.168.2.198";

  Serial.print("connecting to ");
  Serial.println(host);
  WiFiClient client;

  if (!client.connect(host, port)) {
    Serial.println("connection failed");
    Serial.println("wait 5 sec...");
    delay(5000);
    return;
  }
  int byteSize = 0;
  char payload[256];
  if (byteSize = Serial.available()) {
    Serial.print("Sending: ");
    Serial.print(byteSize);
    Serial.println(" bytes");
    
    for (int i = 0; i < byteSize; i++) {
      payload[i] = Serial.read();
    }
    
    String s = "";
    for (int i = 0; i < byteSize; i++) {
      s += payload[i];
      Serial.print(payload[i]);
    }
    Serial.println();
    client.println(s);

    String feedBack = client.readStringUntil('\n');
    Serial.println(feedBack);

    if(feedBack[0] == '2') {
      Serial.println("Synced feedback received.");
    }
    client.stop();
  }

  while (!Serial.available()) {

  }



}


