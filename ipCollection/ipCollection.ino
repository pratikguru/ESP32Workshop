#include <WiFi.h>


char*       ssid;              
char*       password;         

#define     MAXSC     6          
unsigned long long timer;


WiFiServer  server(80);      
WiFiClient  client[MAXSC];     

void setup()
{

  Serial.begin(115200);           
  SetWifi("Vent", "pizzasalami");
}



void loop()
{

  AvailableClients();
  AvailableMessage();

}

void SetWifi(char* Name, char* Password)
{

  WiFi.disconnect();
  ssid      = Name;
  password  = Password;


  WiFi.begin(ssid, password);
  Serial.println("WIFI < " + String(ssid) + " > ... Started");
  while(WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(1000);
  }
  Serial.println(WiFi.localIP());
  server.begin();
  server.setNoDelay(true);
  Serial.println("Server Started");
}



void AvailableClients()
{
  uint8_t i;
  if (server.hasClient()) {
    for ( i = 0; i < MAXSC; i++) {
      if (!client[i] || !client[i].connected()) {
        if (client[i]) {
          client[i].stop();
        }
        if (client[i] = server.available()) {
          Serial.println("New Client: " + String(i));
        }
        continue;
      }
    }
    WiFiClient client = server.available();
    client.stop();
  }
  else {
   
    if((long long)millis() - (long long)timer >= 5000){ 
    Serial.println("--------------Updated list-------------");
    if (client[i]) {
      for (int j = 0; j < MAXSC; j++) {
        if (client[j] && client[j].connected()) {
          Serial.print("[" + String(j) + "]:" + " ");
          Serial.println((client[j].remoteIP()));
        }
      }
      Serial.println("-------------------------------------");
      delay(1000);
      }
      timer = millis();
    }
  }
}



void AvailableMessage()
{
  //check clients for data
  for (uint8_t i = 0; i < MAXSC; i++)
  {
    if (client[i] && client[i].connected() && client[i].available())
    {
      while (client[i].available())
      {
        String Message = client[i].readStringUntil('\r');
        client[i].flush();
        Serial.println("Client No " + String(i) + " - " + Message);
        client[i].println("Server Side ACK");
        Serial.println("\n\n\n");
      }
    }
  }
}


