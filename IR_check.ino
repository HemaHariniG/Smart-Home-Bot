// NEGATIVE LOGIC
const int irSensorPin = 18; // Pin connected to the IR sensor
 void setup() {
 pinMode(irSensorPin, INPUT); // Set the IR sensor pin as input
 Serial.begin(115200); // Initialize serial communication
 }
 void loop() {
 int irState = digitalRead(irSensorPin); // Read the state of the IR
 sensor
 if (irState == 0) { // If the IR sensor detects an object (active LOW)
 Serial.println("Obstacle detected!");
 } else { // No obstacle detected
 Serial.println("No obstacle.");
 }
 delay(500); // Wait for 500ms before checking again
 }

// POSITIVE LOGIC
const int irSensorPin = 18; // Pin connected to the IR sensor
 void setup() {
 pinMode(irSensorPin, INPUT); // Set the IR sensor pin as input
 Serial.begin(115200); // Initialize serial communication
 }
 void loop() {
 int irState = digitalRead(irSensorPin); // Read the state of the IR
 sensor
if (irState == 1) { // If the IR sensor detects an object (active LOW)
 Serial.println("Obstacle detected!");
 } else { // No obstacle detected
 Serial.println("No obstacle.");
 }
 delay(500); // Wait for 500ms before checking again
 }
