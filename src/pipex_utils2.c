/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 11:27:20 by ael-bako          #+#    #+#             */
/*   Updated: 2022/12/08 19:03:04 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	write(0, "here_doc> ", 10);
	r = read(0, &c, 1);
	while (r && r != -1 && c != '\n' && c != '\0')
	{
		buffer[i++] = c;
		r = read(0, &c, 1);
	}
	buffer[i++] = '\n';
	buffer[i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}

void	exit_w_msg(char *msg, int perr)
{
	if (perr)
	{
		write (STDERR, "Pipex: ", 7);
		perror(msg);
	}
	else
		write (STDERR, msg, str_ichr(msg, 0));
	exit(1);
}

void	in_child_process(int fd, char *limiter)
{
	char	*line;

	while (get_next_line(&line))
	{
		if (str_ncmp(line, limiter, str_ichr(limiter, 0) + 1) == 0)
			exit(EXIT_SUCCESS);
		write(fd, line, str_ichr(line, 0));
	}
}

void	here_doc(char *limiter, int ac, int fdout, char *oufile)
{
	pid_t	reader;
	int		fd[2];

	if (fdout == -1)
		exit_w_msg(oufile, 1);
	if (ac != 6)
		exit_w_msg ("Pipex: Invalid number of arguments.\n", 0);
	if (pipe(fd) == -1)
		exit_w_msg("Pipe", 1);
	reader = fork();
	if (reader == -1)
		exit_w_msg("Fork", 1);
	if (reader == 0)
	{
		close(fd[0]);
		in_child_process(fd[1], limiter);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		wait(NULL);
	}
}
