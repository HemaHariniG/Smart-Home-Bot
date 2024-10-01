#include <DHT.h>

#define DPIN 32     
#define DTYPE DHT11   
#define fire 25
#define MQ135_SENSOR_PIN 35

int sensitivity = 200;
DHT dht(DPIN, DTYPE);

void setup() {
  Serial.begin(115200);
  pinMode(fire , INPUT);
  pinMode(MQ135_SENSOR_PIN,INPUT);
  dht.begin();
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
void loop(){
  
  float temperatureC = dht.readTemperature(false);  
  float temperatureF = dht.readTemperature(true);  
  float humidity = dht.readHumidity();            
 
  int gasValue = analogRead(MQ135_SENSOR_PIN);     
  int airQuality = gasValue * sensitivity / 1023;
  String airQualityLabel = interpret_air_quality(airQuality);


  int flame = digitalRead(fire);


  if (flame==HIGH){
    Serial.println("No fire detected");
    Serial.println( );
    } else{
      Serial.println("Fire detected");
      Serial.println( );
    }


  Serial.print("Temp: ");
  Serial.print(temperatureC);
  Serial.print(" C, ");
  Serial.print(temperatureF);
  Serial.print(" F");
  Serial.println( );
  Serial.print("humidity: ");
  Serial.print(humidity);
  Serial.print("%");
  Serial.println( );
  Serial.print("Air Quality Index (Calibrated): ");
  Serial.print(airQualityLabel);
  Serial.println( );
  delay(2000);
}
