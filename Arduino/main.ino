#include <SPI.h>
#include <WiFiNINA.h>

#define oneout 2
#define onein 3
#define twoout 4
#define twoin 5

char ssid[] = "Arduino Network";
char pass[] = "6159250918";
int keyIndex = 0;

int status = WL_IDLE_STATUS;
WiFiServer server(80);

String readString;

void setup() {
  pinMode(oneout, OUTPUT);
  pinMode(twoout, OUTPUT);
  pinMode(onein, OUTPUT);
  pinMode(twoin, OUTPUT);
  Serial.begin(9600);

  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }
  server.begin();

  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);
}

void loop() {
  WiFiClient client = server.available();
  if (client)
  {
    Serial.println("new client");

    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        if (readString.length() < 100)
        {
          readString += c;
          Serial.write(c);
          
          if (c == '\n') {
            client.println("<a href=\"/?oneoff\"\">Actuator One Off</a>");
            client.println("<br />");
            client.println("<a href=\"/?oneout\"\">Actuator One Out</a>");
            client.println("<br />");
            client.println("<a href=\"/?onein\"\">Actuator One In</a>");
            client.println("<br />");
            client.println("<a href=\"/?twooff\"\">Actuator Two Off</a>");
            client.println("<br />");
            client.println("<a href=\"/?twoout\"\">Actuator Two Out</a>");
            client.println("<br />");
            client.println("<a href=\"/?twoin\"\">Actuator Two In</a>");
            client.println("<br />");

            delay(1);
            
            if(readString.indexOf("?oneoff") > 0)
            {
              digitalWrite(oneout, LOW);
              delay(1);
              digitalWrite(onein, LOW);
              delay(1);
            }
            else if(readString.indexOf("?oneout") > 0)
              {
                digitalWrite(oneout, HIGH);
              delay(1);
              digitalWrite(onein, LOW);
              delay(1);
              }
            
            else if(readString.indexOf("?onein") > 0)
              {
                digitalWrite(oneout, LOW);
              delay(1);
              digitalWrite(onein, HIGH);
              delay(1);
              }
            
            else if(readString.indexOf("?twooff") > 0)
              {
                digitalWrite(twoout, LOW);
              delay(1);
              digitalWrite(twoin, LOW);
              delay(1);
              }
            
            else if(readString.indexOf("?twoout") > 0)
              {
                digitalWrite(twoout, HIGH);
              delay(1);
              digitalWrite(twoin, LOW);
              delay(1);
            }
            else if(readString.indexOf("?twoin") > 0)
              {
                digitalWrite(twoout, LOW);
              delay(1);
              digitalWrite(twoin, HIGH);
              delay(1);
              }
            
            readString="";

            delay(1);
            client.stop();
            Serial.println("client disconnected");
          }
        }
      }
    }
  }
}
