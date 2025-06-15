/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:53:51 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:07:52 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static int	is_path_var(char *entry)
{
	if (!entry)
		return (0);
	return (ft_strncmp(entry, "PATH=", 5) == 0);
}

static char	**split_path_value(char *entry)
{
	if (!entry)
		return (NULL);
	return (ft_split(entry + 5, ':'));
}

static char	**get_paths_from_env_entry(char *entry)
{
	if (is_path_var(entry))
		return (split_path_value(entry));
	return (NULL);
}

char	**fetch_path(t_shell *shell, int i)
{
	char	**paths;

	if (!shell || !shell->analyzing_data.envp)
		return (NULL);
	while (shell->analyzing_data.envp[i])
	{
		paths = get_paths_from_env_entry(shell->analyzing_data.envp[i]);
		if (paths)
			return (paths);
		i++;
	}
	return (NULL);
}
