/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:04:28 by abrun             #+#    #+#             */
/*   Updated: 2021/10/21 14:18:00 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_cmd_n(int **fds, char **newargv, int n_newargv)
{
	ft_close_fds(fds, n_newargv);
	ft_dup2(fds[n_newargv - 1][0], STDIN_FILENO);
	ft_dup2(fds[n_newargv][1], STDOUT_FILENO);
	ft_close_fd(fds[n_newargv - 1][0]);
	ft_close_fd(fds[n_newargv][1]);
	if (execve(newargv[0], newargv, NULL) == -1)
	{
		perror("La fonction execve a echoue");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

void	ft_cmd_1(int **fds, char **newargv, int n_newargv, char *infile)
{
	int	infd;

	infd = open(infile, O_RDONLY);
	if (infd > 0)
	{
		ft_dup2(infd, STDIN_FILENO);
		ft_close_fd(infd);
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

void	ft_cmd_2(int **fds, char **newargv, int n_newargv)
{
	ft_close_fds(fds, n_newargv);
	ft_dup2(fds[n_newargv - 1][0], STDIN_FILENO);
	ft_dup2(fds[n_newargv][1], STDOUT_FILENO);
	ft_close_fd(fds[n_newargv - 1][0]);
	ft_close_fd(fds[n_newargv][1]);
	if (execve(newargv[0], newargv, NULL) == -1)
	{
		perror("La fonction execve a echoue");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

int	get_outfd(char *file, int config)
{
	int	outfd;

	if (!access(file, F_OK))
	{
		if (!access(file, W_OK) && config == 1)
			outfd = open(file, O_TRUNC | O_WRONLY);
		else if (!access(file, W_OK) && config == 2)
			outfd = open(file, O_APPEND | O_WRONLY);
		else
		{
			outfd = -1;
			perror("zsh: outfile");
		}
	}
	else if (config == 1)
		outfd = open(file, O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
	else
		outfd = open(file, O_CREAT | O_RDWR,
				S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
	return (outfd);
}

int	ft_write_in_file(int **fds, char **av, int ac, int n_newargv)
{
	int		outfd;
	char	*str_file;

	ft_close_all_execpt(fds, n_newargv);
	str_file = get_str_file(fds[n_newargv][0]);
	ft_close_fd(fds[n_newargv][0]);
	if (!str_file)
		return (0);
	outfd = get_outfd(av[ac - 1], 1);
	if (outfd < 0)
	{
		free(str_file);
		return (0);
	}
	write(outfd, str_file, ft_strlen(str_file));
	free(str_file);
	close(outfd);
	return (1);
}
