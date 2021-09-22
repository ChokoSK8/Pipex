#include "pipex_bonus.h"

int	check_error(char **av, int ac, int len_av)
{
	int	n_cmd;

	if (ac < len_av)
		return (0);
	if (access(av[1], R_OK))
	{
		perror("Le 2e argument n'est un fichier valide");
		return (0);
	}
	n_cmd = get_n_cmd(av, ac, len_av - 2);
	if (n_cmd < 0)
	{
		perror("zsh: parse error near '\\n'");
		return (0);
	}
	return (1);
}

int	get_n_cmd(char **av, int ac, int from)
{
	int		count;
	int		n_cmd;
	char	*path;

	count = from;
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
