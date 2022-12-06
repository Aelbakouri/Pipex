# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2
	int	str_ichr(char *str, char c)
	{
		int	i;

		i = 0;
		while (str[i] && str[i] != c)
			i++;
		if (str[i] == c)
			return (i);
		return (-1);
	}

	char	*join_path(char *path, char *bin)
	{
		char	*joined;
		int		i;
		int		j;

		joined = malloc(sizeof(char) * (str_ichr(path, 0) + str_ichr(bin, 0) + 2));
		i = 0;
		j = 0;
		while (path[j])
			joined[i++] = path[j++];
		joined[i++] = '/';
		j = 0;
		while (bin[j])
			joined[i++] = bin[j++];
		joined[i] = 0;
		return (joined);
	}

	int	str_ncmp(char *str1, char *str2, int n)
	{
		while (--n > 0 && *str1 && *str2 && *str1 == *str2)
		{
			str1++;
			str2++;
		}
		return (*str2 - *str1);
	}

	char	*str_ndup(char *str, unsigned int n)
	{
		char				*duped;
		unsigned int		i;

		i = 0;
		duped = malloc(sizeof(char) * (n + 1));
		while (i < n)
			duped[i++] = *str++;
		duped[n] = 0;
		return (duped);
	}

	char	**ft_split(char *str, char sep)
	{
		char	**tab;
		int		count;
		int		i;
		int		j;

		count = 0;
		j = -1;
		while (str[++j])
			if ((str[j] == sep && str[j + 1] != sep)
				|| (str[j] != sep && str[j + 1] == '\0'))
				count++;
		tab = malloc(sizeof(char *) * (count + 1));
		i = 0;
		while (i < count)
		{
			j = 0;
			while (*str && *str == sep)
				str++;
			while (str[j] && str[j] != sep)
				j++;
			tab[i++] = str_ndup(str, j);
			str = str + j;
		}
		tab[i] = NULL;
		return (tab);
	}
// **********************************************************************************
char	*get_path(char *cmd, char **env)
{
	char	*path;
	char	*dir;
	char	*bin;
	int		i;

	i = 0;
	while (env[i] && str_ncmp(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	path = env[i] + 5;
	while (path && str_ichr(path, ':') > -1)
	{
		dir = str_ndup(path, str_ichr(path, ':'));
		bin = join_path(dir, cmd);
		free(dir);
		if (access(bin, F_OK) == 0)
			return (bin);
		free(bin);
		path += str_ichr(path, ':') + 1;
	}
	return (cmd);
}

void	exec(char *cmd, char **env)
{
	char	**args;
	char	*path;

	args = ft_split(cmd, ' ');
	if (str_ichr(args[0], '/') > -1)
		path = args[0];
	else
		path = get_path(args[0], env);
	execve(path, args, env);
	write(STDERR, "pipex: ", 7);
	write(STDERR, cmd, str_ichr(cmd, 0));
	write(STDERR, ": command not found\n", 20);
	exit(127);
}

void	redir(char *cmd, char **env, int fdin)
{
	pid_t	pid;
	int		pipefd[2];

	pipe(pipefd);
	pid = fork();
	if (pid < 0)
		return (perror("Fork"));
	if (pid)
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN);
		waitpid(pid, NULL, 0);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT);
		if (fdin == STDIN)
			exit(1);
		else
			exec(cmd, env);
	}
}
// int heredoc(char *delim) {
// 	int hfd[2], nbytes, len;
// 	char buff[BUFFERSIZE + 1];

// 	if (pipe(hfd) == -1) {
// 		return -1;
// 	}
// 	len = str_ichr(delim, 0);
// 	write(1, "heredoc> ", 9);
// 	while ((nbytes = read(0, buff, BUFFERSIZE)) > 0) {
// 		buff[nbytes] = 0;
// 		if (nbytes == len + 1 && (str_ncmp(delim, buff, len) == 0) && buff[nbytes - 1] == '\n') {
// 			break ;
// 		}
// 		write(hfd[1], buff, nbytes);
// 		write(1, "heredoc> ", 9);
// 	}
// 	close(hfd[WRITE_END]);
// 	return (hfd[READ_END]);
// }

int	main(int ac, char **av, char** env)
{
		int		pipefd[2];
		int i = 0;
		(void)ac;
		char	*buff;
		char *del = av[1];
		buff = malloc(10000);
		// (void)av;

		// int fdin = open ("test.js", O_CREAT | O_RDWR | O_TRUNC, 0777);
		// dup2(fdin, STDIN);
		// write(0, "hello world ", 11);
		// printf("%d\n", fdin);
		// char *str = get_path(av[1], env);
		// redir(av[1], env, fdin);
		// printf("%s\n", str);
	// printf("%d\n",execve("/bin/lsds", &av[1], env));
	// printf("hello");
	while (buff[i - 1] != '\n' && str_ncmp())
	{
		read(0, &buff[i], 1);
		i++;
	}
	buff[i] = 0;

	write (1, buff, str_ichr(buff, 0));
}

