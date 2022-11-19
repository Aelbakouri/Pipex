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

int main(int argc, char **argv)
{
	int tab[8];
	srand(time(NULL));
	int i;
	for (i = 0; i < 8; i++)
		tab[i] = rand() % 100;
	int fd = open("sum", O_WRONLY);
	if (fd == -1)
		return 1;
	for (i = 0; i < 8; i++)
	{
		write(fd, &tab[i], sizeof(int));
		printf("Wrote %d\n", tab[i]);
	}
	close(fd);
	fork();
}

