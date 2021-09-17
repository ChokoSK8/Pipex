#ifndef PIPEX_H
# define PIPEX_H
# include <stdio.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdarg.h>
# include "Libft/libft.h"

void	ft_dup2(int newfd, int oldfd);

void	ft_close_fd(int fd);

int		**make_pipes(void);

char	**assign_param(char **newargv, char **av, int n_av, int pt_av);

char	*assign_first(char **av, int pt_av);

char	*get_last_param(char **av, int pt_av);

int		get_n_av(int pt_av, char **av, int ac);

char	***ft_init_newargvs(char **av, int ac);

void	ft_write_in_file(int **fds, char **av, int ac);

void	ft_cmd_1(int **fds, char **newargv);

void	ft_cmd_2(int **fds, char **newargv);

int		check_error(char **av, int ac);

int		check_file(char **av, int ac);

int		get_n_cmd(char **av, int ac);

#endif
