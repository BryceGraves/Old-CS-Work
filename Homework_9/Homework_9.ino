//Bryce Graves
//Homework 9: Structs

struct colored_light {
	byte red;
	byte green;
	byte blue;
};

struct colored_light selectRedBlue(struct colored_light led){
  led.red = map(analogRead(3), 0, 1023, 0, 255);
  led.green = 0;
  led.blue = map(analogRead(3), 0, 1023, 0, 255);
  return led;
}

struct colored_light selectGreenBlue(struct colored_light led){
  led.red = 0;
  led.green = map(analogRead(3), 0, 1023, 0, 255);
  led.blue = map(analogRead(3), 0, 1023, 0, 255);
  return led;
}

struct colored_light selectRedGreen(struct colored_light led){
  led.red = map(analogRead(3), 0, 1023, 0, 255);
  led.green = map(analogRead(3), 0, 1023, 0, 255);
  led.blue = 0;
  return led;
}

void turnOnLight(struct colored_light *led){
  analogWrite(9, led.red);
  analogWrite(10, led.green);
  analogWrite(11, led.blue);
}

sizeof

void setup() {

}

void loop() {
  struct colored_light led;
  led = selectRedBlue(led);
  turnOnLight(led);
  delay(100);
  led = selectGreenBlue(led);
  turnOnLight(led);
  delay(100);
  led = selectRedGreen(led);
  turnOnLight(led);
  delay(100);
  
}

