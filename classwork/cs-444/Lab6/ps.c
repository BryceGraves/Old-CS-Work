#include "types.h"
#include "user.h"

int main(int argc, char **argv) {
  if (argc > 1) {
    detailed_cps();
  } else {
    cps();
  }
  exit();
}
