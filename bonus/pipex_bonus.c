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
	fds = make_pipes(n_cmd);
	if (!make_cmds(fds, n_cmd, av, ac))
		return (0);
	free(fds);
	return (1);
}
