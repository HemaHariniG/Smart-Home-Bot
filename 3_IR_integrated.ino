const int leftIR = 19; // Pin connected to the left IR sensor
const int centerIR = 18; // Pin connected to the center IR sensor
const int rightIR = 21; // Pin connected to the right IR sensor
void setup() {
 // Set the IR sensor pins as inputs
 pinMode(leftIR, INPUT);
 pinMode(centerIR, INPUT);
 pinMode(rightIR, INPUT);
 // Initialize serial communication
 Serial.begin(9600);
 }
 void loop() {
 // Read the states of the IR sensors
 int leftState = digitalRead(leftIR);
 int centerState = digitalRead(centerIR);
 int rightState = digitalRead(rightIR);
 // Check and print for obstacles detected by each IR sensor (Negative
 Logic)
 if (leftState == LOW) {
 Serial.println("Obstacle detected on the left!");
 } else {
 Serial.println("No obstacle on the left.");
 }
 delay(1000);
 if (centerState == LOW) {
Serial.println("Obstacle detected in the center!");
 } else {
 Serial.println("No obstacle in the center.");
 }
 delay(1000);
 if (rightState == LOW) {
 Serial.println("Obstacle detected on the right!");
 } else {
 Serial.println("No obstacle on the right.");
 }
 delay(1000); // Wait for 1000ms before checking again
 
