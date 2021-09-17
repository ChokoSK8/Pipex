#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "pipex.h"

int	check_error(char **av, int ac)
{
	int	n_cmd;

	n_cmd = get_n_cmd(av, ac);
	if (n_cmd < 0)
	{
		perror("zsh: parse error near '\\n'");
		return (0);
	}
	if (n_cmd < 2)
		return (0);
	return (1);
}

int	get_n_cmd(char **av, int ac)
{
	int		count;
	int		n_cmd;
	char	*path;

	count = 2;
	n_cmd = 0;
	while (count < ac)
	{
		path = malloc(ft_strlen("/usr/bin/") + strlen(av[count]) + 1);
		if (!path)
			return (0);
		ft_strcpy(path, "/usr/bin/");
		ft_strcat(path, av[count]);
		if (!access(path, X_OK))
		{
			if (count < ac - 1)
				n_cmd++;
			else
				n_cmd = -1;
		}
		free(path);
		count++;
	}
	return (n_cmd);
}
