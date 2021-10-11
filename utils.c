/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:05:41 by abrun             #+#    #+#             */
/*   Updated: 2021/10/11 16:18:38 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	**make_pipes(void)
{
	int		count;
	int		**fds;

	count = 2;
	fds = malloc(sizeof(int *) * 2);
	if (!fds)
		return (0);
	while (count--)
	{
		fds[count] = malloc(sizeof(int) * 2);
		if (!fds[count])
			return (0);
		if (pipe(fds[count]) == -1)
			return (0);
	}
	return (fds);
}

void	ft_dup2(int newfd, int oldfd)
{
	if (dup2(newfd, oldfd) == -1)
	{
		perror("La fonction dup2 a echoue");
		exit(EXIT_FAILURE);
	}
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

void	free_params(char ***newargv, char **paths, int **fds)
{
	if (newargv)
		free_3dim_matc(newargv);
	if (paths)
		free_matc(paths);
	if (fds)
		free_mati(fds, 2);
}
