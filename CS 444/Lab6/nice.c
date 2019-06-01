#include "types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
    if (argc < 3) {
        printf(2, "not enough args\n");
    } else {
        renice(atoi(argv[1]), getpid());
        exec(argv[2], &(argv[2]));
    }
    exit();
}

