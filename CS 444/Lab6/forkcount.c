#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"

int
main(int argc, char *argv[])
{
    int fc = 0;

    fc = forkcount();
    printf(1, "forkcount: %d\n", fc);
    exit();
}

