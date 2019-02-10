#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdlib.h>

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
	char fileType;
	struct stat fstatus;

	if ((dir_ptr = opendir(dirname)) == NULL) {
		fprintf(stderr, "ls1: cannot open %s\n", dirname);
	} else {
		while ((direntp = readdir(dir_ptr)) != NULL) {
			fname = direntp -> d_name;
			if (lflag_opt) {
				stat(fname, &fstatus);
				switch (fstatus.st_mode & S_IFMT) {
					case S_IFSOCK:
						fileType = 's';
						break;
					case S_IFLNK:
						fileType = 'l';
						break;
					case S_IFBLK:
						fileType = 'b';
						break;
					case S_IFCHR :
						fileType = 'c';
						break;
					case S_IFDIR :
						fileType = 'd';
						break;
					case S_IFIFO :
						fileType = 'p';
						break;
					case S_IFREG:
						fileType = '-';
						break;
				}
				printf("%c %s \n", fileType, fname);
			} else {
				printf("%s\n", fname);
			}
		}
		closedir(dir_ptr);
	}
}

