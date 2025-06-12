/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_paths.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:55:28 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 04:55:29 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	**free_paths_shell(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->analyzing_data.path)
	{
		while (shell->analyzing_data.path[i])
		{
			free(shell->analyzing_data.path[i]);
			i++;
		}
		free(shell->analyzing_data.path);
	}
	return (NULL);
}

char	**free_path(char **paths)
{
	int	i;

	i = 0;
	if (paths)
	{
		while (paths[i])
		{
			free(paths[i]);
			i++;
		}
		free(paths);
	}
	return (NULL);
}
