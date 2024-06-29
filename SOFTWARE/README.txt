You will need the the SPI and WiFiNINA libraries installed to compile each project.

Make sure the following settings are met in your IDE.
Board: Arduino Uno WiFi Rev 2
Register Emulation: None (ATMEGA4809)
Port: arduinounowifi (Probably COM 3)

Baud rate is set to 9600 for each one.

Make sure you have the latest version of Arduino installed.


Software instructions - Photoresistor_Reactive_Actuation.ino

This project has no input control but you are able to observe what it is doing by opening the Serial Monitor.


Software instructions - Manual_Jog_Actuators.ino

This project allows you to manually jog the actuators for testing. By using the Serial Monitor, you can send the Arduino a command to jog any actuator for 5 seconds at a time. The commands are Equator In, Equator Out, Side In, Side Out.

It will also print the text per jog for what the final project is supposed to say when it is tilting in the corresponding direction.


Software instructions - Wifi_Control.ino

For this project, you will need a router that has a SSID of "APSU Solar Project" with the password "solarproject".

After you upload the project to the Arduino, connect your computer WiFi to the APSU Solar Project Router.

Open Serial Monitor with the Arduino still connected. Once the Arduino connects to the router, it will display an IP address that you can enter into your web browser. (http://xxx.xxx.xxx.xxx)

Once you load the website, you will be able to manually jog the actuators. The light reactive movement is not included with this project.

Software instructions - Solar_Panel_Combined_Codebase.ino

This is the final project. Essentially this is the WiFi Control project plus the Photoresistor Reactive Actuation project. There is no Serial Monitor control included in this project.

All software written by Taylor Matson.