#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "pipex_bonus.h"

int	main(int ac, char **av)
{
	pid_t	child_pid;
	int		**fds;
	char	***newargv;
	int		n_cmd;
	int		n_newargv;

	if (!check_error(av, ac))
		return (0);
	n_cmd = get_n_cmd(av, ac);
	newargv = ft_init_newargvs_b(av, ac, n_cmd);
	if (!newargv)
		return (0);
	fds = make_pipes(n_cmd);
	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
		ft_cmd_1(fds, newargv[0]);
	n_newargv = 1;
	if (n_cmd > 2)
	{
		while (n_cmd > 2)
		{
			child_pid = fork();
			if (child_pid == 0)
				ft_cmd_n(fds, newargv[n_newargv]);
			n_newargv++;
			n_cmd--;
		}
	}		
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
		ft_cmd_2(fds, newargv[n_newargv]);
	ft_write_in_file(fds, av, ac);
	free(newargv);
	free(fds);
	return (1);
}
