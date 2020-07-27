#define _USE_MATH_DEFINES
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <xmmintrin.h>

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
  #define MILLLION THOUSAND *THOUSAND
#endif  // !MILLLION

// Not sure if using these is best practice
#ifndef INVALID_THREAD_COUNT
  #define INVALID_THREAD_COUNT 2
#endif  // !INVALID_THREAD_COUNT

#ifndef INVALID_FLAG
  #define INVALID_FLAG 3
#endif  // !INVALID_FLAG

/* ------- End of personal ease of use declarations ------- */

#ifndef ARRAY_SIZE
  #define ARRAY_SIZE THOUSAND
#endif  // !ARRAY_SIZE

#ifndef NUM_THREADS
  #define NUM_THREADS 1
#endif  // !NUM_THREADS

#ifndef NUM_TRIES
  #define NUM_TRIES 10
#endif  // !NUM_TRIES

#ifndef SSE_WIDTH
  #define SSE_WIDTH 4
#endif  // !SSE_WIDTH

/* ------ sad globals ------ */

/* ---- sad globals end ---- */

/* ------ sad constants ------ */

/* ---- sad constants end ---- */

#ifndef _OPENMP
  #error OpenMP not supported!
#endif  // !_OPENMP

float simd_mul_sum(float *, float *, int);
