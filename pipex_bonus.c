/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:06:03 by abrun             #+#    #+#             */
/*   Updated: 2021/10/11 19:30:07 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av)
{
	int		**fds;
	int		n_cmd;
	char	**paths;

	paths = init_paths();
	if (!paths)
		return (0);
	if (!strcmp(av[1], "here_doc"))
	{
		n_cmd = main_2(ac, av, paths);
		return (n_cmd);
	}	
	if (!check_error(av, ac, 4, paths))
		return (0);
	n_cmd = get_n_cmd(av, ac, 2, paths);
	fds = make_pipes(n_cmd);
	if (!make_cmds(fds, n_cmd, av, ac, paths))
		return (0);
	free(fds);
	return (1);
}

int	main_2(int ac, char **av, char **paths)
{
	char	*heredoc;
	int		**fds;
	char	***newargv;

	if (!check_error(av, ac, 5, paths))
		return (0);
	heredoc = get_heredoc(av);
	if (!heredoc)
		return (0);
	newargv = init_nw_2(av, ac, paths);
	fds = make_pipes(2);
	if (!put_in_file(heredoc))
		return (0);
	if (!fds)
		return (0);
	if (!make_heredoc_cmd(fds, newargv, av, ac))
		return (0);
	unlink("file_tmp");
	return (1);
}
