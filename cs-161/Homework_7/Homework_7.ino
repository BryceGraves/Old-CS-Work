//Bryce Graves
//Homework 7: I am the night

//Question 1: 0 - 1000 ish

void printValue(){
  Serial.print(analogRead(1));
  Serial.println();
}

int light(){
  return 255 / analogRead(1);
}

/*int switchOutput(){
  return analogRead(2);
}*/

void lightFade(){
  analogWrite(5, light());
  analogWrite(6, light());
}

void redOrBlue(){
  if (digitalRead(2) == 1) {
    analogWrite(9, light());
    analogWrite(10, 0);
  } else  if (digitalRead(2) == 0) {
    analogWrite(10, light());
    analogWrite(9, 0);
  }
}

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  printValue();
  lightFade();
  redOrBlue();
}

