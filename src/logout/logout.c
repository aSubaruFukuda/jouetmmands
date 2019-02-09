#include <fcntl.h>
#include <utmp.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>

int my_logout(char *line) {
	int fd;
	struct utmp rec;
	int len = sizeof(struct utmp);
	int retval = -1;
	time_t *tloc;

	printf("%s\n", UTMP_FILE);
	if ((fd = open(UTMP_FILE, O_RDWR)) == -1) {
		printf("open error\n");
		return -1;
	}
	while (read(fd, &rec, len) == len) {
		if (strncmp(rec.ut_line, line, sizeof(rec.ut_line)) == 0) {
			printf("aaa\n");
			rec.ut_type = DEAD_PROCESS;
			tloc = (time_t *)&rec.ut_tv.tv_sec;
			if (time(tloc) != -1) {
				if (lseek(fd, -len, SEEK_CUR) != -1) {
					if (write(fd, &rec, len) == len) {
						printf("bbb\n");
						retval = 0;
					}
				}
			}
			break;
		}
	}
	if (close(fd) == -1) {
		printf("close error\n");
		retval = -1;
	}
	return retval;
}
