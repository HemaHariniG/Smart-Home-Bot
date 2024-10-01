#define BLYNK_TEMPLATE_ID "TMPL3ryFQVzDR"
#define BLYNK_TEMPLATE_NAME "NEXUS CAR"
#define BLYNK_AUTH_TOKEN "EQxU0jS5pABey1utA2Qo5dNx4UpSmRSN"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "your hotspot name";   // Wi-Fi SSID
char pass[] = "your hotspot password";   // Wi-Fi Password

#define IN1 4
#define IN2 5 
#define IN3 13
#define IN4 12

void setup() {
  Serial.begin(115200);

  // Connect to Wi-Fi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  Blynk.begin(auth, ssid, pass);
}

void forward()
{
  Serial.println("forward");
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void deviateLeft()
{
  Serial.println("left");
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,HIGH);
  digitalWrite(IN4,LOW);
}

void deviateRight()
{
  Serial.println("right");
  digitalWrite(IN1,LOW);
  digitalWrite(IN2,HIGH);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

void reverse()
{
  Serial.println("back");
  digitalWrite(IN1,HIGH);
  digitalWrite(IN2,LOW);
  digitalWrite(IN3,LOW);
  digitalWrite(IN4,HIGH);
}

void stop(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
// forward
BLYNK_WRITE(V0) { 
  int value = param.asInt();
  if (value == 1){
    forward();
  } else {
    stop();
  }
}   
// reverse
BLYNK_WRITE(V1) { 
  int value = param.asInt();
  if (value == 1){
    reverse();
  } else {
    stop();
  }
}  
// Right
BLYNK_WRITE(V2) { 
  int value = param.asInt();
  if (value == 1){
    deviateRight();
  } else {
    stop();
  }
} 
// Left
BLYNK_WRITE(V3) { 
  int value = param.asInt();
  if (value == 1){
    deviateLeft();
  } else {
    stop();
  }
}  

void loop(){
  Blynk.run();
}


