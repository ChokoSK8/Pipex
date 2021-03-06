/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 12:17:09 by abrun             #+#    #+#             */
/*   Updated: 2021/10/11 15:33:12 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1, int len)
{
	size_t			s1_len;
	unsigned char	*dst;

	s1_len = ft_strlen(s1);
	if (len == -1)
		len = s1_len;
	else
		s1_len = len;
	dst = malloc(sizeof(char) * (s1_len + 1));
	if (!dst)
		return (NULL);
	while (s1_len--)
		*dst++ = *s1++;
	*dst = 0;
	return ((char *)dst - len);
}
