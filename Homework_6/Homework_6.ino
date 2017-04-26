//Bryce Graves
//Homework 6: The numbers Mason

//question 1: The numbers multiply until they get outside of the countable amount, since the count is signed it's only half the size it could count without the sign.
//question 2: 0-1023
//question 3: The chip is 10 bit which if you add with binary addition you get 1023 with 10 bits.

//Constants and defined values
int fadeR = 1;
int fadeG = 3;
int fadeB = 5;
int red =   1;
int green = 1;
int blue =  1;


//Pins being used in program: 4, 5, 6, 7, 8, 9, 10, 11
void pinsUsed(){
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}


//LED light boundaries and color change
void changeInColorRed(){
  red += fadeR;
  }
  
  
void changeInColorGreen(){
  green += fadeG;
}


void changeInColorBlue(){
  blue += fadeB;
}


bool redReachesBounds() {
  return (red > 255 || red < 0);
}


bool greenReachesBounds() {
  return (green > 255 || green < 0);
}


bool blueReachesBounds() {
  return (blue > 255 || blue < 0);
}


void boundaryCheck(){
  if (redReachesBounds()) {
    fadeR *= -1 ;
  }

  if (greenReachesBounds()) {
    fadeG *= -1 ;
  }

  if (blueReachesBounds()) {
    fadeB *= -1 ;
  }
}


void updateLight(){
  analogWrite(9, red);
  analogWrite(10, green);
  analogWrite(11, blue);
  delay(10);
  }


//Light control
void lightD8(){
    digitalWrite(8, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
}


void lightD7(){
    digitalWrite(7, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(8, LOW);
}


void lightD6(){
    digitalWrite(6, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
}


void lightD5(){
    digitalWrite(5, HIGH);
    digitalWrite(4, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
}


void lightD4(){
    digitalWrite(4, HIGH);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
}


//Lights up based on slider position
void lightWithSlider(){
  if (analogRead(3) == 1023) {
    lightD8();
    changeInColorRed();
  }
  else if (analogRead(3) > 614) {
    lightD7();
    changeInColorBlue();
  }
  else if (analogRead(3) > 409) {
    lightD6();
    changeInColorGreen();
  }
  else if (analogRead(3) > 205) {
    lightD5();
    changeInColorBlue();
  }
  else if (analogRead(3) == 0) {
    lightD4();
    changeInColorRed();
  }
}


//Debug: value output check
void displayValue() {
  Serial.print(analogRead(3));
  Serial.print(" ");
  Serial.println();
  delay( 100 );
}


void setup()
{
  Serial.begin(9600);
  pinsUsed();
}

void loop(){
  displayValue();
  lightWithSlider();
  updateLight();
  boundaryCheck();


}

