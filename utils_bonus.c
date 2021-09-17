#include "pipex.h"

int	**make_pipes(int n_cmd)
{
	int		**fds;

	fds = malloc(sizeof(int *) * n_cmd);
	if (!fds)
		return (0);
	while (n_cmd--)
	{
		fds[n_cmd] = malloc(sizeof(int) * 2);
		if (!fds[n_cmd])
			return (0);
		if (pipe(fds[n_cmd]) == -1)
			return (0);
	}
	return (fds);
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
	

void	ft_dup2(int newfd, int oldfd)
{
	if (dup2(newfd, oldfd) == -1)
	{
		perror("La fonction dup2 a echoue");
		exit(EXIT_FAILURE);
	}
}
