#include <SimplyFuzzy.h>
#include <AFMotor.h>


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
int outLeft, outRight;

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



    digitalWrite(TRIGGER_L, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIGGER_L, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIGGER_L, LOW);
    duration = pulseIn(ECHO_L, HIGH);
 int distance_check = duration/58.2;


   digitalWrite(TRIGGER_L, LOW);
   delayMicroseconds(2);

   digitalWrite(TRIGGER_L, HIGH);
   delayMicroseconds(10);

   digitalWrite(TRIGGER_L, LOW);
   duration = pulseIn(ECHO_L, HIGH);
  int distance_check2 = duration/58.2;

  if(distance <= distance_check && distance_check <= distance_check2) {
    return distance_check;
  } else if (distance <= distance_check2 && distance_check2 <= distance_check) {
    return distance_check2;
  } else if (distance_check <= distance && distance <= distance_check2) {
    return distance;
  }else if (distance_check <= distance_check2 && distance_check2  <= distance){
     return distance_check2;
 }else if (distance_check2 <= distance && distance <= distance_check){
   return distance;
 }else if (distance_check2 <= distance_check && distance_check  <= distance){
   return distance_check;
 }else return 11;
}

int distanceP(){

 digitalWrite(TRIGGER_R, LOW);
 delayMicroseconds(2);

 digitalWrite(TRIGGER_R, HIGH);
 delayMicroseconds(10);

 digitalWrite(TRIGGER_R, LOW);
 long duration = pulseIn(ECHO_R, HIGH);
 int distance = duration/58.2;

 digitalWrite(TRIGGER_R, LOW);
 delayMicroseconds(2);

 digitalWrite(TRIGGER_R, HIGH);
 delayMicroseconds(10);

 digitalWrite(TRIGGER_R, LOW);
 duration = pulseIn(ECHO_R, HIGH);
 int distance_check = duration/58.2;


 digitalWrite(TRIGGER_R, LOW);
 delayMicroseconds(2);

 digitalWrite(TRIGGER_R, HIGH);
 delayMicroseconds(10);

 digitalWrite(TRIGGER_R, LOW);
 duration = pulseIn(ECHO_R, HIGH);
 int distance_check2 = duration/58.2;

 if(distance <= distance_check && distance_check <= distance_check2) {
 return distance_check;
 } else if (distance <= distance_check2 && distance_check2 <= distance_check) {
 return distance_check2;
 } else if (distance_check <= distance && distance <= distance_check2) {
 return distance;
 }else if (distance_check <= distance_check2 && distance_check2  <= distance){
  return distance_check2;
 }else if (distance_check2 <= distance && distance <= distance_check){
 return distance;
 }else if (distance_check2 <= distance_check && distance_check  <= distance){
 return distance_check;
 }else return 11;
}

int distanceM(){

 digitalWrite(TRIGGER_M, LOW);
 delayMicroseconds(2);

 digitalWrite(TRIGGER_M, HIGH);
 delayMicroseconds(10);

 digitalWrite(TRIGGER_M, LOW);
 long duration = pulseIn(ECHO_M, HIGH);
 int distance = duration/58.2;

     digitalWrite(TRIGGER_M, LOW);
     delayMicroseconds(2);

     digitalWrite(TRIGGER_M, HIGH);
     delayMicroseconds(10);

     digitalWrite(TRIGGER_M, LOW);
     duration = pulseIn(ECHO_M, HIGH);
  int distance_check = duration/58.2;


    digitalWrite(TRIGGER_M, LOW);
    delayMicroseconds(2);

    digitalWrite(TRIGGER_M, HIGH);
    delayMicroseconds(10);

    digitalWrite(TRIGGER_M, LOW);
    duration = pulseIn(ECHO_M, HIGH);
   int distance_check2 = duration/58.2;

   if(distance <= distance_check && distance_check <= distance_check2) {
     return distance_check;
   } else if (distance <= distance_check2 && distance_check2 <= distance_check) {
     return distance_check2;
   } else if (distance_check <= distance && distance <= distance_check2) {
     return distance;
   }else if (distance_check <= distance_check2 && distance_check2  <= distance){
      return distance_check2;
  }else if (distance_check2 <= distance && distance <= distance_check){
    return distance;
  }else if (distance_check2 <= distance_check && distance_check  <= distance){
    return distance_check;
  }else return 11;
}



bool reverseCheck(int oldSpeed) {
  if(oldSpeed<0) return true;
  else return false;
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
    delay(6);
    leftWheel.run(BACKWARD);
    outLeft=abs(outLeft);
  } else {
    leftWheel.run(FORWARD);
  }

  if(reverseCheck(outRight)){
    rightWheel.run(RELEASE);
    delay(6);
    rightWheel.run(BACKWARD);
    outRight=abs(outRight);
  } else {
    rightWheel.run(FORWARD);
  }
  delay(6);
  leftWheel.setSpeed(outLeft);
  delay(6);
  rightWheel.setSpeed(outRight);

  delay(500);
}
