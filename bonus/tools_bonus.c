#include "pipex_bonus.h"

void	print_newargv(char ***newargv, int n_newargv)
{
	int	count;
	int	n;

	count = 0;
	while (count < n_newargv)
	{
		n = 0;
		while (newargv[count][n])
		{
			printf("newargv[%d][%d] : %s\n", count, n, newargv[count][n]);
			n++;
		}
		count++;
	}
}
