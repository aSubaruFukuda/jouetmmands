#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utmplib.h"

#define SHOWHOST

void show_info(struct utmp *);
void showtime(int32_t);

int main() {
	int utmpfd;
	struct utmp *record;

	if ((utmpfd = utmp_open(UTMP_FILE)) == -1) {
		perror(UTMP_FILE);
		exit(1);
	}

	while ((record = utmp_next()) != NULL) {
		show_info(record);
	}
	utmp_close();
	return 0;
}

void show_info(struct utmp *utbufp) {
	if (utbufp->ut_type != USER_PROCESS) {
		return;
	}
	printf("%-8.8s", utbufp->ut_user);
	printf(" ");
	printf("%-8.8s", utbufp->ut_line);
	printf(" ");
	showtime(utbufp->ut_tv.tv_sec);
#ifdef SHOWHOST
	printf("(%s)", utbufp->ut_host);
#endif
	printf("\n");
}

void showtime(int32_t timeval) {
	char *cp;
	time_t tmv = (time_t)timeval;
	cp = ctime(&tmv);
	printf("%12.12s",cp+4);
}
