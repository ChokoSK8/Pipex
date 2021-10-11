/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:03:53 by abrun             #+#    #+#             */
/*   Updated: 2021/10/11 16:42:15 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**init_paths(void)
{
	char	**paths;
	int		fd;
	int		ret;
	char	*line;

	paths = malloc(sizeof(char *));
	if (!paths)
		return (0);
	paths[0] = 0;
	fd = open("/etc/paths", O_RDONLY);
	if (fd < 0)
		return (0);
	ret = get_next_line(fd, &line);
	if (ret < 0)
	{
		free_matc(paths);
		return (0);
	}
	while (ret > 0)
	{
		paths = ft_add_line_path(paths, line);
		if (!paths)
			break ;
		free(line);
		ret = get_next_line(fd, &line);
	}
	free(line);
	close(fd);
	if (!paths)
		free_matc(paths);
	return (paths);
}

char	**ft_add_line_path(char **mat, char *line)
{
	int		matlen;
	char	**new_mat;

	matlen = ft_matlen(mat);
	new_mat = malloc(sizeof(char *) * (matlen + 2));
	if (new_mat)
	{
		new_mat = get_new_mat_path(new_mat, mat, line, matlen);
		if (!new_mat)
			return (0);
	}
	free_matc(mat);
	return (new_mat);
}

char	**get_new_mat_path(char **new_mat, char **mat, char *line, int matlen)
{
	int		count;
	size_t	line_len;

	count = 0;
	while (matlen--)
	{
		new_mat[count] = ft_strdup(mat[count], ft_strlen(mat[count]));
		if (!new_mat[count++])
		{
			free_matc(new_mat);
			free_matc(mat);
			return (0);
		}
	}
	line_len = ft_strlen(line);
	new_mat[count] = ft_strdup(line, line_len + 1);
	if (!new_mat[count])
	{
		free_matc(new_mat);
		free_matc(mat);
		return (0);
	}
	new_mat[count][line_len] = '/';
	new_mat[count++][line_len + 1] = 0;
	new_mat[count] = 0;
	return (new_mat);
}
