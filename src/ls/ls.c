#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include "finfo.h"

void do_ls(char [], int);

int main(int argc, char *argv[]) {
	int opt;
	int lflag_opt = 0;
	while ((opt = getopt(argc, argv, "l")) != -1) {
		switch (opt) {
			case 'l':
				lflag_opt = 1;
				break;
			case '?':
				printf("TODO: help message\n");
				exit(1);
		}
	}
	if ((!lflag_opt && argc == 1) || (lflag_opt && argc == 2)) {
		do_ls(".", lflag_opt);
	} else {
		int i = optind;
		while (i < argc) {
			do_ls(argv[i++], lflag_opt);
		}
	}
}

void do_ls(char dirname[], int lflag_opt) {
	DIR *dir_ptr;
	struct dirent *direntp;
	char *fname;
	struct stat fstatus;
	char user[256];
	char group[256];
	char type;
	char *perm;
	char *mod_time;

	if ((dir_ptr = opendir(dirname)) == NULL) {
		fprintf(stderr, "ls1: cannot open %s\n", dirname);
	} else {
		while ((direntp = readdir(dir_ptr)) != NULL) {
			fname = direntp -> d_name;
			if (lflag_opt) {
				memset(user, '\0', sizeof(char) * 256);
				stat(fname, &fstatus);
				type = getFileType(fstatus.st_mode);
				perm = getPermission(fstatus.st_mode);
				getUname(fstatus.st_uid, user);
				getGname(fstatus.st_gid, group);
				mod_time = getModificationTime(fstatus.st_mtime);
				printf("%c%s %ld %s %s %12.12s %s\n", type, perm, fstatus.st_nlink, user, group, mod_time+4, fname);
				free(perm);
			} else {
				printf("%s\n", fname);
			}
		}
		closedir(dir_ptr);
	}
}
