//libraries
#include <SPI.h>
#include <WiFiNINA.h>

#define Equator_IN 2
#define Equator_OUT 3
#define Side_IN 4
#define Side_OUT 5

String userInput;

char ssid[] = "APSU Solar Project";
char pass[] = "solarproject";
int keyIndex = 0;                 // your network key Index number (needed only for WEP)

int status = WL_IDLE_STATUS;      //connection status
WiFiServer server(80);            //server socket

//special characters
char quote = '"';
char slash = '/';

Servo myservo;

void setup() {
  Serial.begin(9600);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  pinMode(Equator_OUT, OUTPUT);
  pinMode(Side_OUT, OUTPUT);
  pinMode(Equator_IN, OUTPUT);
  pinMode(Side_IN, OUTPUT);
  userInput = String("Stopped");

  // check for the presence of the network:
  while (status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    delay(10000);
  }

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }
  server.begin();                           // start the web server on port 80
  printWiFiStatus();                        // you're connected now, so print out the status
}


void loop() {

  // attempt to connect to WiFi network:
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to Network named: ");
    Serial.println(ssid);                   // print the network name (SSID);

    // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
    status = WiFi.begin(ssid, pass);
    // wait 10 seconds for connection:
    delay(10000);
  }

  int equatorRight = analogRead( A0 );
  int equatorLeft = analogRead( A1 );
  int rearRight = analogRead( A2 );
  int rearLeft = analogRead( A3 );
  int ERFiltered = round(((equatorRight * 15) + equatorRight) / 16); //one-pole filter
  int ELFiltered = round(((equatorLeft * 15) + equatorLeft) / 16); //one-pole filter
  int RRFiltered = round(((rearRight * 15) + rearRight) / 16); //one-pole filter
  int RLFiltered = round(((rearLeft * 15) + rearLeft) / 16); //one-pole filter
  int differenceVertical = (rearLeft + rearRight) - (equatorLeft + equatorRight); // check the diffirence of up and down
  int differenceHorizontal = (rearLeft + equatorLeft) - (rearRight + equatorRight); // check the diffirence og left and right
  int tolerance = 50;

  WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("new client");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();
            // the content of the HTTP response follows the header:
            client.println("<!DOCTYPE HTML>");
            client.print("<head>");
            client.print("<link rel=");
            client.print(quote);
            client.print("stylesheet");
            client.print(quote);
            client.print("href=");
            client.print(quote);
            client.print("https://ioio.mah.se/courses/IDK17/student_0007/mkrsheet.css");  //NOTE: link to your own css stylesheet here
            client.print(quote);
            client.print(slash);
            client.print (">");
            client.print("</head>");
            client.print("<body>");
            client.println("<center><br><br><div class='container'><h1>CONTROL YOUR SOLAR PANEL<h1/></div></center>");
            client.println("<center><div class='equator'> <left><button type='submit' value='down'    onmousedown=location.href='/H\'>Tilt Down</button></center>");
            client.println("<center><div class='equator'> <left><button type='submit' value='up'      onmousedown=location.href='/L\'>Tilt Up</button></center>");
            client.println("<center><div class='stop'>    <left><button type='submit' value='stop'    onmousedown=location.href='/X\'>Stop</button></center>");
            client.println("<center><div class='sides'>   <left><button type='submit' value='right'   onmousedown=location.href='/Y\'>Tilt Right</button></center>");
            client.println("<center><div class='sides'>   <left><button type='submit' value='left'    onmousedown=location.href='/P\'>Tilt Left</button></center>");
//            client.println("<center><div class='update'>  <left><button type='submit' value='update'  onmousedown=location.href='/U\'>Show Light Intensities</button></center>");
            client.println("Equator Left Intensity: ");
            client.println(ELFiltered);
            client.println("<br>");
            client.println("Equator Left Intensity: ");
            client.println(ELFiltered);
            client.println("<br>");
            client.println("Equator Right Intensity: ");
            client.println(ERFiltered);
            client.println("<br>");
            client.println("Top Left Intensity: ");
            client.println(RLFiltered);
            client.println("<br>");
            client.println("Top Right Intensity: ");
            client.println(RRFiltered);
            client.println("<br>");
            client.println("Vertical Difference: ");
            client.println(differenceVertical);
            client.println("<br>");
            client.println(" Horizontal Difference: ");
            client.println(differenceHorizontal);
            client.println("</body>");
            client.println("</html>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          }
          else {      // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        }
        else if (c != '\r') {    // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L" or "GET /X":
        if (currentLine.endsWith("GET /H")) {
          digitalWrite(Equator_OUT, LOW);
          delay(1);
          digitalWrite(Equator_IN, HIGH);
          delay(1);
        }
        if (currentLine.endsWith("GET /L")) {
          digitalWrite(Equator_OUT, HIGH);
          delay(1);
          digitalWrite(Equator_IN, LOW);
          delay(1);
        }
        if (currentLine.endsWith("GET /P")) {
          digitalWrite(Side_OUT, HIGH);
          delay(1);
          digitalWrite(Side_IN, LOW);
          delay(1);
        }
        if (currentLine.endsWith("GET /Y")) {
          digitalWrite(Side_OUT, LOW);
          delay(1);
          digitalWrite(Side_IN, HIGH);
          delay(1);
        }
        if (currentLine.endsWith("GET /X")) {
          digitalWrite(2, HIGH);
          delay(500);
          digitalWrite(3, HIGH);
          delay(500);
          digitalWrite(4, HIGH);
          delay(500);
          digitalWrite(5, HIGH);
          delay(500);
        }
//        if (currentLine.endsWith("GET /U")) {
//          client.println("Equator Left Intensity: ");
//          client.println(ELFiltered);
//          client.println("<br>");
//          client.println("Equator Right Intensity: ");
//          client.println(ERFiltered);
//          client.println("<br>");
//          client.println("Top Left Intensity: ");
//          client.println(RLFiltered);
//          client.println("<br>");
//          client.println("Top Right Intensity: ");
//          client.println(RRFiltered);
//          client.println("<br>");
//          client.println("Vertical Difference: ");
//          client.println(differenceVertical);
//          client.println("<br>");
//          client.println(" Horizontal Difference: ");
//          client.println(differenceHorizontal);
//        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void printWiFiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
  // print where to go in a browser:
  Serial.print("To see this page in action, open a browser to http://");
  Serial.println(ip);
}
