/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:45:27 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 15:48:51 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	find_env_var(char **envp, const char *name, int name_len)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0
			&& envp[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	update_env_var(char **envp, const char *var, int pos)
{
	free(envp[pos]);
	envp[pos] = ft_strdup(var);
}

void	add_env_var(t_analyzing_data *analyze, const char *var)
{
	char	**new_env;
	int		i;

	i = 0;
	while (analyze->envp[i])
		i++;
	new_env = ft_calloc(i + 2, sizeof(char *));
	if (!new_env)
		return ;
	i = 0;
	while (analyze->envp[i])
	{
		new_env[i] = analyze->envp[i];
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	free(analyze->envp);
	analyze->envp = new_env;
}

void	add_or_update(t_analyzing_data *analyze, const char *var)
{
	int	name_len;
	int	pos;

	name_len = get_name_length(var);
	pos = find_env_var(analyze->envp, var, name_len);
	if (pos >= 0)
		update_env_var(analyze->envp, var, pos);
	else
		add_env_var(analyze, var);
}
