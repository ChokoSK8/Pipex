#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

void    print_newargv(char **newargv)
{
	int	count;

	count = 0;
	while (newargv[count])
	{
		printf("newargv[%d] : %s\n", count, newargv[count]);
		count++;
	}
}

int		**make_pipes()
{
	int		count;
	int		**fds;

	count = 2;
	fds = malloc(sizeof(int *) * 2);
	if (!fds)
	{
		perror("Le malloc de fds a echoue");
		exit(EXIT_FAILURE);
	}
	while (count--)
	{
		fds[count] = malloc(sizeof(int) * 2);
		if (!fds[count])
		{
			perror("Le malloc d'un fds a echoue");
			exit(EXIT_FAILURE);
		}
		if (pipe(fds[count]) == -1)
		{
			perror("La fonction pipe a echoue");
			exit(EXIT_FAILURE);
		}
	}
	return (fds);
}

void	ft_close_fd(int fd)
{
	if (close(fd) == -1)
	{
		perror("La fonction close a echoue");
		exit(EXIT_FAILURE);
	}
}

int	ft_len_param(char **av, int n_av)
{
	int	len;
	int	count;

	count = n_av + 1;
	len = 0;
	while (av[count] && av[count][0] == '-')
	{
		len++;
		count++;
	}
	return (len);
}

int	get_n_av(int n, char **av)
{
	int	n_av;

	n_av = 2;
	while (n)
	{
		while (av[n_av + 1][0] == '-')
			n_av++;
		n--;
		n_av++;
	}
	return (n_av);
}

char	*get_last_param(char **av, int n_av, int n)
{
	char	*param;

	if (!n)
	{
		param = malloc(strlen(av[n_av - 1]));
		if (!param)
			return (0);
		strcpy(param, av[n_av - 1]);
	}
	else
		return (0);
	return (param);
}

char	**assign_param(char **newargv, int len_param, char **av, int n_av, int n)
{
	int	count;

	count = 1;
	while (len_param--)
	{
		newargv[count] = malloc(sizeof(strlen(av[n_av + count])));
		if (!newargv[count])
			return (0);
		strcpy(newargv[count], av[n_av + count]);
		count++;
	}
	newargv[count] = get_last_param(av, n_av, n);
	if (!newargv[count])
	{
		if (n)
			newargv[count] = 0;
		else
			return (0);
	}
	newargv[count + 1] = 0;
	return (newargv);
}

char	**ft_init_newargvs(char **av, int n)
{
	char	**newargv;
	int	len_param;
	int	count;
	int	n_av;

	n_av = get_n_av(n, av);
	len_param = ft_len_param(av, n_av);
	newargv = malloc(sizeof(char *) * (len_param + 3));
	if (!newargv)
		return (0);
	newargv[0] = malloc(strlen("/usr/bin/") + strlen(av[n_av]));
	if (!newargv[0])
		return (0);
	strcpy(newargv[0], "/usr/bin/");
	strcat(newargv[0], av[n_av]);
	newargv = assign_param(newargv, len_param, av, n_av, n);
	if (!newargv)
		return (0);
	return (newargv);
}

void	ft_cmd_1(int **fds, char **newargv, char **av)
{
	ft_close_fd(fds[0][0]);
	ft_close_fd(fds[1][0]);
	ft_close_fd(fds[1][1]);
	if (dup2(fds[0][1], STDOUT_FILENO) == -1)
	{
		perror("La fonction dup2 a echoue");
		exit(EXIT_FAILURE);
	}
	if (dup2(fds[0][1], STDERR_FILENO) == -1)
	{
		perror("La fonction dup2 a echoue");
		exit(EXIT_FAILURE);
	}
	ft_close_fd(fds[0][1]);
	newargv = ft_init_newargvs(av, 0);
	if (execve(newargv[0], newargv, NULL) == -1)
	{
		perror("La fonction execve a echoue");
		exit(EXIT_FAILURE);
	}
	//exit(EXIT_FAILURE);
}

void	ft_cmd_2(int **fds, char **newargv, char **av)
{
	ft_close_fd(fds[0][1]);
	ft_close_fd(fds[1][0]);
	if (dup2(fds[0][0], STDIN_FILENO) == -1)
	{
		perror("La fonction dup2 a echoue");
		exit(EXIT_FAILURE);
	}
	if (dup2(fds[1][1], STDOUT_FILENO) == -1)
	{
		perror("La fonction dup2 a echoue");
		exit(EXIT_FAILURE);
	}
	if (dup2(fds[1][1], STDERR_FILENO) == -1)
	{
		perror("La fonction dup2 a echoue");
		exit(EXIT_FAILURE);
	}
	ft_close_fd(fds[0][0]);
	ft_close_fd(fds[1][1]);
	newargv = ft_init_newargvs(av, 1);
	if (execve(newargv[0], newargv, NULL) == -1)
	{
		perror("La fonction execve a echoue");
		exit(EXIT_FAILURE);
	}
	exit(EXIT_FAILURE);
}

void	ft_write_in_file(int **fds, char **av, int ac)
{
	char	buf[100];
	int		ret;
	int		outfd;

	ft_close_fd(fds[0][0]);
	ft_close_fd(fds[0][1]);
	ft_close_fd(fds[1][1]);
	ret = read(fds[1][0], buf, 100);
	buf[ret] = 0;
	outfd = open(av[ac - 1], O_RDWR);
	ft_close_fd(fds[1][0]);
	write(outfd, buf, ret);
	close(outfd);
}

int		main(int ac, char ** av)
{
	pid_t	child_pid;
	int		**fds;
	int		file2;
	char	***newargv;

	//MALLOC NEWARGV
	newargv = malloc(sizeof(char **) * 2);
	if (!newargv)
	{
		perror("Le malloc de newargv a echoue");
		exit(EXIT_FAILURE);
	}

	//ON CREE LES PIPES
	fds = make_pipes();

	//ON CREE LE PROCESS ENFANT 1
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("La fonction fork a echoue");
		exit(EXIT_FAILURE);
	}

	//ON EXECUTE LE PROCESS ENFANT 1
	if (child_pid == 0)
		ft_cmd_1(fds, newargv[0], av);

	//ON CREE LE PROCESS ENFANT 2
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("La fonction fork a echoue");
		exit(EXIT_FAILURE);
	}
	
	//ON EXECUTE LE PROCESS ENFANT 2
	if (child_pid == 0)
		ft_cmd_2(fds, newargv[1], av);

	ft_write_in_file(fds, av, ac);
	return (1);
}
