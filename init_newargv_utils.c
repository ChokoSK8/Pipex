/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_newargv_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:22:50 by abrun             #+#    #+#             */
/*   Updated: 2021/10/19 12:40:42 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_n_cases(char *str, char c, int count)
{
	int	n;

	n = 0;
	while (*str && *str == c)
		str++;
	while (*str)
	{
		n++;
		while (*str && *str != c)
			str++;
		while (*str && *str == c)
			str++;
	}
	if (!count)
		n++;
	return (n);
}

char	*split_cmd(char *av)
{
	char	*split;
	int		len;
	int		c;

	len = 0;
	c = 0;
	while (av[c] && av[c] == 32)
		c++;
	while (av[c + len] && av[c + len] != 32)
		len++;
	split = malloc(len + 1);
	len = 0;
	while (av[c + len] && av[c + len] != 32)
	{
		split[len] = av[c + len];
		len++;
	}
	split[len] = 0;
	return (split);
}

int	get_next_c(char *av, int c)
{
	while (av[c] && av[c] == 32)
		c++;
	while (av[c] && av[c] != 32)
		c++;
	while (av[c] && av[c] == 32)
		c++;
	return (c);
}

char	*assign_next(char *av, int c)
{
	int		len;
	char	*split;
	int		count;

	len = 0;
	while (av[c + len] && av[c + len] != 32)
		len++;
	split = malloc(len + 1);
	if (!split)
		return (0);
	count = 0;
	while (av[c + count] && av[c + count] != 32)
	{
		split[count] = av[c + count];
		count++;
	}
	split[count] = 0;
	return (split);
}

char	**assign_last(char **newargv, char *av, int count, int n)
{
	if (!count)
	{
		newargv[n] = malloc(ft_strlen(av) + 1);
		if (!newargv[n])
		{
			free_matc(newargv);
			return (0);
		}
		ft_strcpy(newargv[n], av);
		n++;
	}
	newargv[n] = 0;
	return (newargv);
}
