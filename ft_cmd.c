#include "pipex.h"

void	ft_cmd_1(int **fds, char **newargv)
{
	ft_close_fd(fds[0][0]);
	ft_close_fd(fds[1][0]);
	ft_close_fd(fds[1][1]);
	ft_dup2(fds[0][1], STDOUT_FILENO);
	ft_close_fd(fds[0][1]);
	if (access(newargv[0], X_OK))
	{
		perror("zsh: command not found");
		exit(EXIT_FAILURE);
	}
	if (execve(newargv[0], newargv, NULL) == -1)
	{
		perror("La fonction execve 1 a echoue");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

void	ft_cmd_2(int **fds, char **newargv)
{
	ft_close_fd(fds[0][1]);
	ft_close_fd(fds[1][0]);
	ft_dup2(fds[0][0], STDIN_FILENO);
	ft_dup2(fds[1][1], STDOUT_FILENO);
	ft_dup2(fds[1][1], STDERR_FILENO);
	ft_close_fd(fds[0][0]);
	ft_close_fd(fds[1][1]);
	if (execve(newargv[0], newargv, NULL) == -1)
	{
		perror("La fonction execve 2 a echoue");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

int	get_outfd(char *file)
{
	int	outfd;

	if (!access(file, F_OK))
	{
		if (!access(file, W_OK))
		{
			outfd = open(file, O_TRUNC | O_WRONLY);
		}
		else
		{
			outfd = 0;
			perror("zsh: permission denied: outfile");
		}
	}
	else
	{
		outfd = open(file, O_CREAT | O_RDWR | O_TRUNC,
				S_IRUSR | S_IRGRP | S_IWUSR | S_IROTH);
	}
	return (outfd);
}

int	ft_write_in_file(int **fds, char **av, int ac)
{
	int		outfd;
	char	*str_file;

	ft_close_fd(fds[0][0]);
	ft_close_fd(fds[0][1]);
	ft_close_fd(fds[1][1]);
	str_file = get_str_file(fds[1][0]);
	if (!str_file)
		return (0);
	ft_close_fd(fds[1][0]);
	outfd = get_outfd(av[ac - 1]);
	if (outfd < 0)
		return (0);
	write(outfd, str_file, ft_strlen(str_file));
	close(outfd);
	return (1);
}
