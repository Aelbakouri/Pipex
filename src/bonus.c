/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:53:49 by ael-bako          #+#    #+#             */
/*   Updated: 2023/01/08 12:19:57 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

void	child_process(char *cmd, char **env, char *infile, int fdout)
{
	int	fdin;

	if (fdout == -1)
		exit_w_msg("Pipex: Permission denied\n", 0);
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
		exit_w_msg ("Pipex: Invalid number of arguments.\n", 0);
	else
	{
		if (!str_ncmp(av[1], "here_doc", 8)
			&& !empty (av[3], 1) && !empty (av[4], 1))
		{
			fdout = ft_open(av[ac - 1], HERE_DOC);
			here_doc(av[2], ac, fdout, av[ac - 1]);
		}
		else
		{
			fdout = ft_open(av[ac - 1], OUTFILE);
			child_process(av[2], env, av[1], fdout);
		}
		dup2(fdout, STDOUT);
		while (i < ac - 2)
			redir(av[i++], env, 1);
		exec(av[i], env);
	}
	return (1);
}
