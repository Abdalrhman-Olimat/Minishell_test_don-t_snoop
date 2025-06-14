/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:44:24 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 15:44:24 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static int	is_valid_env_key(const char *key)
{
	int	k;

	if (!key || !*key)
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	k = 1;
	while (key[k])
	{
		if (!ft_isalnum(key[k]) && key[k] != '_')
			return (0);
		k++;
	}
	return (1);
}

static int	index_of_env(char **envp, const char *target)
{
	int	idx;
	int	namelen;

	if (!envp || !target)
		return (-1);
	namelen = ft_strlen(target);
	idx = 0;
	while (envp[idx])
	{
		if (ft_strncmp(envp[idx], target, namelen) == 0
			&& envp[idx][namelen] == '=')
			return (idx);
		idx++;
	}
	return (-1);
}

static void	exclude_variable_at(char **envp, int idx, int step_in)
{
	int	i;

	if (step_in > 1)
	{
		if (step_in && envp[idx])
			free(envp[idx]);
		i = idx;
		while (envp[i + 1])
		{
			envp[i] = envp[i + 1];
			i++;
		}
		envp[i] = NULL;
	}
}

static void	remove_if_exists(const char *var_name, char **envp)
{
	int	position;

	position = index_of_env(envp, var_name);
	if (position != -1)
		exclude_variable_at(envp, position, VALID_FREE);
}

int	ft_unset(char **argv, t_analyzing_data *context)
{
	int	i;

	if (!argv || !argv[1] || !context || !context->envp)
		return (0);
	i = 1;
	while (argv[i])
	{
		if (!is_valid_env_key(argv[i]))
		{
			ft_putstr_fd("unset: `", 2);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			i++;
			continue ;
		}
		remove_if_exists(argv[i], context->envp);
		unsetenv(argv[i]);
		i++;
	}
	return (0);
}
