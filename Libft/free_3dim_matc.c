/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_3dim_matc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:12:16 by abrun             #+#    #+#             */
/*   Updated: 2021/10/11 19:53:45 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

void	free_3dim_matc(char ***matc)
{
	int	n;
	int	n_2;

	n = 0;
	while (matc[n])
	{
		printf("n : %d\n", n);
		n_2 = 0;
		print_matc(matc[n]);
		while (matc[n][n_2])
		{
			printf("n_2 : %d\n", n_2);
			free(matc[n][n_2]);
			n_2++;
		}
		free(matc[n]);
	//	free_matc(matc[n]);
		n++;
	}
	free(matc);
}
