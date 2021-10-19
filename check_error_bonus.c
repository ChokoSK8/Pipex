/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <abrun@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 11:03:57 by abrun             #+#    #+#             */
/*   Updated: 2021/10/19 12:53:08 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*init_cmd(char *path, char *av)
{
	char	*cmd;

	cmd = malloc(ft_strlen(path) + ft_strlen(av) + 1);
	if (!cmd)
		return (0);
	ft_strcpy(cmd, path);
	ft_strcat(cmd, av);
	return (cmd);
}
