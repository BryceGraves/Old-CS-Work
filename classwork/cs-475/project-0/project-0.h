#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>

#define ONE_THREAD 1
#define FOUR_THREADS 4
#define THOUSAND 1000
#define SIZE 16 * THOUSAND
#define TEST_COUNT 5

#define multiply(_a, _b) (_a * _b)

using namespace std;

#ifndef _OPENMP
  #error OpenMP not supported!
#endif  // !_OPENMP