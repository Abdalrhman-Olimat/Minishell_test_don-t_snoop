/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmad <ahmad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:45:55 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 11:24:56 by ahmad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	print_env(char **sorted)
{
	int	i;

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

char	*merge_export_value(char **args, int *index)
{
	char	*joined;
	char	*tmp;
	int		i;

	i = *index;
	joined = ft_strdup(args[i]);
	while (args[i] && args[i + 1] && (ft_strchr(args[i], '\'') == NULL
			&& ft_strchr(args[i], '\"') == NULL))
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

static void	handle_export_arg(char *arg, t_analyzing_data *analyze, bool **is_from_expansion)
{
	char	*equal_sign;
	char	*var_name;

	equal_sign = ft_strchr(arg, '=');
	if (equal_sign)
		var_name = ft_substr(arg, 0, equal_sign - arg);
	else
		var_name = ft_strdup(arg);
	if (!is_valid_identifier(var_name))
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(var_name, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else if (equal_sign)
	{
		add_or_update(analyze, arg);
		**is_from_expansion = true;
	}
	free(var_name);
}

int	ft_export(char **args, t_analyzing_data *analyze, bool *is_from_expansion)
{
	int		i;
	char	*merged;

	if (!args[1])
	{
		print_sorted_env(analyze->envp);
		return (0);
	}
	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '=') && args[i + 1] && 
		   ((ft_strchr(args[i], '\'') != NULL && ft_strrchr(args[i], '\'') == ft_strchr(args[i], '\'')) ||
			(ft_strchr(args[i], '\"') != NULL && ft_strrchr(args[i], '\"') == ft_strchr(args[i], '\"'))))
			merged = merge_export_value(args, &i);
		else
			merged = ft_strdup(args[i]);
		
		if (!merged)
			return (1);
		handle_export_arg(merged, analyze, &is_from_expansion);
		free(merged);
		i++;
	}
	return (0);
}
