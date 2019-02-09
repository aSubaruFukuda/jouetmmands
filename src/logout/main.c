#include <stdio.h>
#include <stdlib.h>
#include "my_logout.h"

int main(int argc, char *argv[]) {
	if (argc == 1) {
		exit(1);
	}
	while (--argc) {
		my_logout(*++argv);
	}
	return 0;
}
