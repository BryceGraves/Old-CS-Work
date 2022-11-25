#include "project_3.h"

int main(int argc, char *argv[]) {
  seed = strtoul(argv[1], 0L, 10);

  omp_set_num_threads(NUM_THREADS);  // same as # of sections
#pragma omp parallel sections default(none)
  {
#pragma omp section
    { grain_deer(); }

#pragma omp section
    { grain(); }

#pragma omp section
    { watcher(); }

#pragma omp section
    { wolves(); }
  }

  return EXIT_SUCCESS;
}

float calculate_angle(int current_month) {
  return (30.0 * (float)current_month + 15.0) * (M_PI / 180.0);
}

float calculate_precip(float angle, unsigned int *seed) {
  float calculated_precip =
      calculate_precip(angle) + Ranf(seed, -RANDOM_PRECIP, RANDOM_PRECIP);
  return calculated_precip < 0.0 ? 0.0 : calculated_precip;
}

float calculate_precip(float angle) {
  return AVG_PRECIP_PER_MONTH + AMP_PRECIP_PER_MONTH * sin(angle);
}

float calculate_precip_factor(float precip) {
  return exp(-Square((precip - MIDPRECIP) / 10.0));
}

float calculate_temp(float angle, unsigned int *seed) {
  return calculate_temp(angle) + Ranf(seed, -RANDOM_TEMP, RANDOM_TEMP);
}

float calculate_temp(float angle) { return AVG_TEMP - AMP_TEMP * cos(angle); }

float calculate_temp_factor(float temp) {
  return exp(-Square((temp - MIDTEMP) / 10.0));
}

void grain_deer() {
  while (NowMonth < SIMULATION_LENGTH) {
    // Compute
    float nextHeight = NowHeight;
    int nextNumDeer = NowNumDeer;

    nextNumDeer < nextHeight ? ++nextNumDeer : --nextNumDeer;
#pragma omp barrier

    // Assign
    NowNumDeer = nextNumDeer;
#pragma omp barrier

    // Results
#pragma omp barrier
  }
}

void grain() {
  while (NowMonth < SIMULATION_LENGTH) {
    // Compute
    float angle = calculate_angle(NowMonth);
    float nextHeight = NowHeight, nextPrecip = calculate_precip(angle, &seed),
          nextTemp = calculate_temp(angle, &seed);
    int nextNumDeer = NowNumDeer;

    nextHeight += calculate_temp_factor(nextTemp) *
                  calculate_precip_factor(nextPrecip) * GRAIN_GROWS_PER_MONTH;
    nextHeight -= (float)nextNumDeer * ONE_DEER_EATS_PER_MONTH;

    if (nextHeight < 0.0) {
      nextHeight = 0.0;
    }
#pragma omp barrier

    // Assign
    NowHeight = nextHeight;
    NowPrecip = nextPrecip;
    NowTemp = nextTemp;
#pragma omp barrier

    // Results
#pragma omp barrier
  }
}

void watcher() {
  while (NowMonth < SIMULATION_LENGTH) {
    // Compute
#pragma omp barrier

    // Assign
#pragma omp barrier
    int tempWolfCount = 0;

    if (NowMonth >= SIMULATION_LENGTH / 2) {
      tempWolfCount = NowNumWolves;
    }

    // Results
    fprintf(stdout, "%d,%lf,%d,%d,%lf,%lf\n", NowMonth + 1, NowHeight * 2.54,
            NowNumDeer, tempWolfCount, NowPrecip, (5.0 / 9.0) * (NowTemp - 32));
    ++NowMonth;
#pragma omp barrier
  }
}

void wolves() {
  while (NowMonth < SIMULATION_LENGTH) {
    // Compute
    int nextNumDeer = NowNumDeer, nextNumWolves = NowNumWolves;

    if (NowMonth >= SIMULATION_LENGTH / 2) {
      if (nextNumDeer > nextNumWolves) {
        --nextNumDeer;
        ++nextNumWolves;
      } else {
        ++nextNumDeer;
        --nextNumWolves;
      }
    }
#pragma omp barrier

    // Assign
    if (NowMonth >= SIMULATION_LENGTH / 2) {
      NowNumDeer = nextNumDeer;
      NowNumWolves = nextNumWolves;
    }
#pragma omp barrier

    // Results
#pragma omp barrier
  }
}

float Ranf(unsigned int *seedp, const float low, const float high) {
  float r = (float)rand_r(seedp);  // 0 - RAND_MAX

  return (low + r * (high - low) / (float)RAND_MAX);
}

int Ranf(unsigned int *seedp, int ilow, int ihigh) {
  float low = (float)ilow;
  float high = (float)ihigh + 0.9999f;

  return (int)(Ranf(seedp, low, high));
}
