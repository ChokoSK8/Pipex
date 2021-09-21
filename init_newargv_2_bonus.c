#include "pipex_bonus.h"

char	***init_nw_2(char **av, int ac)
{
	char	***newargv;
	int		count;
	int		n_av;
	int		pt_av;

	newargv = malloc(sizeof(char **) * 2);
	if (!newargv)
		return (0);
	count = -1;
	pt_av = 3;
	while (++count < 2)
	{
		n_av = get_n_av(pt_av + 1, av, ac);
		newargv[count] = malloc(sizeof(char *) * (n_av + 3));
		if (!newargv[count])
			return (0);
		newargv[count] = assign_param_2(newargv[count], av, n_av, pt_av);
		if (!newargv[count])
			return (0);
		pt_av += n_av + 1;
	}
	return (newargv);
}

char	**assign_param_2(char **newargv, char **av, int n_av, int pt_av)
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
	if (pt_av == 3 + count)
	{
		newargv[count] = malloc(ft_strlen("file_tmp") + 1);
		if (!newargv[count])
			return (0);
		ft_strcpy(newargv[count++], "file_tmp");
	}
	newargv[count] = 0;
	return (newargv);
}
