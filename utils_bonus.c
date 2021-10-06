/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:05:50 by abrun             #+#    #+#             */
/*   Updated: 2021/10/06 11:05:52 by abrun            ###   ########.fr       */
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

char	*get_heredoc(char **av)
{
	char	*heredoc;
	char	buf[100];
	int		ret;

	heredoc = malloc(1);
	if (!heredoc)
		return (0);
	*heredoc = 0;
	ret = 2;
	while (ret > 0)
	{
		write(STDOUT_FILENO, "pipe heredoc > ", 16);
		ret = read(STDOUT_FILENO, buf, 100);
		buf[ret] = 0;
		if (strncmp(buf, av[2], strlen(av[2])))
			heredoc = ft_strjoin(heredoc, buf);
		else
			ret = 0;
	}
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

char	*get_str_file(int fd)
{
	char	buf[11];
	char	*str_file;
	int		ret;

	str_file = malloc(1);
	if (!str_file)
		return (0);
	*str_file = 0;
	ret = 1;
	while (ret)
	{
		ret = read(fd, buf, 10);
		buf[ret] = 0;
		str_file = ft_strjoin(str_file, buf);
		if (!str_file)
			return (0);
	}
	return (str_file);
}
