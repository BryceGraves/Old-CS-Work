#define _USE_MATH_DEFINES
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include <iostream>

/* ------- Personal ease of use declarations ------- */

#ifndef TRUE
  #define TRUE 1
#endif  // TRUE
#ifndef FALSE
  #define FALSE 0
#endif  // FALSE

// setting the number of threads:
#ifndef THOUSAND
  #define THOUSAND 1000
#endif

// setting the number of threads:
#ifndef MILLLION
  #define MILLLION THOUSAND* THOUSAND
#endif

/* ------- End of personal ease of use declarations ------- */

// setting the number of threads:
#ifndef NUMT
  #define NUMT 1
#endif

// setting the number of trials in the monte carlo simulation:
#ifndef NUMTRIALS
  #define NUMTRIALS MILLLION
#endif

// how many tries to discover the maximum performance:
#ifndef NUMTRIES
  #define NUMTRIES 10
#endif

// ranges for the random numbers:
const float XCMIN = -1.0;
const float XCMAX = 1.0;
const float YCMIN = 0.0;
const float YCMAX = 2.0;
const float RMIN = 0.5;
const float RMAX = 2.0;

// function prototypes:
float Ranf(float, float);
int Ranf(int, int);
void TimeOfDaySeed();

#ifndef _OPENMP
  #error OpenMP not supported!
#endif  // !_OPENMP
