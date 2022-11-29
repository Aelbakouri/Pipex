/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 17:01:19 by ael-bako          #+#    #+#             */
/*   Updated: 2022/11/24 18:29:44 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int ac, char **av)
{
	int fd[3][2];
	int i;
	for (i = 0; i < 3; i++)
	{
		if (pipe(fd[i]) < 0)
		{
			return 1;
		}
	}
	int pid1 = fork();
	if (pid1 < 0)
		return 2;
	if (pid1 == 0)
	{
		//child process
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);
		close(fd[2][1]);
		int x;
		if (read(fd[0][0], &x, sizeof(int)) < 0)
		{
			return 3;
		}
		x += 5;
		if (write(fd[1][1], &x, sizeof(int))<0)
			return 4;
		close (fd[0][0]);
		close (fd[1][1]);
		return 0;
	}

	int pid2 = fork();
	if (pid2 < 0)
		return 2;
	if (pid2 == 0)
	{
		//child process 2
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[2][0]);
		int x;
		if (read(fd[1][0], &x, sizeof(int)) < 0)
		{
			return 4;
		}
		x += 5;
		if (write(fd[2][1], &x, sizeof(int))<0)
			return 5;
		close (fd[1][0]);
		close (fd[2][1]);
		return 0;
	}
	else
	{
		
	}
	// Parent process
}
