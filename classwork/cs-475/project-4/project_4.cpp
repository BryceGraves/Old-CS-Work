#include "project_4.h"

int main(int argc, char *argv[]) {
  double end_time, max_performance_simd, max_performance_non_simd,
      mega_mults_per_second, start_time;
  int array_size = ARRAY_SIZE, opt = 0, threads = NUM_THREADS,
      tries = NUM_TRIES, verbose = 0;

  while ((opt = getopt(argc, argv, "hvt:s:")) != -1) {
    switch (opt) {
      case 'h':
        fprintf(stderr, "Accepted command line arguments are h, v, and t.\n");
        return EXIT_SUCCESS;

      case 'v':
        ++verbose;
        break;

      case 't':
        threads = atoi(optarg);

        if (threads > 8 || threads < 0) {
          fprintf(stderr, "%s",
                  "Hey give me a thread count between 1 and 8 you dingus\n");
          return EXIT_FAILURE;
        }

        break;

      case 's':
        array_size = atoi(optarg);
        break;

      case '?':
        fprintf(stderr, "%s", "Thar be a illegal argument!\n");
        return EXIT_FAILURE;
    }
  }

  if (verbose) {
    fprintf(stderr, "Runtime Settings:\n\tThread Count: %d\n", threads);
  }

  omp_set_num_threads(threads);

  float *A = new float[array_size];
  float *B = new float[array_size];

  for (int n = 0; n < array_size; n++) {
    A[n] = 1.0;
    B[n] = 2.0;
  }

  end_time = max_performance_simd = max_performance_non_simd =
      mega_mults_per_second = start_time = -1.0;

  for (int t = 0; t < tries; t++) {
    start_time = omp_get_wtime();

    float total = 0.0;

#pragma omp parallel for default(none) shared(array_size, A, B) reduction(+ : total)
    for (int i = 0; i < array_size; i++) {
      total += A[i] * B[i];
    }

    end_time = omp_get_wtime();
    mega_mults_per_second =
        ((double)array_size / (end_time - start_time)) / 1000000.0;

    if (mega_mults_per_second > max_performance_non_simd) {
      max_performance_non_simd = mega_mults_per_second;
    }
  }

  for (int t = 0; t < tries; t++) {
    start_time = omp_get_wtime();

    float total = 0.0;

#pragma omp parallel default(none) shared(array_size, threads, A, B) reduction(+ : total)
    {
      int first = omp_get_thread_num() * (array_size / threads);
      total += simd_mul_sum(&A[first], &B[first], array_size / threads);
    }

    end_time = omp_get_wtime();
    mega_mults_per_second =
        ((double)array_size / (end_time - start_time)) / 1000000.0;

    if (mega_mults_per_second > max_performance_simd) {
      max_performance_simd = mega_mults_per_second;
    }
  }

  fprintf(stdout, "%d,%d,%.2lf\n", threads, array_size,
          max_performance_simd / max_performance_non_simd);

  delete[] A;
  delete[] B;

  return EXIT_SUCCESS;
}

float simd_mul_sum(float *a, float *b, int len) {
  float sum[4] = {0.0, 0.0, 0.0, 0.0};
  int limit = (len / SSE_WIDTH) * SSE_WIDTH;
  register float *pa = a;
  register float *pb = b;

  __m128 ss = _mm_loadu_ps(&sum[0]);
  for (int i = 0; i < limit; i += SSE_WIDTH) {
    ss = _mm_add_ps(ss, _mm_mul_ps(_mm_loadu_ps(pa), _mm_loadu_ps(pb)));
    pa += SSE_WIDTH;
    pb += SSE_WIDTH;
  }
  _mm_storeu_ps(&sum[0], ss);

  for (int i = limit; i < len; i++) {
    sum[0] += a[i] * b[i];
  }

  return sum[0] + sum[1] + sum[2] + sum[3];
}
