/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abrun <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 12:20:46 by abrun             #+#    #+#             */
/*   Updated: 2021/10/12 12:49:25 by abrun            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_params(char ***newargv, char **paths,
				int **fds, char *heredoc)
{
	if (heredoc)
		free(heredoc);
	if (newargv)
		free_3dim_matc(newargv);
	if (paths)
		free_matc(paths);
	if (fds)
		free_mati(fds, 2);
}

void	free_params_main(char **paths, int **fds)
{
	if (paths)
		free_matc(paths);
	if (fds)
		free_mati(fds, 2);
}
