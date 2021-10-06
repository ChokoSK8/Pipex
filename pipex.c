/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:06:10 by abrun             #+#    #+#             */
/*   Updated: 2021/10/06 18:48:54 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av)
{
	pid_t	child_pid;
	int		**fds;
	char	***newargv;
	char	**paths;

	paths = init_paths();
	if (!paths)
		return (0);
	if (!check_error(av, ac, paths))
		return (0);
	newargv = ft_init_newargvs(av, ac, paths);
	if (!newargv)
		return (0);
	fds = make_pipes();
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
	ft_write_in_file(fds, av, ac);
	free_3dim_matc(newargv);
	free_matc(paths);
	printf("\nTest des leaks\n");
	system("leaks pipex | grep leaked\n");
	return (1);
}
