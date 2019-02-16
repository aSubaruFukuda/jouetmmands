#include <time.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

char getFileType(mode_t);
char *getPermission(mode_t);
void getUname(uid_t, char *);
void getGname(gid_t, char *);
char *getModificationTime(time_t t);
