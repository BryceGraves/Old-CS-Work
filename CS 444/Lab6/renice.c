#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    int i = 0;

    for (i = 2; i < argc; ++i) {
        renice(atoi(argv[1]), atoi(argv[i]));
    }
    exit();
}

