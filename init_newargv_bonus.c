/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_newargv_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:04:44 by abrun             #+#    #+#             */
/*   Updated: 2021/10/11 19:49:11 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	***ft_init_newargvs_b(char **av, int ac, int n_cmd, char **paths)
{
	char	***newargv;
	int		n_av;
	int		count;
	int		pt_av;

	newargv = malloc(sizeof(char **) * n_cmd);
	if (!newargv)
		return (0);
	count = -1;
	pt_av = 2;
	while (++count < n_cmd)
	{
		n_av = get_n_av(pt_av + 1, av, ac, paths);
		newargv[count] = assign_param(av, n_av, pt_av, paths);
		if (!newargv[count])
			return (0);
		pt_av += n_av + 1;
	}
	printf("count : %d\n", count);
	newargv[count] = 0;
	return (newargv);
}

int	get_n_av(int pt_av, char **av, int ac, char **paths)
{
	int	n_av;
	int	loop;
	int	arg;

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
