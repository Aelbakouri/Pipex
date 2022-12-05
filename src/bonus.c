/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:53:49 by ael-bako          #+#    #+#             */
/*   Updated: 2022/12/05 14:41:11 by ael-bako         ###   ########.fr       */
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

void	here_doc(char *limiter)
{
	pid_t	reader;
	int		fd[2];
	char	*line;

	pipe(fd);
	reader = fork();
	if (reader == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (str_ncmp(line, limiter, str_ichr(limiter, 0)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, str_ichr(line, 0));
		}
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		wait(NULL);
	}
}

void	child_process(char *cmd, char **env, char *infile)
{
	int	fdin;

	fdin = ft_open(infile, INFILE);
	dup2(fdin, STDIN);
	redir(cmd, env, fdin);
}

int	main(int ac, char **av, char **env)
{
	int	fdout;
	int	i;

	i = 3;
	if (ac < 5)
		return (write(STDERR, "Invalid number of arguments.\n", 29));
	else
	{
		if (!str_ncmp(av[1], "here_doc", 8))
		{
			fdout = ft_open(av[ac - 1], HERE_DOC);
			here_doc(av[2]);
		}
		else
		{
			fdout = ft_open(av[ac - 1], OUTFILE);
			child_process(av[2], env, av[1]);
		}
		dup2(fdout, STDOUT);
		while (i < ac - 2)
			redir(av[i++], env, 1);
		exec(av[i], env);
	}
	return (1);
}
