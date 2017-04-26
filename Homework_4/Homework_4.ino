//Bryce Graves
//Homework 4: My Trump Card


//Questions:
//1. When I define a sequence length in one of that past homeworks it turns on lights that aren't defined in setup. Any idea what causes this?
//2. If I plan on dividing values later is it almost always worth defining integers as double at the start to avoid issues or is it best practice to use int?


//Defined constants
const int LED = 3;
const int fadeFix = 3;
const int red = 9;
const int green = 10;
const int blue = 11;


//Defined changeable values
int brightness = 0;
int fadeR = 1;
int fadeG = 1;
int fadeB = 1;


//Pins used
void setup() {
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
}


//Loops using 510 tic
void loop() {
  //for (int i = 0; i < LED; ++i) {
    for (int x = 0; x < 510; ++x) {
      redFish();
      delay(50);
    }
  //delay(50);
    for (int x = 0; x < 510; ++x) {
      blueFish();
      delay(50);
    }
  //delay(50);
    for (int x = 0; x < 510; ++x) {
      greenFish();
      delay(50);
    }
  //delay(50);
}
//}


//Light definitions, each details a cycle that goes from off to bright over 510 tics
void redFish(){
  analogWrite(9, brightness);
  brightness = brightness + fadeR;

  if (brightness == 0 || brightness == 255) {
    fadeR = -fadeR ;
  }
}

void blueFish(){
  analogWrite(11, brightness);
  brightness = brightness + fadeG;

  if (brightness == 0 || brightness == 255) {
    fadeG = -fadeG ;
  }
}

void greenFish(){
  analogWrite(10, brightness);
  brightness = brightness + fadeB;

  if (brightness == 0 || brightness == 255) {
    fadeB = -fadeB ;
  }
}

