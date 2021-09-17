/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:21:18 by abrun             #+#    #+#             */
/*   Updated: 2021/09/16 10:09:17 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strcat(char *dst, const char *src)
{
	size_t			dstlen;
	unsigned int	counter;
	size_t			srclen;

	counter = 0;
	dstlen = 0;
	srclen = ft_strlen(src);
	while (dst[dstlen])
		dstlen++;
	while (src[counter])
	{
		dst[dstlen + counter] = src[counter];
		counter++;
	}
	dst[dstlen + counter] = '\0';
	return (dstlen + srclen);
}
