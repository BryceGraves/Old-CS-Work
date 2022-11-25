#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <libgen.h>

#include <pthread.h>

#ifndef TRUE
# define TRUE 1
#endif // TRUE
#ifndef FALSE
# define FALSE 0
#endif // FALSE

#define COMPACT_PRINT "%d "
#define PRETTY_PRINT "%12d "

typedef struct vector_s {
  char *file_name;
  int32_t size;

  int32_t *data;
} vector_t;

typedef struct sum_s {
  int32_t sum;

  pthread_mutex_t lock;
} sum_t;

typedef struct dot_prod_s {
  vector_t *a;
  vector_t *b;

  sum_t sum;
} dot_prod_t;

#define DEFAULT_THREAD_COUNT 1
#define MICROSECONDS_PER_SECOND 1000000.0D
#define COMMAND_ARGS "vha:b:t:Ss"

short serialOnly = FALSE;
short isVerbose = 0;
char *printFormat = COMPACT_PRINT;
long numThreads = DEFAULT_THREAD_COUNT;
short itsShowTime = TRUE;
short runWithTheBigDogs = FALSE;

dot_prod_t dot_prod;

void read_file(vector_t *vector);
void free_vector(vector_t *vector);
void *goThreadDaddy(void *arg);
void *read_fileThread(void *arg);

int main(int argc, char *argv[]) {
  vector_t *a = NULL;
  vector_t *b = NULL;

  struct timeval tv0;
  struct timeval tv1;
  struct timeval tv2;
  struct timeval tv3;
  struct timeval tv4;

  gettimeofday (&tv0, NULL);
  a = calloc(1, sizeof(vector_t));
  b = calloc(1, sizeof(vector_t));
  dot_prod.a = a;
  dot_prod.b = b;

{
  int c;

  // v - verbose
  // h - help
  // a - left vector - no default
  // b - right vector - no default
  // t - thread count
  // S - serial, no thread stuff at all
  // s - don't collect and show timing results
  while ((c = getopt(argc, argv, COMMAND_ARGS)) != -1) {
    switch (c) {
      case 'v':
        isVerbose++;
        break;
      case 'h':
        printf("%s %s\n", basename(argv[0]), COMMAND_ARGS);
        exit(EXIT_SUCCESS);
        break;
      case 'a':
        a->file_name = optarg;
        break;
      case 'b':
        b->file_name = optarg;
        break;
      case 't':
        numThreads = atoi(optarg);
        break;
      case 'S':
        serialOnly = TRUE;
        break;
      case 's':
        itsShowTime = !itsShowTime;
        break;
      default:
        // oops
        break;
      }
    }
  }

  if (NULL == a->file_name || NULL == b->file_name) {
    fprintf(stderr, "*** You must provide file names for both the "
            "a and b vector files ***\n");
    exit(1);
  }

  gettimeofday (&tv1, NULL);
  if (serialOnly) {
    int32_t i = 0;
    int32_t sum = 0;

    numThreads = 0;
    read_file(a);
    read_file(b);

    gettimeofday (&tv2, NULL);

    if (a->size == b->size) {
      // https://en.wikipedia.org/wiki/Dot_product
      // https://www.mathsisfun.com/algebra/vectors-dot-product.html
      // https://www.toppr.com/bytes/dot-product-of-two-vectors/
      gettimeofday (&tv3, NULL);
      for (i = 0, sum = 0; i < a->size; i++) {
          sum += a->data[i] * b->data[i];
      }
      dot_prod.sum.sum = sum;
    } else {
      fprintf(stderr, "*** the vectors must be the same size\n");
      exit(2);
    }
  } else {
    pthread_t *wthreads = NULL;
    long tid = 0;

    if (runWithTheBigDogs) {
      pthread_t rthreads[2] = {0};

      pthread_create(&rthreads[0], NULL, read_fileThread, a);
      pthread_create(&rthreads[1], NULL, read_fileThread, b);

      pthread_join(rthreads[0], NULL);
      pthread_join(rthreads[1], NULL);
    } else {
      read_file(a);
      read_file(b);
    }

    gettimeofday (&tv2, NULL);

    if (a->size == b->size) {
      gettimeofday (&tv3, NULL);
      wthreads = calloc(numThreads, sizeof(pthread_t));

      pthread_mutex_init(&dot_prod.sum.lock, NULL);

      for (tid = 0; tid < numThreads; tid++) {
        if (isVerbose > 1) {
          fprintf(stderr, "verbose: creating thread %ld\n", tid);
        }
        pthread_create(&wthreads[tid], NULL, goThreadDaddy, (void *) tid);
      }
      for (tid = 0; tid < numThreads; tid++) {
        pthread_join(wthreads[tid], NULL);
      }
      pthread_mutex_destroy(&dot_prod.sum.lock);
    } else {
      fprintf(stderr, "*** the vectors must be the same size\n");
      exit(3);
    }
  }
  gettimeofday (&tv3, NULL);
  printf("dot prod = %d\n", dot_prod.sum.sum);

  free_vector(a);
  free_vector(b);

  gettimeofday (&tv4, NULL);

  if (itsShowTime > 0) {
    double read_time =
        (((double) (tv2.tv_usec - tv1.tv_usec)) / MICROSECONDS_PER_SECOND)
        + ((double) (tv2.tv_sec - tv1.tv_sec));
    double mult_time =
        (((double) (tv3.tv_usec - tv2.tv_usec)) / MICROSECONDS_PER_SECOND)
        + ((double) (tv3.tv_sec - tv2.tv_sec));
    double total_time =
        (((double) (tv4.tv_usec - tv0.tv_usec)) / MICROSECONDS_PER_SECOND)
        + ((double) (tv4.tv_sec - tv0.tv_sec));

    fprintf(stderr, "%ld %lf %lf %lf\n"
            , numThreads, total_time, mult_time, read_time);
  }

  pthread_exit(EXIT_SUCCESS);
  //return EXIT_SUCCESS;
}

