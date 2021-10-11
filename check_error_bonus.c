/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:03:57 by abrun             #+#    #+#             */
/*   Updated: 2021/10/11 19:27:47 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	check_error(char **av, int ac, int len_av, char **paths)
{
	int	n_cmd;

	errno = EIO;
	if (ac < len_av)
	{
		perror("zsh: parse error near '\\n'");
		exit(EXIT_FAILURE);
	}
	n_cmd = get_n_cmd(av, ac, len_av - 2, paths);
	if (n_cmd < 0)
	{
		perror("zsh: parse error near '\\n'");
		exit(EXIT_FAILURE);
	}
	if (n_cmd < 2)
	{
		perror("Il n'y a pas assez de commandes");
		return (0);
	}
	return (1);
}

int	get_n_cmd(char **av, int ac, int from, char **paths)
{
	int		count;
	int		n_cmd;
	char	*cmd;
	int		c_path;

	count = from - 1;
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
