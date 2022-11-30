/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/27 16:48:02 by mlazzare          #+#    #+#             */
/*   Updated: 2022/11/30 17:34:39 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

static char	*ft_join(char *dst, const char *src)
{
	char	*r;
	size_t	i;
	size_t	j;

	i = -1;
	j = -1;
	r = malloc(sizeof(char) * (ft_strlen(src) + ft_strlen(dst) + 1));
	if (!r)
		return (NULL);
	while (dst[++i])
		r[i] = dst[i];
	while (src[++j])
		r[i++] = src[j];
	r[i] = '\0';
	return (r);
}

static void	child(int *fd, t_cmd *c, char **envp)
{
	int		i;
	char	*cmd;

	i = -1;
	if (dup2(c->f, STDIN_FILENO) < 0
		|| dup2(fd[1], STDOUT_FILENO) < 0)
		return (perror("Child process"));
	close(fd[0]);
	while (c->path[++i])
	{
		cmd = ft_join(c->path[i], c->cmd);
		if (!cmd)
			return ;
		if (execve(cmd, c->args, envp) != -1)
		{
			free(cmd);
			exit(EXIT_SUCCESS);
		}
		free(cmd);
	}
	exit(EXIT_FAILURE);
}

static void	parent(int *fd, t_cmd *c, char **envp)
{
	int		i;
	char	*cmd;

	i = -1;
	if (dup2(c->f, STDOUT_FILENO) < 0
		|| dup2(fd[0], STDIN_FILENO) < 0)
		return (perror("parent process"));
	close(fd[1]);
	while (c->path[++i])
	{
		printf ("cmd:%s\n", cmd);
		cmd = ft_join(c->path[i], c->cmd);
		if (!cmd)
			return ;
		if (execve(cmd, c->args, envp) != -1)
		{
			free(cmd);
			exit(EXIT_SUCCESS);
		}
		free(cmd);
	}
	exit(EXIT_FAILURE);
}

void	exec_cmd(t_cmd *cmd1, t_cmd *cmd2, char **envp)
{
	int		status;
	int		fd[2];
	pid_t	pid;

	status = 0;
	pipe(fd);
	pid = fork();
	if (pid < 0)
		return (perror("Fork"));
	if (!pid)
		child(fd, cmd1, envp);
	else
		parent(fd, cmd2, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(-1, &status, 0);
	waitpid(-1, &status, 0);
}

int	check_cmd(t_cmd *c)
{
	int		i;
	char	*cmd;

	i = -1;
	while (c->path[++i])
	{
		cmd = ft_join(c->path[i], c->cmd);
		if (!cmd)
			return (0);
		if (access(cmd, X_OK) != -1)
		{
			free(cmd);
			return (1);
		}
		free(cmd);
	}
	error_msg(c->cmd);
	return (0);
}
