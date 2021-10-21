/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_heredoc_cmd_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:05:27 by abrun             #+#    #+#             */
/*   Updated: 2021/10/21 14:28:31 by abrun            ###   ########.fr       */
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
		ft_cmd_1_hd(fds, newargv[0], 0, "file_tmp");
	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
		ft_cmd_2(fds, newargv[1], 1);
	ft_write_in_file_2(fds, av, ac, 1);
	return (1);
}

void	ft_cmd_1_hd(int **fds, char **newargv, int n_newargv, char *infile)
{
	int	infd;

	infd = open(infile, O_RDONLY);
	if (infd > 0)
	{
		ft_dup2(infd, STDIN_FILENO);
		ft_close_fd(infd);
		unlink(infile);
	}
	else
	{
		ft_put_error(infile);
		exit(EXIT_FAILURE);
	}
	ft_close_fds(fds, n_newargv);
	ft_dup2(fds[n_newargv][1], STDOUT_FILENO);
	ft_close_fd(fds[n_newargv][1]);
	if (execve(newargv[0], newargv, NULL) == -1)
	{
		perror("La fonction execve a echoue");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

void	ft_write_in_file_2(int **fds, char **av, int ac, int n_newargv)
{
	int		outfd;
	char	*str_file;

	ft_close_all_execpt(fds, n_newargv);
	str_file = get_str_file(fds[n_newargv][0]);
	ft_close_fd(fds[n_newargv][0]);
	if (!str_file)
		return ;
	outfd = get_outfd(av[ac - 1], 2);
	if (outfd < 0)
	{
		free(str_file);
		return ;
	}
	write(outfd, str_file, ft_strlen(str_file));
	free(str_file);
	close(outfd);
}
