#include "types.h"
#include "stat.h"
#include "user.h"
 
int main(int argc, char *argv[]) {
  int i, nice = atoi(argv[1]);

  if(argc < 3){
    printf(2, "Usage: nice <nice_value> <pids>\n");
    exit();
  }

  for(i = 2; i < argc; i++) {
    if (renice(atoi(argv[i]), nice) != 0) {
      printf(2, "Something went wrong\n");
      exit();
    }
  }

  exit();
}