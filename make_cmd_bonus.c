/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:05:17 by abrun             #+#    #+#             */
/*   Updated: 2021/10/21 14:26:25 by abrun            ###   ########.fr       */
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

int	make_cmds(int n_cmd, char **av, int ac, char **paths)
{
	pid_t	child_pid;
	int		n_newargv;
	char	***newargv;
	int		**fds;

	fds = make_pipes(n_cmd);
	newargv = ft_init_newargvs_b(av, paths, n_cmd);
	child_pid = fork();
	if (!newargv || !fds || child_pid == -1)
	{
		free_makecmds(newargv, fds, n_cmd);
		return (0);
	}
	if (child_pid == 0)
		ft_cmd_1(fds, newargv[0], 0, av[1]);
	n_newargv = loop_cmd(n_cmd, 1, newargv, fds);
	child_pid = get_child_pid(newargv, fds, n_cmd);
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
		ft_cmd_2(fds, newargv[n_newargv], n_newargv);
	ft_write_in_file(fds, av, ac, n_newargv);
	free_makecmds(newargv, fds, n_cmd);
	return (1);
}

pid_t	get_child_pid(char ***newargv, int **fds, int n_cmd)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		free_makecmds(newargv, fds, n_cmd);
		return (-1);
	}
	return (child_pid);
}	
