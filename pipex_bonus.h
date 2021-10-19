/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:08:30 by abrun             #+#    #+#             */
/*   Updated: 2021/10/19 13:35:37 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H
# include <sys/wait.h>
# include <errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include "Libft/libft.h"

void	ft_dup2(int newfd, int oldfd);

void	ft_close_fd(int fd);

int		**make_pipes(int n_cmd);

char	**assign_param(char **av, int n_av, int pt_av, char **paths);

char	*assign_first(char **av, int pt_av);

char	*get_last_param(char **av, int pt_av);

int		get_n_av(int pt_av, char **av, int ac, char **paths);

char	***ft_init_newargvs_b(char **av, char **paths, int n_cmd);

char	***init_newargvs_2(char **av, char **paths);

int		ft_write_in_file(int **fds, char **av, int ac, int n_newargv);

void	ft_cmd_1(int **fds, char **newargv, int n_newargv);

void	ft_cmd_2(int **fds, char **newargv, int n_newargv);

int		check_file(char **av, int ac);

int		get_n_cmd(char **av, int ac, int from, char **paths);

void	print_newargv(char ***newargv, int n_cmd);

void	ft_close_fds(int **fds, int n_newargv);

void	ft_close_all_execpt(int **fds, int n_newargv);

void	ft_close_fds_around(int **fds, int n_newargv);

void	ft_cmd_n(int **fds, char **newargv, int n_newargv);

int		loop_cmd(int n_cmd, int n_newargv, char ***newargv, int **fds);

int		make_cmds(int n_cmd, char **av, int ac, char **paths);

int		main_2(int ac, char **av, char **paths);

char	*get_heredoc(char **av);

char	**assign_param_2(char **av, int n_av, int pt_av, char **paths);

int		put_in_file(char *heredoc);

void	ft_write_in_file_2(int **fds, char **av, int ac, int n_newargv);

int		make_heredoc_cmd(int **fds, char ***newargv, char **av, int ac);

int		main_2(int ac, char **av, char **paths);

char	*get_str_file(int fd);

int		get_outfd(char *file, int config);

char	**init_paths(void);

char	*init_cmd(char *path, char *av);

char	*assign_cmd(char *av, char **paths);

char	**assign_last_case(char **newargv, int count, char *av, int pt_av);

char	**assign_last_case_2(char **newargv, int count, int pt_av);

char	*assign_one_case(char **av, int *pt_av);

int		is_arg_of_cmd(char **paths, char *av, size_t av_len);

void	free_params(char ***newargv, char **paths, char *heredoc);

void	free_makecmds(char ***newargv, int **fds, int n_cmd);

pid_t	get_child_pid(char ***newargv, int **fds, int n_cmd);

int		get_n_cases(char *av, char c, int count);

int		get_next_c(char *av, int c);

char	*assign_next(char *av, int c);

char	**assign_last(char **newargv, char *av, int count, int n);

char	*split_cmd(char *av);

char	**get_one_newargv(char **av, int count, char **paths);

char	**get_one_newargv_2(char **av, int count, char **paths);

char	**assign_last_2(char **newargv, int count, int n);

char	*get_str_file(int fd);

void	free_params_nhf(char ***newargv, char * heredoc, int **fds, int n_cmd);
#endif
