/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:05:50 by abrun             #+#    #+#             */
/*   Updated: 2021/10/21 14:31:23 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	**make_pipes(int n_cmd)
{
	int	**fds;
	int	count;

	fds = malloc(sizeof(int *) * (n_cmd + 1));
	if (!fds)
		return (0);
	count = 0;
	while (count < n_cmd)
	{
		fds[count] = malloc(sizeof(int) * 2);
		if (!fds[count])
			return (0);
		if (pipe(fds[count]) == -1)
			return (0);
		count++;
	}
	fds[count] = 0;
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

int	init_param_heredoc(char *av, char **buf, char **heredoc, int *ret)
{
	int	av_len;

	av_len = ft_strlen(av);
	*buf = malloc(av_len + 1);
	if (!*buf)
		return (0);
	*heredoc = malloc(1);
	if (!*heredoc)
	{
		free(*buf);
		return (0);
	}
	**heredoc = 0;
	*ret = -2;
	return (av_len);
}	

char	*get_heredoc(char **av)
{
	char	*heredoc;
	char	*buf;
	int		ret;
	int		av_len;

	av_len = init_param_heredoc(av[2], &buf, &heredoc, &ret);
	if (!av_len)
		return (0);
	write(STDOUT_FILENO, "pipe heredoc > ", 16);
	while (ret > 0 || ret == -2)
	{
		if (ret != -2 && ft_strnstr(buf, "\n", av_len))
			write(STDOUT_FILENO, "pipe heredoc > ", 16);
		ret = read(STDOUT_FILENO, buf, av_len);
		buf[ret] = 0;
		if (strncmp(buf, av[2], av_len))
			heredoc = ft_strjoin_free(heredoc, buf);
		else
			ret = 0;
	}
	read(STDOUT_FILENO, buf, 1);
	free(buf);
	return (heredoc);
}

int	put_in_file(char *heredoc)
{
	int	fd;
	int	ret;
	int	heredoc_len;

	fd = open("file_tmp", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (fd <= 0)
		return (0);
	heredoc_len = ft_strlen(heredoc);
	ret = write(fd, heredoc, heredoc_len);
	if (ret != heredoc_len)
		return (0);
	close (fd);
	return (1);
}
