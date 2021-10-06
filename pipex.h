/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:06:30 by abrun             #+#    #+#             */
/*   Updated: 2021/10/06 19:29:37 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdarg.h>
# include "Libft/libft.h"
# define BUFFER_SIZE 10

void	ft_dup2(int newfd, int oldfd);

void	ft_close_fd(int fd);

int		**make_pipes(void);

char	**assign_param(char **av, int n_av, int pt_av, char **paths);

char	*assign_cmd(char *av, char **paths);

char	*get_last_param(char **av, int pt_av);

int		get_n_av(int pt_av, char **av, int ac, char **paths);

char	***ft_init_newargvs(char **av, int ac, char **paths);

int		ft_write_in_file(int **fds, char **av, int ac);

void	ft_cmd_1(int **fds, char **newargv);

void	ft_cmd_2(int **fds, char **newargv);

int		check_error(char **av, int ac, char **paths);

int		check_file(char **av, int ac);

int		get_n_cmd(char **av, int ac, char **paths);

char	*get_str_file(int fd);

int		get_outfd(char *file);

size_t	get_len_buf(char *buf);

int		fill_line(char *buf, char **line);

char	*get_buf(int fd, int *ret, char *buf);

int		get_next_line(int fd, char **line);

char	*get_new_buf(char *buf);

int		checker_and_init(int fd, char **line, char *buf);

char	**init_paths();

char	**get_new_mat_path(char **new_mat, char **mat, char *line, int matlen);

char	**ft_add_line_path(char **mat, char *line);

int		is_arg_of_cmd(char **paths, char *av, size_t av_len);

char	*ft_add_one_path(char *line, int *count);

char	**get_paths(char *line, int count);

int		get_path_len(char *line, int count);
#endif
