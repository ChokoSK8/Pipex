#include "pipex_bonus.h"

int	main(int ac, char **av)
{
	int		**fds;
	int		n_cmd;

	if (!strcmp(av[1], "here_doc"))
	{
		n_cmd = main_2(ac, av);
		return (n_cmd);
	}	
	if (!check_error(av, ac, 4))
		return (0);
	n_cmd = get_n_cmd(av, ac, 2);
	fds = make_pipes(n_cmd);
	if (!make_cmds(fds, n_cmd, av, ac))
		return (0);
	free(fds);
	return (1);
}

int	main_2(int ac, char **av)
{
	char	*heredoc;
	int		**fds;
	char	***newargv;

	if (!check_error(av, ac, 5))
		return (0);
	heredoc = get_heredoc(av);
	if (!heredoc)
		return (0);
	newargv = init_nw_2(av, ac);
	fds = make_pipes(2);
	if (!put_in_file(heredoc))
		return (0);
	if (!fds)
		return (0);
	if (!make_heredoc_cmd(fds, newargv, av, ac))
		return (0);
	unlink("file_tmp");
	return (1);
}
