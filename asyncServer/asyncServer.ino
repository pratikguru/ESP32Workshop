#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;
const char* ssid;
const char* password;
//const char* host = "192.168.2.189";
#define rxPort 4242
#define txPort 4343


WiFiServer rxServer(txPort);
WiFiServer txServer(rxPort);
WiFiClient rxClient;
WiFiClient txClient;
unsigned long long timer;
unsigned long long lapTime;
int button = 36;


void setup() {
  Serial.begin(115200);
  pinMode(button, INPUT);
  setWifi("Vent", "pizzasalami");
}

void setWifi(const char* Name, const char* Password)
{

  
  ssid      = Name;
  password  = Password;
  WiFiMulti.addAP(ssid, password);
  Serial.println("WIFI < " + String(ssid) + " > ... Started");
  while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }
  Serial.println(WiFi.localIP());
  txServer.begin();
  rxServer.begin();
  txServer.setNoDelay(true);
  rxServer.setNoDelay(true);
  Serial.println("Server Started");
}

void loop() {
  portOne();
  int val = analogRead(button);
  delay(100);
  if(val == 0) {
    Serial.println("Hand over sensor 3");
    portTwo("192.168.2.140");
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
        lapTime = millis();
        Serial.print(rxClient.remoteIP());
        Serial.println(" sent: " + message);
        Serial.println("---------------------------------");
        Serial.println("\n");
        rxClient.stop();
      }
    }
  }
}

void portTwo(const char* host) {
  //if ((long long)millis() - (long long)timer >= 5000) {
  
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
      txClient.println("Trigger from sensor 3");
      Serial.println();
      timer = millis();
      delay(100);
    
  //}
}


