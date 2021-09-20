#include "pipex_bonus.h"

int	main(int ac, char **av)
{
	pid_t	child_pid;
	int		**fds;
	int		n_cmd;

	if (strcmp(av[1], "here_doc"))
	{
		n_cmd = main_2(ac, av);
		return (n_cmd);
	}	
	if (!check_error(av, ac))
		return (0);
	n_cmd = get_n_cmd(av, ac);
	fds = make_pipes(n_cmd);
	if (!make_cmds(fds, n_cmd, av, ac))
		return (0);
	free(fds);
	return (1);
}

char	*get_heredoc(av)
{
	char	*heredoc;
	char	buf[100];

	heredoc = malloc(1);
	if (!heredoc)
		return (0);
	*heredoc = 0;
	ret = 2;
	while (ret > 0)
	{
		write(STDOUT_FILENO, "pipe heredoc > ", 16);
		ret = read(STDOUT_FILENO, buf, 100);
		buf[ret] = 0;
		if (strncmp(buf, av[1], strlen(av[1])))
			heredoc = ft_strjoin(heredoc, buf);
		else
			ret = 0;
	}
	return (heredoc);
}

int	main_2(int ac, char **av)
{
	char	*heredoc;
	int		**fds;
	pid_t	child_pid;

	heredoc = get_heredoc;
	if (!heredoc)
		return (0);
	

