/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_heredoc_cmd_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:05:27 by abrun             #+#    #+#             */
/*   Updated: 2021/10/06 11:05:29 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	make_heredoc_cmd(int **fds, char ***newargv, char **av, int ac)
{
	int	child_pid;

	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
		ft_cmd_1(fds, newargv[0], 0);
	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
		ft_cmd_2(fds, newargv[1], 1);
	ft_write_in_file_2(fds, av, ac, 1);
	return (1);
}

void	ft_write_in_file_2(int **fds, char **av, int ac, int n_newargv)
{
	char	buf[100];
	int		ret;
	int		outfd;
	char	c;

	ft_close_all_execpt(fds, n_newargv);
	ret = read(fds[n_newargv][0], buf, 100);
	ft_close_fd(fds[n_newargv][0]);
	buf[ret] = 0;
	outfd = open(av[ac - 1], O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	if (outfd < 0)
		exit(EXIT_FAILURE);
	ret = 1;
	while (ret)
		ret = read(outfd, &c, 1);
	write(outfd, buf, ft_strlen(buf));
	close(outfd);
}
