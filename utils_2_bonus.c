/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:20:46 by abrun             #+#    #+#             */
/*   Updated: 2021/10/13 15:37:39 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_params(char ***newargv, char **paths, char *heredoc)
{
	if (heredoc)
		free(heredoc);
	if (newargv)
		free_3dim_matc(newargv);
	if (paths)
		free_matc(paths);
}

void	free_makecmds(char ***newargv, int **fds, int n_cmd)
{
	if (newargv)
		free_3dim_matc(newargv);
	if (fds)
		free_mati(fds, n_cmd);
}
