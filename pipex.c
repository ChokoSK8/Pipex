#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "pipex.h"

int	main(int ac, char **av)
{
	pid_t	child_pid;
	int		**fds;
	char	***newargv;

	if (!check_error(av, ac))
		return (0);
	newargv = ft_init_newargvs(av, ac);
	if (!newargv)
		return (0);
	fds = make_pipes();
	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
		ft_cmd_1(fds, newargv[0]);
	child_pid = fork();
	if (child_pid == -1)
		return (0);
	if (child_pid == 0)
		ft_cmd_2(fds, newargv[1]);
	ft_write_in_file(fds, av, ac);
	free(newargv);
	free(fds);
	return (1);
}
