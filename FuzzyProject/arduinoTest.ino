#include <SimplyFuzzy.h>

SimplyFuzzy sf;
int left, mid, right;
float outValue;

void setup(){
  Serial.begin(9600);

  sf.init();
}

void loop(){
  Serial.println("Inputs: ");
  Serial.parseInt(left);
  Serial.print("Left : ");
  Serial.println(left);
  
  Serial.parseInt(mid);
  Serial.print("Mid  : ");
  Serial.println(mid);

  Serial.parseInt(right);
  Serial.print("Right: ");
  Serial.println(right);

  Serial.println("\n");

  sf.setInputs(left, mid, right);
  outValue = sf.getOutput(true);

  Serial.print("Left Wheel : ");
  Serial.print(outValue);

  outValue = sf.getOutput(false);
  
  Serial.print("Right Wheel: ");
  Serial.print(outValue);

  delay(100);
}