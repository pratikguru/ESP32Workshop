#include <WiFi.h>
char* ssid;
char* password;
const char* host = "192.168.2.189";
#define rxPort 4242
#define txPort 4343


WiFiServer rxServer(txPort);
WiFiServer txServer(rxPort);
WiFiClient rxClient;
WiFiClient txClient;
unsigned long long timer;
unsigned long long lapTime;

void setup() {
  Serial.begin(115200);
  setWifi("Vent", "pizzasalami");
}

void setWifi(char* Name, char* Password)
{

  WiFi.disconnect();
  ssid      = Name;
  password  = Password;
  WiFi.begin(ssid, password);
  Serial.println("WIFI < " + String(ssid) + " > ... Started");
 
  rxServer.begin();
  rxServer.setNoDelay(true);
  txServer.begin();
  txServer.setNoDelay(true);
  Serial.println("Server Started");
  Serial.println(WiFi.localIP());
}

void loop() {
  portOne();
  int val = analogRead(36);
  delay(100);
  if (val == 0){
    portTwo();
    Serial.println("Hand over sensor2");
    return;
  }
}

void portOne() {
  //Port for receiving data.
  
  rxClient = rxServer.available();
  if (rxClient) {
    if (rxClient.connected()) {
      if (rxClient.available()) {
        Serial.println("---------------------------------");
        Serial.print("Last message received: ");
        float x = (long long)millis() - (long long)lapTime;
        Serial.println(x/1000);
        x = 0;
        String message = rxClient.readStringUntil('\n');
        Serial.print(rxClient.remoteIP());
        Serial.println(" sent: " + message);
        lapTime = millis();
        //rxClient.println("ACK from rxPort");
        Serial.println("---------------------------------");
        Serial.println("\n");
        rxClient.stop();
      }
    }
  }
}

void portTwo() {
 
  //Port for transmitting data.
   {
   
    Serial.print("Connecting to: ");
    Serial.print(txPort);
    Serial.print(":");
    Serial.println(host);

    if (!txClient.connect(host, txPort)) {
      Serial.println("Connection failed");
      Serial.println("wait 5 sec....");
      delay(5000);
      return;
    }
    else {
      txClient.println("Trigger from sensor 2");
      Serial.println();
      
    }
  }
}


