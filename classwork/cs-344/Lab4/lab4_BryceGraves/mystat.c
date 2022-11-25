#include <pwd.h>
#include <grp.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[]) {
  int i, chmodValue;
  char permissions[11], accessDate[40], modificationDate[40], changeDate[40], fileType[100], fileName[100], linkedFile[100];
  struct group  *groupStuffs;
  struct passwd *userStuffs;
  struct stat fileStat;

  for (i = 1; i < argc; i++) {
    lstat(argv[i], &fileStat);

    strcpy(fileName, argv[i]);

    userStuffs = getpwuid(fileStat.st_uid);
    groupStuffs = getgrgid(fileStat.st_gid);

    strftime(accessDate, 40, "%Y-%m-%d %H:%M:%S %z (%Z) %a", localtime(&fileStat.st_atime));
    strftime(modificationDate, 40, "%Y-%m-%d %H:%M:%S %z (%Z) %a", localtime(&fileStat.st_mtime));
    strftime(changeDate, 40, "%Y-%m-%d %H:%M:%S %z (%Z) %a", localtime(&fileStat.st_ctime));

    switch (fileStat.st_mode & S_IFMT) {
      case S_IFREG:
        strcpy(fileType, "regular file");
        permissions[0] = '-';
        break;
      case S_IFDIR:
        strcpy(fileType, "directory");
        permissions[0] = 'd';
        break;
      case S_IFCHR:
        strcpy(fileType, "character device");
        permissions[0] = 'c';
        break;
      case S_IFBLK:
        strcpy(fileType, "block device");
        permissions[0] = 'b';
        break;
      case S_IFLNK:
        strcpy(fileType, "Symbolic Link -> ");
        readlink(argv[i], linkedFile, fileStat.st_size + 1);
        strcat(fileType, linkedFile);
        permissions[0] = 'l';
        break;
      case S_IFIFO:
        strcpy(fileType, "FIFO/pipe");
        permissions[0] = 'p';
        break;
      case S_IFSOCK:
        strcpy(fileType, "socket");
        permissions[0] = 's';
        break;
      default:
        strcpy(fileType, "unknown");
     }

    permissions[1] = (fileStat.st_mode & S_IRUSR) ? 'r' : '-';
    permissions[2] = (fileStat.st_mode & S_IWUSR) ? 'w' : '-';
    permissions[3] = (fileStat.st_mode & S_IXUSR) ? 'x' : '-';
    permissions[4] = (fileStat.st_mode & S_IRGRP) ? 'r' : '-';
    permissions[5] = (fileStat.st_mode & S_IWGRP) ? 'w' : '-';
    permissions[6] = (fileStat.st_mode & S_IXGRP) ? 'x' : '-';
    permissions[7] = (fileStat.st_mode & S_IROTH) ? 'r' : '-';
    permissions[8] = (fileStat.st_mode & S_IWOTH) ? 'w' : '-';
    permissions[9] = (fileStat.st_mode & S_IXOTH) ? 'x' : '-';
    permissions[10] = '\0';

    chmodValue = fileStat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);

    printf(\
      "File: %s\n\
      File Type: %s\n\
      Device ID Number: %lu\n\
      I-Node Number: %lu\n\
      Mode: %s    (%o in octal)\n\
      Link Count: %lu\n\
      Owner ID: %s    (UID = %d)\n\
      Group ID: %s    (GID = %d)\n\
      Preferred I/O Block Size: %ld Bytes\n\
      File Size: %ld Bytes\n\
      Blocks Alllocated: %ld\n\
      Last File Access: %ld (Seconds Since the EPOCH)\n\
      Last File Modification: %ld (Seconds Since the EPOCH)\n\
      Last File Status Change: %ld (Seconds Since the EPOCH)\n\
      Last File Access: %s (local)\n\
      Last File Modification: %s (local)\n\
      Last File Status Change: %s (local)\n",\
      fileName, fileType, fileStat.st_dev, fileStat.st_ino, permissions, chmodValue,\
      fileStat.st_nlink, userStuffs->pw_name, fileStat.st_uid,\
      groupStuffs->gr_name, fileStat.st_gid, fileStat.st_blksize, fileStat.st_size,\
      fileStat.st_blocks, fileStat.st_atime, fileStat.st_mtime, fileStat.st_ctime,\
      accessDate, modificationDate, changeDate);
  }

  return(EXIT_SUCCESS);
}
