/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_close.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:04:09 by abrun             #+#    #+#             */
/*   Updated: 2021/10/06 11:04:10 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_close_fd(int fd)
{
	if (close(fd) == -1)
	{
		perror("La fonction close a echoue");
		exit(EXIT_FAILURE);
	}
}

void	ft_close_fds_around(int **fds, int n_newargv)
{
	int	backup;

	backup = n_newargv;
	n_newargv -= 2;
	while (n_newargv >= 0)
	{
		ft_close_fd(fds[n_newargv][0]);
		ft_close_fd(fds[n_newargv][1]);
		n_newargv--;
	}
	n_newargv = backup + 1;
	while (fds[n_newargv])
	{
		ft_close_fd(fds[n_newargv][0]);
		ft_close_fd(fds[n_newargv][1]);
		n_newargv++;
	}
}

void	ft_close_fds(int **fds, int n_newargv)
{
	if (n_newargv == 0)
	{
		ft_close_fds_around(fds, n_newargv);
		ft_close_fd(fds[0][0]);
	}
	else
	{
		ft_close_fd(fds[n_newargv - 1][1]);
		ft_close_fd(fds[n_newargv][0]);
		ft_close_fds_around(fds, n_newargv);
	}
}

void	ft_close_all_execpt(int **fds, int n_newargv)
{
	ft_close_fd(fds[n_newargv][1]);
	while (n_newargv-- > 0)
	{
		ft_close_fd(fds[n_newargv][1]);
		ft_close_fd(fds[n_newargv][0]);
	}
}
