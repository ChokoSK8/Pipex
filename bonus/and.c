#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

char	*ft_strjoin(char const *s1, const char *s2)
{
	size_t			s1_len;
	size_t			s2_len;
	char			*strjoin;
	size_t			strjoin_len;
	unsigned int	counter;

	counter = 0;
	s1_len = strlen(s1);
	s2_len = strlen(s2);
	strjoin_len = s1_len + s2_len + 1;
	strjoin = malloc(sizeof(char) * strjoin_len);
	if (!strjoin)
		return (NULL);
	while (counter < s1_len)
	{
		strjoin[counter] = s1[counter];
		counter++;
	}
	while (counter - s1_len < s2_len)
	{
		strjoin[counter] = s2[counter - s1_len];
		counter++;
	}
	strjoin[counter] = '\0';
	return (strjoin);
}

int	main(int ac, char **av)
{
	char	buf[100];
	int		ret;
	char	*p;

	p = malloc(1);
	if (!p)
		return (0);
	*p = 0;
	ret = 2;
	while (ret > 0)
	{
		write(STDOUT_FILENO, "pipe heredoc > ", 16);
		ret = read(STDOUT_FILENO, buf, 100);
		buf[ret] = 0;
		if (strncmp(buf, av[1], strlen(av[1])))
			p = ft_strjoin(p, buf);
		else
			ret = 0;
	}
	printf("buf : %s", p);
	free(p);
	return (1);
}
