/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:05:17 by abrun             #+#    #+#             */
/*   Updated: 2021/10/11 19:39:30 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	loop_cmd(int n_cmd, int n_newargv, char ***newargv, int **fds)
{
	pid_t	child_pid;

	while (n_cmd > 2)
	{
		child_pid = fork();
		if (child_pid == 0)
			ft_cmd_n(fds, newargv[n_newargv], n_newargv);
		n_newargv++;
		n_cmd--;
	}
	return (n_newargv);
}

int	make_cmds(int **fds, int n_cmd, char **av, int ac, char **paths)
{
	int		child_pid;
	int		n_newargv;
	char	***newargv;

	newargv = ft_init_newargvs_b(av, ac, n_cmd, paths);
	if (!newargv)
		return (0);
	child_pid = fork();
	if (child_pid == -1)
	{
		free_3dim_matc(newargv);
		return (0);
	}
	if (child_pid == 0)
		ft_cmd_1(fds, newargv[0], 0);
	n_newargv = 1;
	n_newargv = loop_cmd(n_cmd, n_newargv, newargv, fds);
	child_pid = fork();
	if (child_pid == -1)
	{
		free_3dim_matc(newargv);
		return (0);
	}
	if (child_pid == 0)
		ft_cmd_2(fds, newargv[n_newargv], n_newargv);
	ft_write_in_file(fds, av, ac, n_newargv);
	free_3dim_matc(newargv);
	return (1);
}
