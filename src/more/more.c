#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/fcntl.h>
#include <sys/ioctl.h>

void do_more(FILE *fp);
char see_more(void);
void set_cr_noecho_mode(int);
void tty_mode(int, int);
int printFileNameFlg = 0;
struct winsize ws;

int main(int argc, char *argv[]) {
	FILE *fp;
	if (argc == 1) {
		fprintf(stderr, "more: bad usage\nTry 'more --help' for more information.\n");
  }
	else {
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws) == -1) {
      perror("cannot get the size of terminal window");
      exit(1);
    }
    if (argc > 2) {
      printFileNameFlg = 1;
    }
		while (--argc){
      if (printFileNameFlg) {
        printf("::::::::::::::\n");
        printf("%s\n", *(argv + 1));
        printf("::::::::::::::\n");
      }
			if((fp = fopen(*++argv, "r")) != NULL) {
				do_more(fp);
				fclose(fp);
			} else {
        perror("cannot open the file");
				exit(1);
      }
		}
  }
	return 0;
}

void do_more(FILE *fp) {

	char buf[ws.ws_col];
	int lineCounter = 0;
	char *str;
  int inpFd;
  if (printFileNameFlg) {
    lineCounter += 3;
  }

  if ((inpFd = open("/dev/tty", O_RDONLY)) == -1) {
    exit(1);
  }
  tty_mode(0, inpFd);
  set_cr_noecho_mode(inpFd);

	while ((str = fgets(buf, sizeof(buf), fp))) {
		if (lineCounter < (ws.ws_row - 1)) {
			if (fputs(buf, stdout) != EOF) {
				lineCounter++;
      } else {
				exit(1);
      }
		} else {
			AGAIN:;
			switch (see_more()) {
				case ' ':
					lineCounter = 0;
					fseek(fp,-(strlen(str) * sizeof(char)), SEEK_CUR);
          printf("\r       \r");
					break;
				case 'q':
          printf("\r       \r");
					goto FINISH;
				case '\n':
					lineCounter--;
					fseek(fp, -(strlen(str) * sizeof(char)), SEEK_CUR);
          printf("\r       \r");
					break;
				default:
					goto AGAIN;
			}
		}
	}
	FINISH:;
  tty_mode(1, inpFd);
}

char see_more(void){
	printf("\033[7m more?\033[m");
	FILE *inpFile;
	if ((inpFile = fopen("/dev/tty", "r")) == NULL) {
    perror("cannot open the file");
		exit(1);
  } else {
		return fgetc(inpFile);
  }
}

void tty_mode(int how, int fd) {
  // If how is equaled to 0, that means saving current state
  // If how is equaled to 1, that means revert to saved state
  static struct termios original_mode;
  if (how == 0)
    tcgetattr(fd, &original_mode);
  else
    tcsetattr(fd, TCSANOW, &original_mode);
}
void set_cr_noecho_mode(int fd) {
  struct termios ttystate;
  tcgetattr(fd, &ttystate);
  ttystate.c_lflag &= ~ICANON;
  ttystate.c_lflag &= ~ECHO;
  ttystate.c_cc[VMIN] = 1;
  tcsetattr(fd, TCSANOW, &ttystate);
}
