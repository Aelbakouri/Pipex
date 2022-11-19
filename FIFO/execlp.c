#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	int pid = fork();

	if (pid == -1) { return 1; }
	if (pid == 0)
		execlp("ping", "ping" ,"-c", "4", "google.com ", NULL);
	else
	{
		wait(NULL);
		printf("hello world\n%d\n", pid);
	}
}
