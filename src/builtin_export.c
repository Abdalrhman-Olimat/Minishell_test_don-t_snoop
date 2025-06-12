/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:45:55 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 15:51:09 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static int	is_valid_identifier(const char *str)
{
	int	i;

	if (!str || !*str)
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

int	get_name_length(const char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

static void	print_sorted_env(char **envp)
{
	int		count;
	char	**sorted;
	int		i;
	int		j;
	char	*tmp;

	count = 0;
	while (envp[count])
		count++;
	sorted = ft_calloc(count + 1, sizeof(char *));
	if (!sorted)
		return ;
	i = 0;
	while (envp[i])
	{
		sorted[i] = ft_strdup(envp[i]);
		i++;
	}
	sorted[i] = NULL;
	i = 0;
	while (i < count - 1)
	{
		j = i + 1;
		while (j < count)
		{
			if (ft_strcmp(sorted[i], sorted[j]) > 0)
			{
				tmp = sorted[i];
				sorted[i] = sorted[j];
				sorted[j] = tmp;
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (sorted[i])
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(sorted[i], 1);
		ft_putchar_fd('\n', 1);
		free(sorted[i]);
		i++;
	}
	free(sorted);
}

static char	*merge_export_value(char **args, int *index)
{
	char	*joined;
	char	*tmp;
	int		i;

	i = *index;
	joined = ft_strdup(args[i]);
	while (args[i] && (ft_strchr(args[i], '\'') == NULL && ft_strchr(args[i],
				'\"') == NULL))
	{
		tmp = ft_strjoin(joined, " ");
		free(joined);
		joined = ft_strjoin(tmp, args[i + 1]);
		free(tmp);
		i++;
	}
	*index = i;
	return (joined);
}

int	ft_export(char **args, t_analyzing_data *analyze)
{
	int		i;
	char	*equal_sign;
	char	*var_name;
	char	*merged;

	if (!args[1])
	{
		print_sorted_env(analyze->envp);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '=') == NULL && args[i + 1] && args[i
				+ 1][0] != '\0')
			merged = merge_export_value(args, &i);
		else
			merged = ft_strdup(args[i]);
		equal_sign = ft_strchr(merged, '=');
		if (equal_sign)
			var_name = ft_substr(merged, 0, equal_sign - merged);
		else
			var_name = ft_strdup(merged);
		if (!is_valid_identifier(var_name))
		{
			ft_putstr_fd("export: `", 2);
			ft_putstr_fd(var_name, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
		}
		else if (equal_sign)
			add_or_update(analyze, merged);
		free(var_name);
		free(merged);
		i++;
	}
	return (0);
}
