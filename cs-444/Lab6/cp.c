#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define BUFSIZE 512
#define DIRSTR 128

static char buf[BUFSIZE] = {'\0'};

void cp(char *, char *);

int
main(int argc, char *argv[])
{
    struct stat st;
    char *dest;
    int i;
    int res;
    char dirstr[DIRSTR];

    if (argc < 3) {
        // barf
        printf(2, "yeet\n");
        exit();
    }

    dest = argv[argc - 1];
    res = stat(dest, &st);

    if (res < 0) {
        // dest does not exist
        cp(dest, argv[1]);
    }
    else {
        switch (st.type) {
        case T_DIR:
            for (i = 1; i < (argc - 1); i++) {
                memset(dirstr, 0, DIRSTR);
                strcpy(dirstr, dest);
                dirstr[strlen(dirstr)] = '/';
                strcpy(&(dirstr[strlen(dirstr)]), argv[i]);
                cp(dirstr, argv[i]);
            }
            break;
        case T_FILE:
            cp(dest, argv[1]);
            break;
        default:
            printf(2, "barf\n");
            break;
        }
    }
    exit();
}

void
cp(char *oname, char *iname)
{
#ifndef TRUNC_FILE
    struct stat st;
#endif // TRUNC_FILE
    int n;
    int ofd;
    int ifd;
#ifndef TRUNC_FILE
    int res;
#endif // TRUNC_FILE
    int flags;

    if ((ifd = open(iname, O_RDONLY)) >= 0) {
#ifdef TRUNC_FILE
    flags = O_WRONLY | O_CREATE | O_TRUNC;
#else // TRUNC_FILE
        res = stat(oname, &st);
        if (res >= 0) {
            unlink(oname);
        }

        flags = O_WRONLY | O_CREATE;
#endif // TRUNC_FILE
        if ((ofd = open(oname, flags)) >= 0) {
            // for ( ; ((n = read(ifd, buf, BUFSIZE)) > 0) 
            //         && ((res = write(ofd, buf, n)) > 0; );
            // n = read(ifd, buf, BUFSIZE);
            n = read(ifd, buf, BUFSIZE);
            while (n > 0) {
                write(ofd, buf, n);
                n = read(ifd, buf, BUFSIZE);
            }
            close(ofd);
        }
        close(ifd);
    }
    else {
        printf(2, "yack attack\n");
        exit();
    }
}

