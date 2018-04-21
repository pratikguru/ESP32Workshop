
#include <WiFi.h>
#include <WiFiServer.h>
const char* ssid     = "Vent";
const char* password = "pizzasalami";
WiFiServer server(80);

#define RELAY 32
#define ANALOG_PIN_0 36
int     analog_value = 0;

void setup()
{
  Serial.begin(115200);
  pinMode(RELAY, OUTPUT);
  delay(10);
  connectWiFi();
  //setWiFi("cthings.co", "lawl123456");
}
const char* cssButton = "<!DOCTYPE html>"
                        "<html>"
                        "<head>"
                        "<meta http-equiv='refresh' content='5'>"
                        "<style>"
                        ".button {"
                        "background-color: #A9A9A9;"
                        "border: none;"
                        "color: white;"
                        "transition: padding 0.3s ease;"
                        "padding: 20px;"
                        "text-align: center;"
                        "text-decoration: none;"
                        "display: inline-block;"
                        "font-size: 16px;"
                        "margin: 4px 2px;"
                        "cursor: pointer;"
                        "border-radius: 29px;"
                        "}"
                        ".button:hover {"
                        "padding: 25px;"
                        "}"
                        "</style>"
                        "</head>"
                        "<body>"
                        "<div style='text-align: center;'>"
                        "<form style='display: inline;'' action= \"/H\">"
                        "<input type='submit' class='button' value='On'>"
                        "</form>"
                        "<form style='display: inline;' action=\"/L\">"
                        "<input type='submit' class='button' value='Off'>"
                        "</form>"
                        "</div>"
                        "</body>"
                        "</html>";

int value = 0;

const char* cssButton2 = "<!DOCTYPE html>"
                         "<html>"
                         "<head>"
                         "<meta http-equiv='refresh' content='1'>"
                         "<style>"
                         ".button {"
                         "background-color: #A9A9A9;"
                         "border: none;"
                         "color: white;"
                         "transition: padding 0.3s ease;"
                         "padding: 20px;"
                         "text-align: center;"
                         "text-decoration: none;"
                         "display: inline-block;"
                         "font-size: 16px;"
                         "margin: 4px 2px;"
                         "cursor: pointer;"
                         "border-radius: 29px;"
                         "}"
                         ".button:hover {"
                         "padding: 25px;"
                         "}"
                         ".center_container {"
                         "display: flex;"
                         "justify-content: center;"
                         "align-items: center;"
                         "margin-top: 10%;"
                         "}"
                         ".boxxy {"
                         "height: 300px;"
                         "width: 300px;"
                         "border-radius: 10px;"
                         "background-color: gray;"
                         "display: flex;"
                         "align-items: center;"
                         "flex-direction: column;"
                         "justify-content: center;"
                         "}"
                         "#text-box {"
                         "padding: 12px 20px;"
                         "margin: 8px 0;"
                         "display: inline-block;"
                         "border: 1px solid #ccc;"
                         "border-radius: 4px;"
                         "box-sizing: border-box;"
                         "}"
                         "</style>"
                         "</head>"
                         "<body>"
                         "<div class='center_container'>"
                         "<div class='boxxy'>"
                         "<div class='buttons'>"
                         "<form style='display: inline;'' action='/H'>"
                         "<input type='submit' class='button' value='On'>"
                         "</form>"
                         "<form style='display: inline;' action=/L>"
                         "<input type='submit' class='button' value='Off'>"
                         "</form>"
                         "</div>"
                         "<input id='text-box' type='text'>"
                         "</div>"
                         "</div>"
                         "<script>"
                         "(function() {";

void loop()
{
  analog_value = analogRead(ANALOG_PIN_0);
  WiFiLocalWebPageCtrl();
}


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
            client.println();
            client.print(cssButton2);
            client.print("var x =" + String(analog_value) + ";");
            client.println("var box = document.getElementById(\'text-box\');");
            client.println("box.value = x;");
            client.println("})();");
            client.println("</script>");
            client.println("</html>");
            client.println();
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
      }
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
  while(WiFi.status() != WL_CONNECTED)
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

void setWiFi(const char* Name, const char* Password)
{
  ssid      = Name;
  password  = Password;
  while(!WiFi.softAP(ssid, password)) {
    Serial.print(".");
    delay(400);
  }
  Serial.println("WIFI < " + String(ssid) + " > ... Started");
  Serial.println(WiFi.softAPIP());
  server.begin();
  Serial.println("Server Started");
}


