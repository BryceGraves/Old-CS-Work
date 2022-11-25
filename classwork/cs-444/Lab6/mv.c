#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define DIRSTR 128

int
ln(char *src, char *dest)
{
    int res = -1;
    if (link(src, dest) < 0) {
        // problem
        exit();
    } else {
        if (unlink(src) < 0) {
            // another problem
        } else {
            res = 0;
        }
    }
    return res;
}

int
main(int argc, char *argv[])
{
    struct stat st;
    char dirstr[DIRSTR];
    char *dest;
    int i;
    int res;
    
    if (argc < 3) {
        printf(2, "yerp\n");
        exit();
    }

    dest = argv[argc - 1];
    res = stat(dest, &st);

    if (res < 0) {
        ln(argv[1], dest);
    } else {
        switch(st.type) {
        case T_DIR:
            for (i = 1; i < (argc - 1); i++) {
                memset(dirstr, 0, DIRSTR);
                strcpy(dirstr, dest);
                dirstr[strlen(dirstr)] = '/';
                strcpy(&(dirstr[strlen(dirstr)]), argv[i]);
                ln(argv[i], dirstr);
            }
            break;
        case T_FILE:
            unlink(dest);
            ln(argv[1], dest);
            break;
        }
    }
    exit();
}

