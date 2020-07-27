#include "project-2.h"

int main(int argc, char *argv[]) {
  int node_count = 4, opt = 0, threads = NUM_THREADS, tries = NUM_TRIES,
      verbose = 0;

  while ((opt = getopt(argc, argv, "hvt:n:")) != -1) {
    switch (opt) {
      case 'h':
        fprintf(stderr,
                "Accepted command line arguments are h, v, t, and c.\n");
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

      case 'n':
        node_count = atoi(optarg);

        if (node_count < 1) {
          fprintf(stderr, "%s", "I need at least one node!\n");
          return EXIT_FAILURE;
        }

        break;

      case '?':
        fprintf(stderr, "%s", "Thar be a illegal argument!\n");
        return EXIT_FAILURE;
    }
  }

  if (verbose) {
    fprintf(stderr, "Runtime Settings:\n\tThread Count: %d\n\tNode Count: %d\n",
            threads, node_count);
  }

  // Set number of threads to use
  omp_set_num_threads(threads);

  double full_tile_area = (((XMAX - XMIN) / (double)(node_count - 1)) *
                           ((YMAX - YMIN) / (double)(node_count - 1)));

  double max_performance = 0.0;

  for (int t = 0; t < tries; t++) {
    double start_time = omp_get_wtime();

    double total_volume = 0.0;

#pragma omp parallel for collapse(2) default(none) shared(full_tile_area, node_count) reduction(+:total_volume)
    for (int iv = 0; iv < node_count; iv++) {
      for (int iu = 0; iu < node_count; iu++) {
        double available_tile_area = full_tile_area,
               current_height = Height(iu, iv, node_count);

        if (iu == 0 || iu == node_count - 1) {
          available_tile_area /= 2.0;
        }

        if (iv == 0 || iv == node_count - 1) {
          available_tile_area /= 2.0;
        }

        total_volume += available_tile_area * current_height;
      }
    }

    double end_time = omp_get_wtime();
    double mega_heights_per_second =
        ((double)(node_count * node_count) / (end_time - start_time)) /
        1000000.0;

    if (mega_heights_per_second > max_performance) {
      max_performance = mega_heights_per_second;
    }

    if (verbose) {
      fprintf(stderr, "Calculated Volume: %lf\n", total_volume * 2);
    }
  }

  fprintf(stdout, "%d,%d,%lf\n", threads, node_count, max_performance);

  return EXIT_SUCCESS;
}

double Height(int iu, int iv, int node_count) {
  double x = -1. + 2. * (double)iu / (double)(node_count - 1);  // -1. to +1.
  double y = -1. + 2. * (double)iv / (double)(node_count - 1);  // -1. to +1.

  double xn = pow(fabs(x), (double)N);
  double yn = pow(fabs(y), (double)N);
  double r = 1. - xn - yn;
  if (r < 0.) return 0.;
  double height = pow(1. - xn - yn, 1. / (double)N);
  return height;
}
