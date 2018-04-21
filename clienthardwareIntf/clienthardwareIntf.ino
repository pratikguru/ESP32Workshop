
#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;
void setup()
{
    Serial.begin(115200);
    delay(10);
    WiFiMulti.addAP("Vent", "pizzasalami");

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");
    WiFi.mode(WIFI_STA);
    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    delay(500);
}


void loop()
{
    const uint16_t port = 80;
    const char * host = "192.168.2.127"; 
    
    Serial.print("connecting to ");
    Serial.println(host);
    WiFiClient client; 
    uint8_t data[2] = {0x01, 0x00};
  
    Serial.println("Connected: " + String(host));
    if (!client.connect(host, port)) {
      Serial.println("Failed to connect to server");
      delay(500);
      return;
    }
   
    for (int i = 0; i < 2; i++) {
      client.print(data[i]);
      String feedback = client.readStringUntil('\n');
      Serial.println(feedback);
      delay(500);
    }
}

