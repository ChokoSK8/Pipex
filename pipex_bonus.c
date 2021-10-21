/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:06:03 by abrun             #+#    #+#             */
/*   Updated: 2021/10/21 12:34:53 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av)
{
	int		n_cmd;
	char	**paths;

	if (ac < 5)
		return (0);
	paths = init_paths();
	if (!paths)
		return (0);
	if (!strcmp(av[1], "here_doc"))
	{
		n_cmd = main_2(ac, av, paths);
		free_matc(paths);
		return (n_cmd);
	}
	n_cmd = ac - 3;
	if (!make_cmds(n_cmd, av, ac, paths))
	{
		free_matc(paths);
		return (0);
	}
	free_matc(paths);
	return (1);
}

int	main_2(int ac, char **av, char **paths)
{
	char	*heredoc;
	int		**fds;
	char	***newargv;
	int		n_cmd;
	int		ret;

	ret = 1;
	if (ac < 6)
		return (0);
	heredoc = get_heredoc(av);
	newargv = init_newargvs_2(av, paths);
	n_cmd = ac - 4;
	fds = make_pipes(n_cmd);
	if (!heredoc || !newargv || !fds || !put_in_file(heredoc))
	{
		free_params_nhf(newargv, heredoc, fds, n_cmd);
		return (0);
	}
	if (!make_heredoc_cmd(fds, newargv, av, ac))
		ret = 0;
	free_params_nhf(newargv, heredoc, fds, n_cmd);
	return (ret);
}
