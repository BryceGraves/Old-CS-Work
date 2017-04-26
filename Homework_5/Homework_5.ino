//Bryce Graves
//Homework 5: YOU THINK THIS IS A GAME?!

//The program lights up a light at a time, the switch speeds it up or slows it down. While the button stops the light sequence.

//1. We use pinMode(x, INPUT);
//2. They define that function at the top of the program like we should so the C language doesn't need to use hoisting to bring the function definitions to the top.
//3. Because the code from Ardublock is created by preset blocks which we kinda just smash together to form the code block from the example.

int LED = 0;
int Speed = 0;
void returnPinAndBoolean(int pinNumber, boolean status)
{
  pinMode(pinNumber, OUTPUT);
  digitalWrite(pinNumber, status);
}


void STOP()
{
  if (( ( digitalRead(2) ) == ( HIGH ) ))
  {
    returnPinAndBoolean(LED, HIGH);
  }
  else
  {
    returnPinAndBoolean(LED, LOW);
    LED = ( LED + 1 ) ;
    if (( ( LED ) > ( 8 ) ))
    {
      LED = 4 ;
    }
    returnPinAndBoolean(LED, HIGH);
    delay( Speed );
  }
}


void lightSpeedToggle()
{
  if (( ( digitalRead(12) ) == ( HIGH ) ))
  {
    Speed = 50 ;
  }
  else
  {
    Speed = 150 ;
  }
}


void setup()
{
  pinMode( 12 , INPUT);
  pinMode( 2 , INPUT);
  LED = 4 ;
  Speed = 100 ;

}

void loop()
{
  STOP();
  lightSpeedToggle();
}



