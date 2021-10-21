/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_newargv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:04:35 by abrun             #+#    #+#             */
/*   Updated: 2021/10/21 11:48:00 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	***ft_init_newargvs(char **av, char **paths)
{
	char	***newargv;
	int		count;

	newargv = malloc(sizeof(char **) * 3);
	if (!newargv)
		return (0);
	count = -1;
	while (++count < 2)
	{
		newargv[count] = get_one_newargv(av, count, paths);
		if (!newargv[count])
		{
			free_3dim_matc(newargv);
			return (0);
		}
	}
	newargv[count] = 0;
	return (newargv);
}

char	**get_one_newargv(char **av, int count, char **paths)
{
	int		n_cases;
	char	**newargv;
	int		n;
	int		c;

	n_cases = get_n_cases(av[count + 2], 32, count);
	newargv = malloc(sizeof(char *) * (n_cases + 1));
	if (!newargv)
		return (0);
	n = 0;
	newargv[n++] = assign_cmd(av[count + 2], paths);
	c = 0;
	c = get_next_c(av[count + 2], c);
	while (av[count + 2][c])
	{
		newargv[n] = assign_next(av[count + 2], c);
		if (!newargv[n++])
		{
			free_matc(newargv);
			return (0);
		}
		c = get_next_c(av[count + 2], c);
	}
	newargv[n] = 0;
	return (newargv);
}

char	*assign_cmd(char *av, char **paths)
{
	char	*cmd;
	int		n_path;
	size_t	len;
	char	*split;

	n_path = 0;
	split = split_cmd(av);
	len = ft_strlen(split);
	while (paths[n_path])
	{
		cmd = malloc(ft_strlen(paths[n_path]) + len + 1);
		ft_strcpy(cmd, paths[n_path]);
		ft_strcat(cmd, split);
		if (!access(cmd, X_OK))
		{
			free(split);
			return (cmd);
		}
		n_path++;
		free(cmd);
	}
	return (split);
}
