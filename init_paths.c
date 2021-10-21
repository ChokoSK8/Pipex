/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 15:03:53 by abrun             #+#    #+#             */
/*   Updated: 2021/10/19 19:35:56 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**init_paths(void)
{
	char	**paths;
	int		fd;
	char	*line;
	int		count;

	fd = open("/etc/environment", O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_file_line(fd);
	close(fd);
	if (!line)
		return (0);
	count = 0;
	while (line[count] && line[count] != '/')
		count++;
	paths = get_paths(line, count);
	free(line);
	return (paths);
}

char	**get_paths(char *line, int count)
{
	char	**paths;
	int		n_path;
	int		path_len;

	n_path = 0;
	path_len = get_path_len(line, count);
	paths = malloc(sizeof(char *) * (path_len + 1));
	if (!paths)
		return (0);
	while (line[count])
	{
		paths[n_path] = ft_add_one_path(line, &count);
		if (!paths[n_path])
		{
			free_matc(paths);
			return (0);
		}
		n_path++;
	}
	paths[n_path] = 0;
	return (paths);
}

int	get_path_len(char *line, int count)
{
	int	len;

	len = 0;
	while (line[count])
	{
		if (line[count] == ':')
			len++;
		count++;
	}
	if (len)
		len++;
	return (len);
}

char	*ft_add_one_path(char *line, int *count)
{
	char	*path;
	int		path_len;
	int		n;

	path_len = 0;
	while (line[*count + path_len] && line[*count + path_len] != ':')
		path_len++;
	path = malloc(path_len + 2);
	if (!path)
		return (0);
	n = 0;
	while (path_len-- && line[*count + 1])
	{
		path[n] = line[*count];
		*count += 1;
		n++;
	}
	path[n++] = '/';
	path[n] = 0;
	*count += 1;
	return (path);
}

char	*get_file_line(int fd)
{
	int		ret;
	char	buf[11];
	char	*line;

	line = get_line_step_1(buf, fd, &ret);
	if (!line)
		return (0);
	while (ret > 0)
	{
		ret = read(fd, buf, 10);
		if (ret < 0)
		{
			free(line);
			return (0);
		}
		if (ret && buf[ret - 1] == '\n')
			buf[ret - 1] = 0;
		else
			buf[ret] = 0;
		line = ft_strjoin_free(line, buf);
		if (!line)
			return (0);
	}
	return (line);
}
