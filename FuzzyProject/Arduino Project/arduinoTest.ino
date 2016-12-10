#include <SimplyFuzzy.h>
#include <AFMotor.h>
#include <Math.h>
 
#define TRIGGER_R  52
#define ECHO_R     53
 
#define TRIGGER_M  38
#define ECHO_M     39
 
#define TRIGGER_L  23
#define ECHO_L     22
 
AF_DCMotor leftWheel(1);
AF_DCMotor rightWheel(2);
SimplyFuzzy sf;
int left, mid, right;
float outLeft, outRight;
 
void setup(){
  Serial.begin(9600);
  pinMode(TRIGGER_R,OUTPUT);
  pinMode(ECHO_R,INPUT);
  pinMode(TRIGGER_M,OUTPUT);
  pinMode(ECHO_M,INPUT);
  pinMode(TRIGGER_L,OUTPUT);
  pinMode(ECHO_L,INPUT);
  sf.init();
}
 
int distanceL(){
 
 digitalWrite(TRIGGER_L, LOW);
 delayMicroseconds(2);
 
 digitalWrite(TRIGGER_L, HIGH);
 delayMicroseconds(10);
 
 digitalWrite(TRIGGER_L, LOW);
 long duration = pulseIn(ECHO_L, HIGH);
 int distance = duration/58.2;
 if(distance > 200) {
  return 200;
 }
 return distance;
}
 
int distanceP(){
 
 digitalWrite(TRIGGER_R, LOW);
 delayMicroseconds(2);
 
 digitalWrite(TRIGGER_R, HIGH);
 delayMicroseconds(10);
 
 digitalWrite(TRIGGER_R, LOW);
 long duration = pulseIn(ECHO_R, HIGH);
 int distance = duration/58.2;
 if(distance > 200) {
  return 200;
 }
 return distance;
 
}
 
int distanceM(){
 
 digitalWrite(TRIGGER_M, LOW);
 delayMicroseconds(2);
 
 digitalWrite(TRIGGER_M, HIGH);
 delayMicroseconds(10);
 
 digitalWrite(TRIGGER_M, LOW);
 long duration = pulseIn(ECHO_M, HIGH);
 int distance = duration/58.2;
 if(distance > 200) {
  return 200;
 }
 return distance;
}
 
bool reverseCheck(float oldSpeed) {
  if(oldSpeed<0) return true;
  else return false;
}
 
float speedCheck(float oldSpeed) {
 
}
 
void loop(){
  left = distanceL();
  Serial.println("Inputs: ");
  Serial.print("Left : ");
  Serial.println(left);
 
  mid = distanceM();
  Serial.print("Mid  : ");
  Serial.println(mid);
 
  right = distanceP();
  Serial.print("Right: ");
  Serial.println(right);
 
  Serial.println("\n");
 
  sf.setInputs(left, mid, right);
  outLeft = sf.getOutput(true);
 
  Serial.print("Left Wheel : ");
  Serial.print(outLeft);
 
  Serial.println("\n");
  outRight = sf.getOutput(false);
 
  Serial.print("Right Wheel: ");
  Serial.print(outRight);
  Serial.println("\n");
 
  if(reverseCheck(outLeft)){
   
    leftWheel.run(RELEASE);
    leftWheel.run(BACKWARD);
    outLeft=abs(outLeft);
  } else {
    leftWheel.run(FORWARD);
  }
 
  if(reverseCheck(outRight)){
    rightWheel.run(RELEASE);
    rightWheel.run(BACKWARD);
    outRight=abs(outRight);
  } else {
    rightWheel.run(FORWARD);
  }
 
  leftWheel.setSpeed(outLeft);
  rightWheel.setSpeed(outRight);
 
  delay(100);
}