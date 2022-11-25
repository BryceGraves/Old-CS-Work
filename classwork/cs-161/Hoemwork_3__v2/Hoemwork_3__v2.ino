
int brightness = 0;
int fadeAmount = 1;

void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}

void loop() {
  redFish();
  blueFish();
  notLikeTheOthers();
  delay(30);
}

void redFish(){
  analogWrite(9, brightness);
  brightness = brightness + fadeAmount;

  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
  }
}

void blueFish(){
  analogWrite(10, brightness);
  brightness = brightness + fadeAmount;

  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
  }
}

void notLikeTheOthers(){
  analogWrite(11, brightness);
  brightness = brightness + fadeAmount;

  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ;
  }
}