void *goThreadDaddy(void *arg) {
  long tid = (long) arg;
  int32_t sum = 0;
  int32_t i = 0;

  for (i = tid, sum = 0; i < dot_prod.a->size; i += numThreads) {
    sum += dot_prod.a->data[i] * dot_prod.b->data[i];
  }

  pthread_mutex_lock(&dot_prod.sum.lock);
  dot_prod.sum.sum += sum;
  pthread_mutex_unlock(&dot_prod.sum.lock);

  pthread_exit(EXIT_SUCCESS);
}

void *read_fileThread(void *arg) {
  vector_t *vector = (vector_t *) arg;

  read_file(vector);

  pthread_exit(EXIT_SUCCESS);
}

void read_file(vector_t *vector) {
  FILE *file = NULL;
  char *dot = strrchr(vector->file_name, '.');
  short inputFileZipped = FALSE;

  inputFileZipped = strcmp(dot, ".gz") == 0;
  if (inputFileZipped) {
    char cmd[200];

    sprintf(cmd, "gunzip -c %s", vector->file_name);
    file = popen(cmd, "r");
  }
  else {
    file = fopen(vector->file_name, "r");
  }
  if (NULL == file) {
    perror("count open input file");
    fprintf(stderr, "*** failed to open input file '%s' ***\n", vector->file_name);
    exit(4);
  }

  fscanf(file, "%d", &vector->size);
  {
    int32_t col = 0;

    vector->data = calloc(vector->size, sizeof(int32_t));
    for (col = 0; col < vector->size; col++) {
      fscanf(file, COMPACT_PRINT, &(vector->data[col]));
    }
  }
  if (inputFileZipped) {
    pclose(file);
  } else {
    fclose(file);
  }

  if (isVerbose > 2) {
    int32_t col = 0;

    fprintf(stderr,  "size: %d\n", vector->size);
    for (col = 0; col < vector->size; col++) {
        fprintf(stderr, COMPACT_PRINT, vector->data[col]);
    }
    fprintf(stderr, "\n");
  }
}

void free_vector(vector_t *vector) {
  free(vector->data);
  free(vector);
}
