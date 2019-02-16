#include <stdio.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

char getFileType(mode_t st_mode) {
	mode_t typeBits;
	char fileType;

	typeBits = st_mode & S_IFMT;
	switch (typeBits) {
		case S_IFSOCK:
			fileType = 's';
			break;
		case S_IFLNK:
			fileType = 'l';
			break;
		case S_IFREG:
			fileType = '-';
			break;
		case S_IFBLK:
			fileType = 'b';
			break;
		case S_IFDIR:
			fileType = 'd';
			break;
		case S_IFCHR:
			fileType = 'c';
			break;
		case S_IFIFO:
			fileType = 'p';
			break;
	}
	return fileType;
}

char *getPermission(mode_t st_mode) {
	char *permission;
	permission = calloc(10, sizeof(char));

	permission[0] = (st_mode & S_IRUSR) ? '-' : 'r';
	permission[1] = (st_mode & S_IWUSR) ? '-' : 'w';
	permission[2] = (st_mode & S_IXUSR) ? '-' : 'x';
	permission[3] = (st_mode & S_IRGRP) ? '-' : 'r';
	permission[4] = (st_mode & S_IWGRP) ? '-' : 'w';
	permission[5] = (st_mode & S_IXGRP) ? '-' : 'x';
	permission[6] = (st_mode & S_IROTH) ? '-' : 'r';
	permission[7] = (st_mode & S_IWOTH) ? '-' : 'w';
	permission[8] = (st_mode & S_IXOTH) ? '-' : 'x';
	permission[9] = '\0';

	return permission;
}

void getUname(uid_t st_uid, char *user_buf) {
	struct passwd *pwd;
	if ((pwd = getpwuid(st_uid)) == NULL) {
		printf("error\n");
		perror("getpwuid error");
	} else {
		strcpy(user_buf, pwd->pw_name);
	}
}

void getGname(gid_t st_gid, char *group_buf) {
	struct group *grp;
	if ((grp = getgrgid(st_gid)) == NULL) {
		printf("error\n");
		perror("getgrgid error");
	} else {
		strcpy(group_buf, grp->gr_name);
	}
}

char *getModificationTime(time_t t) {
	return ctime(&t);
}
