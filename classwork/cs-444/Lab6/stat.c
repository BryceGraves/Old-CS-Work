#include "types.h"
#include "stat.h"
#include "user.h"

char *
filetype(int sttype)
{
    static char ftype[20];

    switch(sttype) {
    case T_DIR:
        strcpy(ftype, "directory");
        break;
    case T_FILE:
        strcpy(ftype, "file");
        break;
    case T_DEV:
        strcpy(ftype, "device");
        break;
    default:
        strcpy(ftype, "wtf");
        break;
    }
    return ftype;
}

int
main(int argc, char *argv[])
{
    struct stat st;
    int i;
    int rez;

    for (i = 1; i < argc; i++) {
        rez = stat(argv[i], &st);
        if (rez < 0) {
            printf(2, "barf\n");
        } else {
            printf(1, "name: %s\n type: %s\n links: %d\n inode: %d\n size: %d\n",
                    argv[i], filetype(st.type), st.nlink, st.ino, st.size);
        }
    }
    exit();
}

