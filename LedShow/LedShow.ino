#include <WiFi.h>
#include <WiFiMulti.h>

WiFiMulti WiFiMulti;
char* ssid;
char* password;
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

void setWifi(char* Name, char* Password)
{

  WiFi.disconnect();
  ssid      = Name;
  password  = Password;
  WiFiMulti.addAP("Vent", "pizzasalami");
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
  delay(100);
  if((long long)millis() - (long long)timer >= 3000){
    portTwo("192.168.2.127");
    timer = millis()
    }
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

  //Port for transmitting data.
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
      txClient.println("Ping from Node!");
      Serial.println();
      timer = millis();
      delay(100);
    
  //}
}


