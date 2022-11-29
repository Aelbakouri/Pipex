#include <unistd.h>

int main (int ac, char **av)
{

	char *str;
	read(STDIN_FILENO, str, 50);
	str[50] = '\0';
	 write (1, str, 50);

}
 