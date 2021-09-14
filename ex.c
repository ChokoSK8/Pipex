#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>

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

int	get_av_len(char **av)
{
	int	av_len;

	av_len = 0;
	while (av[av_len])
		av_len++;
	return (av_len);
}

char	*get_last_param(char **av, int n_av, int n)
{
	char	*param;
	int	av_len;

	av_len = 0;
	if (!n)
	{
		param = malloc(strlen(av[n_av - 1]));
		if (!param)
			return (0);
		strcpy(param, av[n_av - 1]);
	}
	else
	{
		av_len = get_av_len(av);
		param = malloc(strlen(av[av_len - 1]));
		if (!param)
			return (0);
		strcpy(param, av[av_len - 1]);
	}
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
	newargv[count + 1] = 0;
	return (newargv);
}

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

char	**ft_init_newargvs(char **av, char *pathname, int n)
{
	char	**newargv;
	int	len_param;
	int	count;
	int	tmp;
	int	n_av;

	n_av = get_n_av(n, av);
	len_param = ft_len_param(av, n_av);
	newargv = malloc(sizeof(char *) * (len_param + 3));
	if (!newargv)
		return (0);
	newargv[0] = malloc(strlen(pathname) + strlen(av[n_av]));
	if (!newargv[0])
		return (0);
	strcpy(newargv[0], pathname);
	strcat(newargv[0], av[n_av]);
	newargv = assign_param(newargv, len_param, av, n_av, n);
	if (!newargv)
		return (0);
	return (newargv);
}

int	ft_child(int *filedes, char **newargv)
{
	if (close(filedes[0]) == -1)
	{
		perror("La fonction close a echoue");
		return (0);
	}
	if (dup2(filedes[1], STDOUT_FILENO) == -1)
	{
		perror("La fonction dup2 a echoue");
		return (0);
	}
	if (dup2(filedes[1], STDERR_FILENO) == -1)
	{
		perror("La fonction dup2 a echoue");
		return (0);
	}
	if (close(filedes[1]) == -1)
	{
		perror("La fonction close a echoue");
		return (0);
	}
	if (execve(newargv[0], newargv, NULL) == -1)
	{
		perror("La fonction execve a echoue");
		return (0);
	}
}

int	ft_father(int *filedes, char ***newargv, char **av, char *pathname, int fd, int tmp)
{
	if (close(filedes[1]) == -1)
	{
		perror("La fonction close a echoue");
		return (0);
	}
	if (dup2(filedes[0], STDIN_FILENO) == -1)
	{
		perror("La fonction dup2 a echoue");
		return (0);
	}
	if (close(filedes[0]) == -1)
	{
		perror("La fonction close a echoue");
		return (0);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("La fonction dup2 a echoue");
		return (0);
	}
	if (dup2(tmp, STDOUT_FILENO) == -1)
	{
		perror("La fonction dup2 a echoue");
		return (0);
	}
	newargv[1] = ft_init_newargvs(av, pathname, 1);
	newargv[1][2] = 0;
	if (execve(newargv[1][0], newargv[1], NULL) == -1)
	{
		perror("La fonction execve a echoue");
		close(1);
		return (0);
	}
	return (1);
}

int	get_buf_len(int fd)
{
	int	buf_len;
	int	ret;
	char	buf[100];

	ret = read(fd, buf, 100);
	buf_len = ret;
	while (ret)
	{
		ret = read(fd, buf, 100);
		buf_len += ret;
	}
	return (buf_len);
}

int	ft_write_in_file(int *filedes, char **newargv, int tmp)
{
	char	*buf;
	int	buf_len;

	close(filedes[1]);
	buf_len = get_buf_len(tmp);
	printf("buf_len : %d\n", buf_len);
	if (close(filedes[0]) == -1)
	{
		perror("La fonction close a echoue");
		return (-1);
	}
	filedes[0] = open("tmp.txt", O_RDWR);
	if (filedes[0] < 0)
		return (0);
	buf = malloc(buf_len);
	if (!buf)
		return (0);
	read(filedes[0], buf, buf_len);
	buf[buf_len] = 0;
	printf("buf : %s\n", buf);
	close(filedes[0]);
	filedes[0] = open(newargv[get_av_len(newargv)], O_RDWR);
	if (filedes[0] < 0)
		return (0);
	return (1);
}	

int	main(int ac, char **av)
{
	char	*pathname;
	char	***newargv;
	int	filedes[2];
	pid_t	child_pid;
	int	fd;

	pathname = malloc(strlen("/usr/bin/"));
	if (!pathname)
		return (0);
	strcpy(pathname, "/usr/bin/");
	newargv = malloc(sizeof(char **) * 2);
	if (!newargv)
		return (0);
	newargv[0] = ft_init_newargvs(av, pathname, 0);
	if (!newargv[0])
		return (0);
	fd = open("tmp.txt", O_CREAT | O_RDWR);
	if (fd < 0)
		return (0);
	if (pipe(filedes) == -1)
	{
		perror("La fonction pipe a echoue");
		return (0);
	}
	child_pid = fork();
	if (child_pid == -1)
	{
		perror("La fonction fork a echoue");
		return (0);
	}
	if (child_pid == 0)
		if (!(ft_child(filedes, newargv[0])))
			return (0);
	child_pid = fork();
	int tmp = open ("hello.txt", O_RDWR);
	if (child_pid == 0)
		if (!(ft_father(filedes, newargv, av, pathname, fd, tmp)))
			return (0);
	if (!(ft_write_in_file(filedes, newargv[1], tmp)))
		return (0);
	return (1);
}