#include "pipex_bonus.h"

char	***ft_init_newargvs_b(char **av, int ac, int n_cmd)
{
	char	***newargv;
	int		n_av;
	int		count;
	int		pt_av;

	newargv = malloc(sizeof(char **) * n_cmd);
	if (!newargv)
		return (0);
	count = -1;
	pt_av = 2;
	while (++count < n_cmd)
	{
		n_av = get_n_av(pt_av + 1, av, ac);
		newargv[count] = malloc(sizeof(char *) * (n_av + 3));
		if (!newargv[count])
			return (0);
		newargv[count] = assign_param(newargv[count], av, n_av, pt_av);
		if (!newargv[count])
			return (0);
		pt_av += n_av + 1;
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
		path = malloc(ft_strlen("/usr/bin/") + ft_strlen(av[pt_av + n_av]) + 1);
		if (!path)
			return (0);
		ft_strcpy(path, "/usr/bin/");
		ft_strcat(path, av[pt_av + n_av]);
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
		param = malloc(ft_strlen(av[pt_av - 1]) + 1);
		if (!param)
			return (0);
		ft_strcpy(param, av[pt_av - 1]);
	}
	else
		return (0);
	return (param);
}

char	*assign_first(char **av, int pt_av)
{
	char	*first;

	first = malloc(ft_strlen("/usr/bin/") + ft_strlen(av[pt_av]) + 1);
	if (!first)
		return (0);
	ft_strcpy(first, "/usr/bin/");
	ft_strcat(first, av[pt_av]);
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
		newargv[count] = malloc(sizeof(ft_strlen(av[pt_av]) + 1));
		if (!newargv[count])
			return (0);
		ft_strcpy(newargv[count], av[pt_av]);
		count++;
		pt_av++;
	}
	if (pt_av == 2 + count)
	{
		newargv[count] = malloc(ft_strlen(av[1]) + 1);
		if (!newargv[count])
			return (0);
		ft_strcpy(newargv[count++], av[1]);
	}
	newargv[count] = 0;
	return (newargv);
}
