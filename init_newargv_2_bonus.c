/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_newargv_2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:04:51 by abrun             #+#    #+#             */
/*   Updated: 2021/10/13 15:06:04 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	***init_nw_2(char **av, int ac, char **paths)
{
	char	***newargv;
	int		count;
	int		n_av;
	int		pt_av;

	newargv = malloc(sizeof(char **) * 3);
	if (!newargv)
		return (0);
	count = -1;
	pt_av = 3;
	while (++count < 2)
	{
		n_av = get_n_av(pt_av + 1, av, ac, paths);
		newargv[count] = assign_param_2(av, n_av, pt_av, paths);
		if (n_av < 0 || newargv[count])
		{
			free_3dim_matc(newargv);
			return (0);
		}
		pt_av += n_av + 1;
	}
	newargv[count] = 0;
	return (newargv);
}

char	**assign_param_2(char **av, int n_av, int pt_av, char **paths)
{
	int		count;
	char	**newargv;

	count = 0;
	if (n_av < 0)
		return (0);
	newargv = malloc(sizeof(char *) * (n_av + 3));
	if (!newargv)
		return (0);
	newargv[count] = assign_cmd(av[pt_av++], paths);
	count++;
	while (n_av--)
	{
		newargv[count] = assign_one_case(av, &pt_av);
		if (!newargv[count++])
		{
			free_matc(newargv);
			return (0);
		}
	}
	newargv = assign_last_case_2(newargv, count, pt_av);
	return (newargv);
}

char	**assign_last_case_2(char **newargv, int count, int pt_av)
{
	if (pt_av == 3 + count)
	{
		newargv[count] = malloc(ft_strlen("file_tmp") + 1);
		if (!newargv[count])
		{
			free_matc(newargv);
			return (0);
		}
		ft_strcpy(newargv[count++], "file_tmp");
	}
	newargv[count] = 0;
	return (newargv);
}
