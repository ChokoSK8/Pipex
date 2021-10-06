#include "libft.h"

int	ft_matlen(char **mat)
{
	int		matlen;

	matlen = 0;
	while (mat[matlen])
		matlen++;
	return (matlen);
}
