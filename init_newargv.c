#include "pipex.h"

char	***ft_init_newargvs(char **av, int ac)
{
	char	***newargv;
	int		n_av;
	int		count;
	int		pt_av;

	newargv = malloc(sizeof(char **) * 2);
	if (!newargv)
		return (0);
	count = -1;
	pt_av = 2;
	while (++count < 2)
	{
		n_av = get_n_av(pt_av + 1, av, ac);
		newargv[count] = malloc(sizeof(char *) * (n_av + 3));
		if (!newargv[count])
			return (0);
		newargv[count] = assign_param(newargv[count], av, n_av, pt_av);
		if (!newargv[count])
			return (0);
		if (pt_av == 2)
			pt_av++;
		pt_av += n_av;
	}
	return (newargv);
}

int	get_n_av(int pt_av, char **av, int ac)
{
	int		n_av;
	int		loop;
	char	*path;

	n_av = -1;
	loop = 1;
	while (loop && n_av + pt_av < ac - 1)
	{
		n_av++;
		path = malloc(ft_strlen("/usr/bin/") + strlen(av[pt_av + n_av]));
		if (!path)
			return (0);
		strcpy(path, "/usr/bin/");
		strcat(path, av[pt_av + n_av]);
		if (!access(path, X_OK))
			loop = 0;
		free(path);
	}
	return (n_av);
}

char	*get_last_param(char **av, int pt_av)
{
	char	*param;

	if (!av[pt_av])
	{
		param = malloc(strlen(av[pt_av - 1]));
		if (!param)
			return (0);
		strcpy(param, av[pt_av - 1]);
	}
	else
		return (0);
	return (param);
}

char	*assign_first(char **av, int pt_av)
{
	char	*first;

	first = malloc(strlen("/usr/bin/") + strlen(av[pt_av]));
	if (!first)
		return (0);
	strcpy(first, "/usr/bin/");
	strcat(first, av[pt_av]);
	return (first);
}

char	**assign_param(char **newargv, char **av, int n_av, int pt_av)
{
	int	count;

	count = 0;
	newargv[count] = assign_first(av, pt_av);
	if (!newargv[count++])
		return (0);
	pt_av++;
	while (n_av--)
	{
		newargv[count] = malloc(sizeof(strlen(av[pt_av])));
		if (!newargv[count])
			return (0);
		strcpy(newargv[count], av[pt_av]);
		count++;
		pt_av++;
	}
	if (pt_av == 2 + count)
	{
		newargv[count] = malloc(strlen(av[1]));
		if (!newargv[count])
			return (0);
		strcpy(newargv[count++], av[1]);
	}
	newargv[count] = 0;
	return (newargv);
}
