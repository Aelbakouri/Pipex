/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main3.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 21:01:08 by ael-bako          #+#    #+#             */
/*   Updated: 2022/11/19 12:11:37 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <fcntl.h>

// int	main(int ac, char **av)
// {
// 	int	p1[2];
// 	int	p2[2];
// 	if (pipe(p1) == -1)
// 		return 1;
// 	int pid = fork();
// 	if (pid == -1)
// 		return 2;
// 	if (pid == 0) {
// 		close(p1[0]);
// 		close(p2[1]);
// 		// this for child process
// 		int x;
// 		if (read(p2[0], &x, sizeof(int)) == -1)
// 			return 3;
// 		printf("Received %d\n", x);
// 		x *= 4;
// 		if (write(p1[1], &x, sizeof(int)) == -1)
// 			return 4;
// 			printf("Wrote %d\n", x);
// 			close(p1[1]);
// 			close(p2[0]);
// 	}
// 	else {
// 		close(p1[1]);
// 		close(p2[0]);
// 		srand(time(NULL));
// 		int y = rand() % 10;
// 		if (write(p2[1], &y, sizeof(int)) == -1)
// 			return 5;
// 		printf("Wrote %d\n",y);
// 		if (read(p1[0], &y, sizeof(int)) == -1)
// 			return 6;
// 		printf("Result is %d\n", y);
// 		close(p1[0]);
// 		close(p2[1]);
// 		wait(NULL);
// 	}

// 	return 0;
// }
int main()
{
char *ptr = calloc(6,1);

int fd = open("maind.txt", O_RDWR  | O_CREAT, 0777);
// write(fd, "hello",5);
int x = read(fd, ptr, 5);
//if (ptr[0] == '\0')
	printf("%s", ptr);

}
