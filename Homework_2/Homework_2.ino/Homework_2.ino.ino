//Bryce Graves
//Homework 2: Rogue Lights

//Questions
//1. The library or IDE
//2. The LED lights are dim, but still light up
//3. When you do not define output for a pin digitalWrite enables the internal resister resulting in a dim light.

//https://drive.google.com/open?id=0B3GFnO1kTWZ4T2FPTXN6RGJxVE0

const int SEQUENCE_LENGTH = 9;
int sequence[] = {10, 8, 11, 4, 13, 8, 6, 9, 7};


void setup()
{
         pinMode( 4 , OUTPUT);
         pinMode( 5 , OUTPUT);
         pinMode( 6 , OUTPUT);
         pinMode( 7 , OUTPUT);
         pinMode( 8 , OUTPUT);
         pinMode( 9 , OUTPUT);
         pinMode( 10 , OUTPUT);
         pinMode( 11 , OUTPUT);
         pinMode( 13 , OUTPUT);
         
}

void loop() {
  for (int i = 0; i < SEQUENCE_LENGTH; ++i) {
    digitalWrite( sequence[i] , HIGH );
    delay( 250 );
    digitalWrite( sequence[i] , LOW );
    digitalWrite( sequence[i] , HIGH );
    delay( 500 );
    digitalWrite( sequence[i] , LOW );
    digitalWrite( sequence[i] , HIGH );
    delay( 100 );
    digitalWrite( sequence[i] , LOW );
    digitalWrite( sequence[i] , HIGH );
    delay( 50 );
    digitalWrite( sequence[i] , LOW );
  }
  
}
