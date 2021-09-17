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
	n_newargv = backup;
	while (fds[n_newargv])
	{
		ft_close_fd(fds[n_newargv][0]);
		ft_close_fd(fds[n_newargv][1]);
		n_newargv++;
	}
}

void	ft_close_fd(int fd)
{
	if (close(fd) == -1)
	{
		perror("La fonction close a echoue");
		exit(EXIT_FAILURE);
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
		ft_close_fd(fds[n_newargv - 1][1];
		ft_close_fd(fds[n_newargv][0];
		ft_close_fds_around(fds, n_newargv);
	}
}

void	ft_close_all_execpt(int **fds, int n_newargv)
{
	ft_close_fd(fds[n_newargv][1]);
	while (n_newargv-- > 0)
	{
		ft_close_fd(fds[n_newargv][1];
		ft_close_fd(fds[n_newargv][0];
	}
}

void	ft_dup2(int newfd, int oldfd)
{
	if (dup2(newfd, oldfd) == -1)
	{
		perror("La fonction dup2 a echoue");
		exit(EXIT_FAILURE);
	}
}
