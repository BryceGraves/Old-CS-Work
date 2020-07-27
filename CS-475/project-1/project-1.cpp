#include "project-1.h"

int main(int argc, char *argv[]) {
  int opt = 0, threads = NUMT, tries = NUMTRIES, verbose = 0;

  long long trials = NUMTRIALS;

  while ((opt = getopt(argc, argv, "hvt:c:")) != -1) {
    switch (opt) {
      case 'h':
        fprintf(stderr,
                "Accepted command line arguments are h, v, t, and c.\n");
        return (0);

      case 'v':
        ++verbose;
        break;

      case 't':
        // not verifying input for this cause I am lazy right meow
        threads = atoi(optarg);
        break;

      case 'c':
        // not verifying input for this cause I am lazy right meow
        trials = atoll(optarg) * MILLLION;
        break;

      case '?':
        fprintf(stderr, "%s", "Thar be a illegal argument!\n");
        return (1);
    }
  }

  float tn = tan((M_PI / 180.) * 30.);
  TimeOfDaySeed();  // seed the random number generator

  // set the number of threads to use in the for-loop:`
  omp_set_num_threads(threads);

  // better to define these here so that the rand() calls don't get into the
  // thread timing:
  float *xcs = new float[trials];
  float *ycs = new float[trials];
  float *rs = new float[trials];

  // fill the random-value arrays:
  for (int n = 0; n < trials; n++) {
    xcs[n] = Ranf(XCMIN, XCMAX);
    ycs[n] = Ranf(YCMIN, YCMAX);
    rs[n] = Ranf(RMIN, RMAX);
  }

  // get ready to record the maximum performance and the probability:
  float maxPerformance = 0.;  // must be declared outside the NUMTRIES loop
  float currentProb;          // must be declared outside the NUMTRIES loop

  // looking for the maximum performance:
  for (int t = 0; t < tries; t++) {
    double time0 = omp_get_wtime();

    int numHits = 0;
#pragma omp parallel for default(none) shared(xcs, ycs, rs, tn, trials) reduction(+:numHits)
    for (int n = 0; n < trials; n++) {
      // randomize the location and radius of the circle:
      float xc = xcs[n];
      float yc = ycs[n];
      float r = rs[n];

      // solve for the intersection using the quadratic formula:
      float a = 1. + tn * tn;
      float b = -2. * (xc + yc * tn);
      float c = xc * xc + yc * yc - r * r;
      float d = b * b - 4. * a * c;

      if (d <= 0) continue;

      // hits the circle:
      // get the first intersection:
      d = sqrt(d);
      float t1 = (-b + d) / (2. * a);  // time to intersect the circle
      float t2 = (-b - d) / (2. * a);  // time to intersect the circle
      float tmin = t1 < t2 ? t1 : t2;  // only care about the first intersection

      if (tmin <= 0) continue;

      // where does it intersect the circle?
      float xcir = tmin;
      float ycir = tmin * tn;

      // get the unitized normal vector at the point of intersection:
      float nx = xcir - xc;
      float ny = ycir - yc;
      float nxy = sqrt(nx * nx + ny * ny);
      nx /= nxy;  // unit vector
      ny /= nxy;  // unit vector

      // get the unitized incoming vector:
      float inx = xcir - 0.;
      float iny = ycir - 0.;
      float in = sqrt(inx * inx + iny * iny);
      inx /= in;  // unit vector
      iny /= in;  // unit vector

      // get the outgoing (bounced) vector:
      float dot = inx * nx + iny * ny;
      float outx =
          inx - 2. * nx * dot;  // angle of reflection = angle of incidence`
      float outy =
          iny - 2. * ny * dot;  // angle of reflection = angle of incidence`

      // find out if it hits the infinite plate:
      float tt = (0. - ycir) / outy;

      if (tt <= 0) continue;

      ++numHits;
    }
    double time1 = omp_get_wtime();
    double megaTrialsPerSecond = (double)trials / (time1 - time0) / 1000000.;
    if (megaTrialsPerSecond > maxPerformance)
      maxPerformance = megaTrialsPerSecond;
    currentProb = (float)numHits / (float)trials;
  }

  // Output results
  printf("%d,%lld,%f,%f\n", threads, trials, currentProb, maxPerformance);

  // Clean up
  delete[] xcs;
  delete[] ycs;
  delete[] rs;
}

float Ranf(float low, float high) {
  float r = (float)rand();        // 0 - RAND_MAX
  float t = r / (float)RAND_MAX;  // 0. - 1.

  return low + t * (high - low);
}

int Ranf(int ilow, int ihigh) {
  float low = (float)ilow;
  float high = ceil((float)ihigh);

  return (int)Ranf(low, high);
}

void TimeOfDaySeed() {
  struct tm y2k = {0};
  y2k.tm_hour = 0;
  y2k.tm_min = 0;
  y2k.tm_sec = 0;
  y2k.tm_year = 100;
  y2k.tm_mon = 0;
  y2k.tm_mday = 1;

  time_t timer;
  time(&timer);
  double seconds = difftime(timer, mktime(&y2k));
  unsigned int seed = (unsigned int)(1000. * seconds);  // milliseconds
  srand(seed);
}