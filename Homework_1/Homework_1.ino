// Bryce Graves
// Homework 1: Blink like "Phrase"

void setup()
{
  pinMode( 13 , OUTPUT);
}

void loop()
{
  //Nin_ten_do
  for (int i = 0; i < 3; ++i) {
    digitalWrite( 13 , HIGH );
    delay( 100 );
    digitalWrite( 13 , LOW );
    delay( 250 );
  }
  //Switch
  digitalWrite( 13 , HIGH );
  delay( 100 );
  digitalWrite( 13 , LOW );
  delay( 600 );

  //Hype
  digitalWrite( 13 , HIGH );
  delay( 100 );
  digitalWrite( 13 , LOW );
  delay( 1000 );
}


