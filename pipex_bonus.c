/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:06:03 by abrun             #+#    #+#             */
/*   Updated: 2021/10/13 15:55:19 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av)
{
	int		n_cmd;
	char	**paths;

	paths = init_paths();
	if (!paths)
		return (0);
	if (!strcmp(av[1], "here_doc"))
	{
		n_cmd = main_2(ac, av, paths);
		free_matc(paths);
		return (n_cmd);
	}
	if (!check_error(av, ac, 4, paths))
		return (0);
	n_cmd = get_n_cmd(av, ac, 2, paths);
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
	if (!check_error(av, ac, 5, paths))
		return (0);
	heredoc = get_heredoc(av);
	newargv = init_nw_2(av, ac, paths);
	fds = make_pipes(2);
	n_cmd = get_n_cmd(av, ac, 3, paths);
	if (!heredoc || !newargv || !fds || !put_in_file(heredoc))
	{
		free_params(newargv, paths, heredoc);
		free_mati(fds, n_cmd);
		return (0);
	}
	if (!make_heredoc_cmd(fds, newargv, av, ac))
		ret = 0;
	unlink("file_tmp");
	free_params(newargv, paths, heredoc);
	free_mati(fds, n_cmd);
	return (ret);
}
