#include "libft.h"

void	print_matc(char **mat)
{
	int		y;

	y = 0;
	while (mat[y])
	{
		write(1, mat[y], ft_strlen(mat[y]));
		write(1, "\n", 1);
		y++;
	}
}
