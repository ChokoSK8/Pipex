/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:20:46 by abrun             #+#    #+#             */
/*   Updated: 2021/10/15 03:30:05 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_params(char ***newargv, char **paths, char *heredoc)
{
	if (heredoc)
		free(heredoc);
	if (newargv)
		free_3dim_matc(newargv);
	if (paths)
		free_matc(paths);
}

void	free_params_nhf(char ***newargv, char *heredoc, int **fds, int n_cmd)
{
	if (heredoc)
		free(heredoc);
	if (newargv)
		free_3dim_matc(newargv);
	if (fds)
		free_mati(fds, n_cmd);
}

void	free_makecmds(char ***newargv, int **fds, int n_cmd)
{
	if (newargv)
		free_3dim_matc(newargv);
	if (fds)
		free_mati(fds, n_cmd);
}

char	*get_str_file(int fd)
{
	char	buf[11];
	char	*str_file;
	int		ret;

	ret = read(fd, buf, 10);
	if (ret < 0)
		return (0);
	buf[ret] = 0;
	str_file = ft_strdup(buf, ft_strlen(buf));
	if (!str_file)
		return (0);
	while (ret > 0)
	{
		ret = read(fd, buf, 10);
		if (ret < 0)
		{
			free(str_file);
			return (0);
		}
		buf[ret] = 0;
		str_file = ft_strjoin_free(str_file, buf);
		if (!str_file)
			return (0);
	}
	return (str_file);
}
