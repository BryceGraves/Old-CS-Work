#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    if (argc < 2) {
        printf(2, "barf");
        exit();
    }

    debug(atoi(argv[1]));
    exit();
}

