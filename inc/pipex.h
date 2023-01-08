/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:54:13 by ael-bako          #+#    #+#             */
/*   Updated: 2023/01/08 12:20:44 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>

# define STDIN 0
# define STDOUT 1
# define STDERR 2

# define INFILE 0
# define OUTFILE 1
# define HERE_DOC 2

// PIPEX UTILS
int		get_next_line(char **line);
int		exit_with_error(void);
int		print_error(char *message);
int		ft_open(char *filename, int mode);
char	*get_path(char *cmd, char **env);
void	exec(char *cmd, char **env);
void	here_doc(char *limiter, int ac, int fdout, char *oufile);
int		get_next_line(char **line);
void	redir(char *cmd, char **env, int fdin);
int		empty(char *s, int c);
void	exit_w_msg(char *msg, int c);

// STRING UTILS
char	*join_path(char *path, char *bin);
int		str_ncmp(char *str1, char *str2, int n);
int		str_ichr(char *str, char c);
char	*str_ndup(char *str, unsigned int n);
char	**ft_split(char *str, char sep);

#endif
