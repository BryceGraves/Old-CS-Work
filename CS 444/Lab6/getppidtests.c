#include "types.h"
#include "user.h"

int
main(int argc, char **argv)
{
#ifdef GETPPID
    int ppid;
    
    ppid = getppid();
    printf(1, "ppid %d\n", ppid);

#endif // GETPPID
    exit();
}

