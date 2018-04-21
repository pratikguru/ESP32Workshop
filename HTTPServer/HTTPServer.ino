
#include <WiFi.h>
const char* ssid     = "Vent";
const char* password = "pizzasalami";
WiFiServer server(80);


//add list of IP's connected
//make better http page.

#define RELAY 32

//Analog Input
#define ANALOG_PIN_0 36
int analog_value = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(RELAY, OUTPUT);
  delay(10);
  connectWiFi();

}

int value = 0;

void loop()
{
  analog_value = analogRead(ANALOG_PIN_0);
  WiFiLocalWebPageCtrl();
}

/***************************************************
  Get indoor Temp/Hum data
****************************************************/


/***************************************************
  Send and receive data from Local Page
****************************************************/
void WiFiLocalWebPageCtrl(void)
{
  WiFiClient client = server.available();   // listen for incoming clients

  String sHTML;
  if (client) {
    Serial.println("New Client.");
    String currentLine = "";
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n') {
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Refresh: 0.5");
            client.println();
            client.println("<title> ESP32 Analog Data Server page</title>");
            client.println("</br>" );
            client.println("<p style = \"font-size:300%; text-align:center;\"> ESP32 Sensor console system</p><br>");
            client.print("<p style = \"font-size: 200%;\">Analog Data:</p>" + String(analog_value));
            
            client.print("<br>");
            client.print("<br>");
            client.print(" <h1>Click <a href=\"/H\">here</a> to turn the LED on.</h1><br><br><br>");
            client.print("<h1>Click <a href=\"/L\">here</a> to turn the LED off.</h1><br>");
          
            //AvailableClients();
            client.println();
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(RELAY, HIGH);               // GET /H turns the LED on
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(RELAY, LOW);                // GET /L turns the LED off
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}

/***************************************************
  Connecting to a WiFi network
****************************************************/
void connectWiFi(void)
{
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
}




