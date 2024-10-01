 # define IN1 4
 # define IN2 5
 # define IN3 13
 # define IN4 12
 int centerIR; // ALL THREE FOR INITIALIZING IR PIN
 int leftIR;
 int rightIR;
 int leftFlag;
 int centerFlag;
 int rightFlag;
 void setup() {
 // put your setup code here, to run once:
 pinMode(IN1, OUTPUT);
 pinMode(IN2, OUTPUT);
 pinMode(IN3, OUTPUT);
 pinMode(IN4, OUTPUT);
 pinMode(centerIR,INPUT);
 pinMode(leftIR,INPUT);
 pinMode(rightIR,INPUT);
 Serial.begin(115200);
 }
 void loop() {
 // put your main code here, to run repeatedly:
 centerIR = digitalRead(18);// connected as negative logic-0 is
 detected and 1 is not detected
 leftIR = digitalRead(19);
 rightIR = digitalRead(21);
 if(leftIR==0){
 leftFlag=1;
 }
 else{
 leftFlag=0;
 }
 if(centerIR==0){
centerFlag=1;
 }
 else{
 centerFlag=0;
 }
 if(rightIR==0){
 rightFlag=1;
 }
 else{
 rightFlag=0;
 }
 if(leftFlag==0 && centerFlag==0 && rightFlag==0){
 forward();
 }
 else if(centerFlag==1){
 if(leftFlag==1){
 deviateright();
 }
 else if(rightFlag==1){
 deviateleft();//forward after?
 }
 else{
 deviateleft();//ok?
 }
 }
 else if(leftFlag==1){
 deviateright();
 }
 else if(rightFlag==1){
 deviateleft();
 }
 else if(leftFlag==1 && centerFlag==1 && rightFlag==1){
 reverse();
 }
 }
 void forward()
{
 Serial.println("Forward");
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,HIGH);
 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,LOW);
 delay(1000);
 }
 void deviateleft()
 {
 Serial.println("Left");
 digitalWrite(IN1,HIGH);
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,HIGH);
 digitalWrite(IN4,LOW);
 delay(1000);//issue with delay?
 }
 void deviateright()
 {
 Serial.println("Right");
 digitalWrite(IN1,LOW);
 digitalWrite(IN2,HIGH);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,HIGH);
 delay(1000);
 }
 void backward()
 {
 Serial.println("Backing Up");
 digitalWrite(IN1,HIGH);
 digitalWrite(IN2,LOW);
 digitalWrite(IN3,LOW);
 digitalWrite(IN4,HIGH);
 delay(1000);
