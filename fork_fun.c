#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <sys/wait.h>

int main(int argc, char **argv)
{
	int fd[2];
	int pid = fork();

	if (pipe(fd) == -1)
		return 1;
	if (pid == 0)
	{
		printf("child: %d\n ", pid);
		// child process
		close(fd[0]);
		char str[200];
		printf("input string: ");
		fgets(str, 200, stdin);
		str[strlen(str) - 1] = '\0';

		int n = strlen(str) + 1;
		if (write (fd[1], &n, sizeof(int)) == -1){
			return 2;
		}
		if (write(fd[1], &str, sizeof(char) * n) == -1)
			return 3;
		close(fd[1]);

	}
	else
	{
		printf("process: %d\n ", pid);
		// parent process
		close(fd[1]);
		char str[200];
		int n;
		if (read(fd[0], &n, sizeof(int)) == -1)
			return 4;
		if (read(fd[0], str, sizeof(char) * n) == -1)
			return 5;
		printf("Received: %s\n", str);
		close(fd[0]);
		wait(NULL);
	}
	return 0;
	// int tab[8];
	// srand(time(NULL));
	// int i;
	// for (i = 0; i < 8; i++)
	// 	tab[i] = rand() % 100;
	// int fd = open("sum", O_WRONLY);
	// if (fd == -1)
	// 	return 1;
	// for (i = 0; i < 8; i++)
	// {
	// 	write(fd, &tab[i], sizeof(int));
	// 	printf("Wrote %d\n", tab[i]);
	// }
	// close(fd);
	// fork();
}

