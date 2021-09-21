#include "pipex_bonus.h"

void	ft_cmd_n(int **fds, char **newargv, int n_newargv)
{
	ft_close_fds(fds, n_newargv);
	ft_dup2(fds[n_newargv - 1][0], STDIN_FILENO);
	ft_dup2(fds[n_newargv][1], STDOUT_FILENO);
	ft_close_fd(fds[n_newargv - 1][0]);
	ft_close_fd(fds[n_newargv][1]);
	if (execve(newargv[0], newargv, NULL) == -1)
		perror("La fonction execve a echoue");
}

void	ft_cmd_1(int **fds, char **newargv, int n_newargv)
{
	ft_close_fds(fds, n_newargv);
	ft_dup2(fds[n_newargv][1], STDOUT_FILENO);
	ft_close_fd(fds[n_newargv][1]);
	if (execve(newargv[0], newargv, NULL) == -1)
	{
		perror("La fonction execve 1 a echoue");
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
		perror("La fonction execve 2 a echoue");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
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
	outfd = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	if (outfd < 0)
		return (0);
	write(outfd, str_file, ft_strlen(str_file));
	close(outfd);
	return (1);
}
