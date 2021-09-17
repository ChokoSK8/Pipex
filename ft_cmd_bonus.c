#include "pipex_bonus.h"

void	ft_cmd_n(int **fds, char **newargv, int n_newargv)
{
	ft_close_fd(fds[0][1]);
	ft_close_fd(fds[1][0]);
	ft_dup2(fds[0][0], STDIN_FILENO);
	ft_dup2(fds[1][1], STDOUT_FILENO);
	ft_dup2(fds[1][1], STDERR_FILENO);
	ft_close_fd(fds[0][0]);
	ft_close_fd(fds[1][1]);
	if (execve(newargv[0], newargv, NULL) == -1)
	{
		perror("La fonction execve 2 a echoue");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

void	ft_write_in_file(int **fds, char **av, int ac)
{
	char	buf[100];
	int		ret;
	int		outfd;

	ft_close_fd(fds[0][0]);
	ft_close_fd(fds[0][1]);
	ft_close_fd(fds[1][1]);
	ret = read(fds[1][0], buf, 100);
	ft_close_fd(fds[1][0]);
	buf[ret] = 0;
	outfd = open(av[ac - 1], O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
	if (outfd < 0)
		exit(EXIT_FAILURE);
	write(outfd, buf, ret);
	close(outfd);
}
