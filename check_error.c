/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:03:36 by abrun             #+#    #+#             */
/*   Updated: 2021/10/19 11:10:31 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_n_cmd(char **av, int ac, char **paths)
{
	int		count;
	int		n_cmd;
	int		c_path;
	char	*cmd;

	count = 1;
	n_cmd = 0;
	while (++count < ac - 1)
	{
		c_path = -1;
		while (paths[++c_path])
		{
			cmd = init_cmd(paths[c_path], av[count]);
			if (!cmd)
				return (0);
			if (!access(cmd, X_OK))
			{
				free(cmd);
				n_cmd++;
				break ;
			}
			free(cmd);
		}
	}
	return (n_cmd);
}

char	*init_cmd(char *path, char *av)
{
	char	*cmd;

	cmd = malloc(ft_strlen(path) + ft_strlen(av) + 1);
	if (!cmd)
		return (0);
	ft_strcpy(cmd, path);
	ft_strcat(cmd, av);
	return (cmd);
}
