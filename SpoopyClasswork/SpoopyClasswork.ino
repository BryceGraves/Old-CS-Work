//Bryce Graves
//Spoopy Fades


//Constants and defined values
int fadeR = 1;
int fadeG = 3;
int fadeB = 5;
int red =   0;
int green = 0;
int blue =  0;


  
  //Application of fade change
void changeInColor(){
  red += fadeR;
  green += fadeG;
  blue += fadeB;
  }

bool redReachesBounds() {
  return (red >= 255 || red <= 0);
}

bool greenReachesBounds() {
  return (green >= 255 || green <= 0);
}

bool blueReachesBounds() {
  return (blue >= 255 || blue <= 0);
}


void setup() {
   //Filled with dead memes
}


void loop() {
  updateLight();
  changeInColor();
  

  //boundry check, top and bottom
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
  delay(50);
  }
