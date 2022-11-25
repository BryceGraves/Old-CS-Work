#include "types.h"
#include "stat.h"
#include "user.h"
 
int main(int argc, char *argv[]) {
  if(argc < 3){
    printf(2, "Usage: nice <nice_value> <program>\n");
    exit();
  }

  renice(getpid(), atoi(argv[1]));
  exec(argv[2], &argv[2]);
  exit();
}