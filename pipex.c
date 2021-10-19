/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:06:10 by abrun             #+#    #+#             */
/*   Updated: 2021/10/19 11:12:41 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av)
{
	char	***newargv;
	char	**paths;
	int		**fds;

	if (ac != 5)
		return (0);
	paths = init_paths();
	if (!paths)
		return (0);
	newargv = ft_init_newargvs(av, paths);
	fds = make_pipes();
	if (!newargv || !fds || !main_cmds(fds, newargv))
	{
		free_params(newargv, paths, fds);
		return (0);
	}
	ft_write_in_file(fds, av, ac);
	free_params(newargv, paths, fds);
	return (1);
}

int	main_cmds(int **fds, char ***newargv)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
		ft_cmd_1(fds, newargv[0]);
	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
		ft_cmd_2(fds, newargv[1]);
	return (1);
}
