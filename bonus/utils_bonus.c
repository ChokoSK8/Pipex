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

void	ft_dup2(int newfd, int oldfd)
{
	if (dup2(newfd, oldfd) == -1)
	{
		perror("La fonction dup2 a echoue");
		exit(EXIT_FAILURE);
	}
}
