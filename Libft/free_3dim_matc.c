/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_3dim_matc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 18:12:16 by abrun             #+#    #+#             */
/*   Updated: 2021/10/13 12:53:13 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_3dim_matc(char ***matc)
{
	int	n;

	n = 0;
	while (matc[n])
	{
		free_matc(matc[n]);
		n++;
	}
	free(matc);
}
