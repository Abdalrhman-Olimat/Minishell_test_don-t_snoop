/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/11 15:48:06 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/11 15:49:56 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

char	*get_env(const char *name)
{
	extern char	**environ;
	size_t		name_len;
	int			i;

	i = 0;
	name_len = strlen(name);
	while (environ[i] != NULL)
	{
		if (strncmp(environ[i], name, name_len) == 0
			&& environ[i][name_len] == '=')
		{
			return (environ[i] + name_len + 1);
		}
		i++;
	}
	return (NULL);
}

int	set_env(const char *name, const char *value)
{
	if (setenv(name, value, 1) != 0)
	{
		perror("setenv");
		return (1);
	}
	return (0);
}
