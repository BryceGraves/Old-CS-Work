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
#endif  // !TRUE
#ifndef FALSE
  #define FALSE 0
#endif  // !FALSE

#ifndef THOUSAND
  #define THOUSAND 1000
#endif  // !THOUSAND

#ifndef MILLLION
  #define MILLLION THOUSAND* THOUSAND
#endif  // !MILLLION

// Not sure if using these is best practice
#ifndef INVALID_THREAD_COUNT
  #define INVALID_THREAD_COUNT 2
#endif  // !INVALID_THREAD_COUNT

#ifndef INVALID_FLAG
  #define INVALID_FLAG 3
#endif  // !INVALID_FLAG

/* ------- End of personal ease of use declarations ------- */

// setting the number of threads:
#ifndef NUM_THREADS
  #define NUM_THREADS 1
#endif  // !NUM_THREADS

// how many tries to discover the maximum performance:
#ifndef NUM_TRIES
  #define NUM_TRIES 10
#endif  // !NUM_TRIES

#ifndef N
  #define N 4
#endif  // !N

const double XMIN = -1.0;
const double XMAX = 1.0;
const double YMIN = -1.0;
const double YMAX = 1.0;

// function prototypes:
double Height(int, int, int);

#ifndef _OPENMP
  #error OpenMP not supported!
#endif  // !_OPENMP
