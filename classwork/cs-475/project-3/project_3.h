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

#ifndef MONTHS_IN_YEAR
  #define MONTHS_IN_YEAR 12
#endif  // !MONTHS_IN_YEAR

#ifndef SIMULATION_LENGTH
  #define SIMULATION_LENGTH 6 * MONTHS_IN_YEAR
#endif  // !SIMULATION_LENGTH

/* ------- End of personal ease of use declarations ------- */

// setting the number of threads:
#ifndef NUM_THREADS
  #define NUM_THREADS 4
#endif  // !NUM_THREADS

// how many tries to discover the maximum performance:
#ifndef NUM_TRIES
  #define NUM_TRIES 10
#endif  // !NUM_TRIES

/* ------ sad globals ------ */

int NowMonth = 0;  // 0 - 11

float NowHeight = 1.0;  // grain height in inches
int NowNumDeer = 1;     // number of deer in the current population
float NowPrecip = 0.0;  // inches of rain per month
float NowTemp = 0.0;    // temperature this
int NowNumWolves = 1;

unsigned int seed = 1;

/* ---- sad globals end ---- */

/* ------ sad constants ------ */

const float GRAIN_GROWS_PER_MONTH = 9.0;
const float ONE_DEER_EATS_PER_MONTH = 1.0;

const float AVG_PRECIP_PER_MONTH = 7.0;  // average
const float AMP_PRECIP_PER_MONTH = 6.0;  // plus or minus
const float RANDOM_PRECIP = 2.0;         // plus or minus noise

const float AVG_TEMP = 60.0;     // average
const float AMP_TEMP = 20.0;     // plus or minus
const float RANDOM_TEMP = 10.0;  // plus or minus noise

const float MIDTEMP = 40.0;
const float MIDPRECIP = 10.0;

/* ---- sad constants end ---- */

#ifndef _OPENMP
  #error OpenMP not supported!
#endif  // !_OPENMP

float calculate_angle(int);
float calculate_precip(float, unsigned int*);
float calculate_precip(float);
float calculate_precip_factor(float);
float calculate_temp(float, unsigned int*);
float calculate_temp(float);
float calculate_temp_factor(float);
void grain_deer(void);
void grain(void);
void watcher(void);
void wolves(void);

float Ranf(unsigned int*, float, float);
int Ranf(unsigned int*, int, int);

template <typename T>
T Square(T x) {
  return x * x;
}
