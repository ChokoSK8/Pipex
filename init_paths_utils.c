/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_paths_linux_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/11 16:46:56 by abrun             #+#    #+#             */
/*   Updated: 2021/10/11 16:55:06 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_line_step_1(char *buf, int fd, int *ret)
{
	char	*line;

	*ret = read(fd, buf, 10);
	if (*ret < 0)
		return (0);
	buf[*ret] = 0;
	line = ft_strdup(buf, ft_strlen(buf));
	return (line);
}
