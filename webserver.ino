//web server
#include <WiFi.h>
#include <DHT.h>
#define DPIN 32
#define DTYPE DHT11
#define FIRE_PIN 25
#define MQ135_SENSOR_PIN 35
int sensitivity = 200;
DHT dht(DPIN, DTYPE);
// Replace with your network credentials
const char* ssid = "Your Hotspot name";
const char* password = "Your Hotspot's password";
// Create a WiFiServer object
WiFiServer server(80);
void setup(){
Serial.begin(115200);
pinMode(FIRE_PIN, INPUT);
dht.begin();
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
delay(1000);
Serial.print(".");
}
Serial.println("");
Serial.println("WiFi connected.");
Serial.println("IP address: ");
Serial.println(WiFi.localIP());
// Start the server
server.begin();
}
String interpret_air_quality(int sensor_value) {
if (sensor_value < 350)
return "Excellent";
else if (sensor_value < 500)
return "Good";
else if (sensor_value < 850)
return "Moderate";
else if (sensor_value < 1000)
return "Poor";
else
return "Dangerous";
}
void loop() {
// Check if a client has connected
WiFiClient client = server.available();
if (!client) {
return;
}
Serial.println("New client connected");//this will indicate that the
user is now connected to the web server
//Sending HTTP Request
while (!client.available()) {
delay(1);
}
// Read the first line of the request
//We push the sensor data and allow the web server to read/display the
respective data
String request = client.readStringUntil('\r');
client.flush();
// Read sensor values
float temperatureC = dht.readTemperature(false); // in Celsius
float temperatureF = dht.readTemperature(true); // in Fahrenheit
float humidity = dht.readHumidity(); // Humidity
int gasValue = analogRead(MQ135_SENSOR_PIN); // Gas sensor value
int airQuality = gasValue * sensitivity / 1023; // Calculate air
quality
String airQualityLabel = interpret_air_quality(airQuality);
int flame = digitalRead(FIRE_PIN); // Fire sensor status
String fireStatus = (flame == HIGH) ? "Fire detected!" : "No fire
detected";
// Prepare the response for the web page
String html = "<!DOCTYPE html>";
html+="<html><head><meta http-equiv='refresh' content='5'/>";
html+="<title>ESP32 Sensor Data</title>";
html+="</head><style>";
//internal css - cascading style sheets (to design/style our web page)
html+="html {background-color: black;color: white;font-family:
sans-serif;text-align: center;}";
html+="p{color: #B27AFB;font-weight: 200;}";
html+=".spacer {margin: 5%;}";
//designing part of our nexus logo on the web page
html+=".square {height: 100px;width: 100px;background-color:
#000;border: #8957ca solid 5px;outline: 5px solid #B27AFB;margin:
5px;border-radius: 15%;margin-inline: auto;}";
html+=".eye{height: 45px;width: 28px;margin-left: 15px;background-color:
#c4a1f1;border-radius: 5px;}</style>";
html+="<body><div class='spacer'></div>";
html+="<div class='square'>\t<div>";
html+="\n\t\t&nbsp;";
html+="\n\t<div class='eye'></div>";
html+="\n\t\t<div class='eye' style='margin-left: 55px; margin-top:
-45px;'></div>";
html+="\n\t</div>";
html+="\n</div>\n";
html+="<h1>Nexus</h1>";
//^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
html+="<br>";
//displaying the sensor data onto the webpage
html+="<h3>Temperature:</h3><p>" + String(temperatureC) + "&deg;C(" +
String(temperatureF) + "&deg;F)</p> <h3>Humidity:</h3><p>" +
String(humidity) + "%</p>";
html+="<h3>Air Quality:</h3><p> " + String(airQuality) + " (" +
airQualityLabel + ")</p>";
html+="<h3>Fire Status:</h3><p>" + fireStatus + "</p>";
html+="</body></html>";
// Send HTTP response
//once the web page is created, the IP address will be returned on the
serial monitor
client.println("HTTP/1.1 200 OK");
client.println("Content-type:text/html");
client.println();
client.println(html);
client.println();
delay(1000);
}
