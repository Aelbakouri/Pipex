#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	int tab[8];
	srand(time(NULL));
	int i, sum = 0;
	for (i = 0; i < 8; i++)
		tab[i] = rand() % 1000;
	int fd = open("sum", O_RDONLY);
	if (fd == -1)
		return 1;
	for (i = 0; i < 8; i++)
	{
		if(read(fd, &tab[i], sizeof(int)) == -1)
			return 1;
			sum = sum + tab[i];

		printf("Received %d\n", tab[i]);
	}
		printf("sum %d\n", sum);
	close(fd);
	return 0;
}
