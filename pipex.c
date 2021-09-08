#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>

int	ft_len_param(char **av, int n_av)
{
	int	len;
	int	count;

	count = n_av + 1;
	len = 0;
	while(av[count] && av[count][0] == '-')
	{
		len++;
		count++;
	}
	return len;
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
		if (!(param = malloc(strlen(av[n_av - 1]))))
			return 0;
		strcpy(param, av[n_av - 1]);
	}
	else
	{
		if (!(param = malloc(strlen("sortie.txt"))))
			return 0;
		strcpy(param, "sortie.txt");
	}
	return (param);
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
	if (!(newargv = malloc(sizeof(char *) * (len_param + 3))))
		return (0);
	if (!(newargv[0] = malloc(strlen(pathname) + strlen(av[n_av]))))
		return (0);
	strcpy(newargv[0], pathname);
	strcat(newargv[0], av[n_av]);
	count = 1;
	tmp = len_param;
	while (tmp--)
	{
		if (!(newargv[count] = malloc(sizeof(strlen(av[n_av + count])))))
			return 0;
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

char	*get_file_in_buf(char *av)
{
	char	*buf;
	int	len_buf;
	int	fd;
	char	c;

	fd = open(av, O_RDONLY);
	while (read(fd, &c, 1) == 1)
		len_buf++;
	close(fd);
	if (!(buf = malloc(len_buf + 1)))
	{
		perror("Un malloc a echoue");
		return (0);
	}
	fd = open(av, O_RDONLY);
	if (read(fd, buf, len_buf) != len_buf)
	{
		perror("La lecture de file1 a echoue");
		return (0);
	}
	buf[len_buf] = 0;
	return (buf);
}

int	main(int ac, char **av)
{
	int	fd;
	char	*pathname;
	int	status;
	char	***newargv;
	char	*newenviron[] = { NULL };
	int	filedes[2];
	char	buf[100];
	pid_t	child_pid;
//	char	*file1;
	int	fw;

	if (ac < 3)
		return 0;
	fd = open(av[1], O_RDONLY);	
	if (fd < 1)
		return 0;
	if (!(pathname = malloc(5 + strlen(av[2]) + 1)))
		return 0;
	strcpy(pathname, "/bin/");

	//init newargv
	if (!(newargv = malloc(sizeof(char **) * 2)))
		return (0);
	newargv[0] = ft_init_newargvs(av, pathname, 0);
        print_newargv(newargv[0]);

//	if (!(file1 = get_file_in_buf(av[1])))
//		return (0);

	if ((child_pid = fork()) == -1)
	{
		perror("erreur avec fork");
		return (0);
	}
	
	if (pipe(filedes) == -1)
	{
		perror("erreur ouverture pipe");
		return (0);
	}

	if (child_pid == 0)
	{
		close(filedes[0]);
		dup2(filedes[1], 1);
		execve(newargv[0][0], newargv[0], newenviron);
		wait(&status);
	}
	else
	{
		close(filedes[1]);
		int len_buf = read(filedes[0], buf, sizeof(buf));
		fw = open("sortie.txt", O_CREAT|S_IRWXU|O_RDWR);
		newargv[1] = ft_init_newargvs(av, pathname, 1);
        	print_newargv(newargv[1]);
		write(fw, buf, len_buf);
		execve(newargv[1][0], newargv[1], newenviron);
		wait(&status);
	}
	close(fd);
	return 1;
}
