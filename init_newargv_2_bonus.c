/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_newargv_2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:04:51 by abrun             #+#    #+#             */
/*   Updated: 2021/10/21 12:26:11 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	***init_newargvs_2(char **av, char **paths)
{
	char	***newargv;
	int		count;

	newargv = malloc(sizeof(char **) * 3);
	if (!newargv)
		return (0);
	count = -1;
	while (++count < 2)
	{
		newargv[count] = get_one_newargv_2(av, count, paths);
		if (!newargv[count])
		{
			free_3dim_matc(newargv);
			return (0);
		}
	}
	newargv[count] = 0;
	return (newargv);
}

char	**get_one_newargv_2(char **av, int count, char **paths)
{
	int		n_cases;
	char	**newargv;
	int		n;
	int		c;

	n_cases = get_n_cases(av[count + 3], 32, count);
	newargv = malloc(sizeof(char *) * (n_cases + 1));
	if (!newargv)
		return (0);
	n = 0;
	newargv[n++] = assign_cmd(av[count + 3], paths);
	c = 0;
	c = get_next_c(av[count + 3], c);
	while (av[count + 3][c])
	{
		newargv[n] = assign_next(av[count + 3], c);
		if (!newargv[n++])
		{
			free_matc(newargv);
			return (0);
		}
		c = get_next_c(av[count + 3], c);
	}
	newargv[n] = 0;
	return (newargv);
}

char	**assign_last_2(char **newargv, int count, int n)
{
	if (!count)
	{
		newargv[n] = malloc(ft_strlen("file_tmp") + 1);
		if (!newargv[n])
		{
			free_matc(newargv);
			return (0);
		}
		ft_strcpy(newargv[n++], "file_tmp");
	}
	newargv[n] = 0;
	return (newargv);
}
