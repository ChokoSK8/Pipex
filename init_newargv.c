/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_newargv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:04:35 by abrun             #+#    #+#             */
/*   Updated: 2021/10/11 19:02:43 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	***ft_init_newargvs(char **av, int ac, char **paths)
{
	char	***newargv;
	int		n_av;
	int		count;
	int		pt_av;

	newargv = malloc(sizeof(char **) * 3);
	if (!newargv)
		return (0);
	count = -1;
	pt_av = 2;
	while (++count < 2)
	{
		n_av = get_n_av(pt_av + 1, av, ac, paths);
		if (n_av < 0)
			return (0);
		newargv[count] = assign_param(av, n_av, pt_av, paths);
		if (!newargv[count])
			return (0);
		if (pt_av == 2)
			pt_av++;
		pt_av += n_av;
	}
	newargv[2] = 0;
	return (newargv);
}

int	get_n_av(int pt_av, char **av, int ac, char **paths)
{
	int		n_av;
	int		loop;
	int		arg;

	n_av = -1;
	loop = 1;
	while (loop && n_av + pt_av < ac - 1)
	{
		n_av++;
		arg = is_arg_of_cmd(paths, av[pt_av + n_av],
				ft_strlen(av[pt_av + n_av]));
		if (arg < 0)
			return (-1);
		if (!arg)
			loop = 0;
	}
	return (n_av);
}

char	*assign_cmd(char *av, char **paths)
{
	char	*cmd;
	int		n_path;
	size_t	av_len;

	n_path = 0;
	av_len = ft_strlen(av);
	while (paths[n_path])
	{
		cmd = malloc(ft_strlen(paths[n_path]) + av_len + 1);
		ft_strcpy(cmd, paths[n_path]);
		ft_strcat(cmd, av);
		if (!access(cmd, X_OK))
			return (cmd);
		n_path++;
		free(cmd);
	}
	free(cmd);
	return (0);
}

char	**assign_param(char **av, int n_av, int pt_av, char **paths)
{
	int		count;
	char	**newargv;

	count = 0;
	newargv = malloc(sizeof(char *) * (n_av + 3));
	if (!newargv)
		return (0);
	newargv[count] = assign_cmd(av[pt_av++], paths);
	if (!newargv[count++])
		return (0);
	while (n_av--)
	{
		newargv[count] = assign_one_case(av, &pt_av);
		if (!newargv[count++])
		{
			free_matc(newargv);
			return (0);
		}
	}
	newargv = assign_last_case(newargv, count, av[1], pt_av);
	return (newargv);
}
