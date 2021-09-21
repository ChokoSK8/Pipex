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
	int	fd;

	if (ac < 5)
		return (0);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		perror("Le 2e argument n'est un fichier valide");
		return (0);
	}
	close(fd);
	n_cmd = get_n_cmd(av, ac);
	if (n_cmd < 0)
	{
		perror("zsh: parse error near '\\n'");
		return (0);
	}
	if (n_cmd > 2)
	{
		perror("Il n'y a pas exactement 2 commandes");
		return (0);
	}
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
		printf("path : %s\n", path);
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
	printf("n_cmd : %d\n", n_cmd);
	return (n_cmd);
}
