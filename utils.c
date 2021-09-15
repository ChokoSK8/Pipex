#include "pipex.h"

int	**make_pipes(void)
{
	int		count;
	int		**fds;

	count = 2;
	fds = malloc(sizeof(int *) * 2);
	if (!fds)
		return (0);
	while (count--)
	{
		fds[count] = malloc(sizeof(int) * 2);
		if (!fds[count])
			return (0);
		if (pipe(fds[count]) == -1)
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

void	ft_dup2(int newfd, int oldfd)
{
	if (dup2(newfd, oldfd) == -1)
	{
		perror("La fonction dup2 a echoue");
		exit(EXIT_FAILURE);
	}
}
