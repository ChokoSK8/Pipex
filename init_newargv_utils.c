/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_newargv_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:22:50 by abrun             #+#    #+#             */
/*   Updated: 2021/10/06 18:29:42 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	is_arg_of_cmd(char **paths, char *av, size_t av_len)
{
	int		n_path;
	char	*cmd;

	n_path = 0;
	while (paths[n_path])
	{
		cmd = malloc(ft_strlen(paths[n_path]) + av_len + 1);
		if (!cmd)
			return (-1);
		ft_strcpy(cmd, paths[n_path]);
		ft_strcat(cmd, av);
		if (!access(cmd, X_OK))
		{
			free(cmd);
			return (0);
		}
		n_path++;
		free(cmd);
	}
	return (1);
}
