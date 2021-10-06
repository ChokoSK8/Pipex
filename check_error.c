/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:03:36 by abrun             #+#    #+#             */
/*   Updated: 2021/10/06 18:28:24 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	check_error(char **av, int ac, char **paths)
{
	int	n_cmd;

	errno = EIO;
	if (ac < 5)
		return (0);
	n_cmd = get_n_cmd(av, ac, paths);
	if (n_cmd < 0)
	{
		perror("zsh: parse error near '\\n'");
		return (0);
	}
	if (n_cmd != 2)
	{
		perror("Il n'y a pas exactement 2 commandes");
		return (0);
	}
	return (1);
}

int	get_n_cmd(char **av, int ac, char **paths)
{
	int		count;
	int		n_cmd;
	int		c_path;
	char	*cmd;

	count = 2;
	n_cmd = 0;
	while (count < ac - 1)
	{
		c_path = 0;
		while (paths[c_path])
		{
			cmd = malloc(ft_strlen(paths[c_path]) + ft_strlen(av[count]));
			if (!cmd)
				return (0);
			ft_strcpy(cmd, paths[c_path]);
			ft_strcat(cmd, av[count]);
			if (!access(cmd, X_OK))
			{
					n_cmd++;
					break ;
			}
			c_path++;
		}
		count++;
	}
	free(cmd);
	return (n_cmd);
}
