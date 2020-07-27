#include "project-0.h"

int main(int argc, char *argv[]) {
  int opt = 0, tests = TEST_COUNT, verbose = 0;
  long long size = SIZE;

  // TODO: pull this out into a function
  while ((opt = getopt(argc, argv, "hvs:t:")) != -1) {
    switch (opt) {
      case 'h':
        fprintf(stderr,
                "Accepted command line arguments are h, v, s, and t.\n");
        return (0);

      case 'v':
        ++verbose;
        break;

      case 's':
        // not verifying input for this cause I am lazy right meow
        size = atoll(optarg) * THOUSAND;
        break;

      case 't':
        // not verifying input for this cause I am lazy right meow
        tests = atoi(optarg);
        break;

      case '?':
        fprintf(stderr, "%s", "Thar be a illegal argument!\n");
        return (1);
    }
  }

  if (verbose) {
    fprintf(stderr, "Initializing arrays with size: %lld\n", size);
  }

  // allocate the arrays
  float *A = new float[size];
  float *B = new float[size];
  float *C = new float[size];

  // inialize the arrays:
  for (long long i = 0; i < size; i++) {
    A[i] = 1.;
    B[i] = 2.;
    C[i] = 0.;
  }

  fprintf(stderr, "Starting %d thread test.\n", ONE_THREAD);
  omp_set_num_threads(ONE_THREAD);

  double single_threaded_result, quad_threaded_result,
      max_mults_per_second = 0.;

  for (int t = 0; t < tests; t++) {
    double start = omp_get_wtime();

#pragma omp parallel for
    for (long long i = 0; i < size; i++) {
      C[i] = multiply(A[i], B[i]);
    }

    double finish = omp_get_wtime();
    double current_mults_per_second =
        (double)size / (finish - start) / 1000000.;

    if (current_mults_per_second > max_mults_per_second)
      max_mults_per_second = current_mults_per_second;
  }

  single_threaded_result = max_mults_per_second;

  fprintf(stdout, "Single Thread Peak Performance: %8.2lf MegaMults/Sec\n",
          single_threaded_result);

  fprintf(stderr, "Starting %d thread test.\n", FOUR_THREADS);
  omp_set_num_threads(FOUR_THREADS);

  max_mults_per_second = 0.;

  // inialize the arrays:
  for (long long i = 0; i < size; i++) {
    A[i] = 1.;
    B[i] = 2.;
    C[i] = 0.;
  }

  for (int t = 0; t < tests; t++) {
    double start = omp_get_wtime();

#pragma omp parallel for
    for (long long i = 0; i < size; i++) {
      C[i] = multiply(A[i], B[i]);
    }

    double finish = omp_get_wtime();
    double current_mults_per_second =
        (double)size / (finish - start) / 1000000.;

    if (current_mults_per_second > max_mults_per_second)
      max_mults_per_second = current_mults_per_second;
  }

  quad_threaded_result = max_mults_per_second;

  fprintf(stdout, "Quad Thread Peak Performance: %8.2lf MegaMults/Sec\n",
          quad_threaded_result);

  fprintf(stdout, "Speedup: %8.2lf\n",
          quad_threaded_result / single_threaded_result);
  fprintf(stdout, "Parallel Fraction: %8.2lf\n",
          (4. / 3.) *
              (1. - (1. / (quad_threaded_result / single_threaded_result))));

  delete[] A;
  delete[] B;
  delete[] C;

  return 0;
}