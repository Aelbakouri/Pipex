/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-bako <ael-bako@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:54:00 by ael-bako          #+#    #+#             */
/*   Updated: 2022/12/08 16:59:16 by ael-bako         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/pipex.h"

int	main(int ac, char **av, char **env)
{
	int	fdin;
	int	fdout;

	if (ac == 5)
	{
		fdin = ft_open(av[1], INFILE);
		fdout = ft_open(av[4], OUTFILE);
		if (fdin == -1)
			exit_w_msg(av[1], 1);
		if (fdout == -1)
			exit_w_msg(av[4], 1);
		dup2(fdin, STDIN);
		dup2(fdout, STDOUT);
		redir(av[2], env, fdin);
		exec(av[3], env);
	}
	else
		exit_w_msg ("Pipex: Invalid number of arguments.\n", 0);
	return (1);
}
