

#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;


void setup()
{
    Serial.begin(115200);
    delay(10);
    WiFiMulti.addAP("cthings.co", "lawl123456");

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
    const uint16_t port = 4242;
    const char * host = "10.0.0.11"; 
    
    Serial.print("connecting to ");
    Serial.println(host);
    WiFiClient client;

    if (!client.connect(host, port)) {
        Serial.println("connection failed");
        Serial.println("wait 5 sec...");
        delay(5000);
        return;
    }
    Serial.println("Ready to send data");
    Serial.println("Type in the above box and hit'send'");
    int byteSize = 0;
    char payload[256];
    
      if(byteSize = Serial.available()){
        Serial.print("Sending: ");
        Serial.print(byteSize);
        Serial.println(" bytes");
        
        for(int i = 0; i < byteSize; i++){
          payload[i] = Serial.read();
        }
        String s = "";
        for(int i = 0; i < byteSize; i++){
          s += payload[i];
          Serial.print(payload[i]);
        }
        Serial.println();
        client.println(s);
        
        String feedBack = client.readStringUntil('\n');
        Serial.println(feedBack);
        
        Serial.println();
      }
    
    while(!Serial.available()){
     
   }
}

