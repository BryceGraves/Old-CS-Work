//Bryce Graves
//Homework 3: What a shocker

const int SEQUENCE_LENGTH = 6;
int firstLight[] =      {9, 10, 11};
int secondLight[] =     {10, 11, 9};
int lightOff[] =        {11, 9, 10}; 
int delays[] =          {50, 50, 50};

int firstVoltage = 0;
int secondVoltage = 0;


void setup()
{

         pinMode( 10 , OUTPUT);
         pinMode( 11 , OUTPUT);
         pinMode( 13 , OUTPUT);
         
}

void loop() {
  bringOnTheSun();  
}


void bringOnTheSun() {
for (int i = 0; i < SEQUENCE_LENGTH; ++i) {
    analogWrite( firstLight[i], ++firstVoltage);
    delay(delays[i]);
    analogWrite( secondLight[i], ++secondVoltage);
    delay(10);
    analogWrite( lightOff[i], 0);
    //analogWrite( LED[i], voltage[i]);

}
}
    

