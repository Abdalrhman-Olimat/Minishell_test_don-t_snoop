/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:45:55 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:49:17 by aeleimat         ###   ########.fr       */
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

static void	handle_export_arg(char *arg, t_analyzing_data *analyze,
		bool **is_from_expansion)
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
		if (is_from_expansion != NULL)
			**is_from_expansion = true;
	}
	free(var_name);
}

static bool	has_unclosed_quotes(char *arg)
{
	char	*first_single;
	char	*last_single;
	char	*first_double;
	char	*last_double;

	first_single = ft_strchr(arg, '\'');
	last_single = ft_strrchr(arg, '\'');
	first_double = ft_strchr(arg, '\"');
	last_double = ft_strrchr(arg, '\"');
	if (first_single != NULL && last_single == first_single)
		return (true);
	if (first_double != NULL && last_double == first_double)
		return (true);
	return (false);
}

static bool	should_merge_export_value(char **args, int i)
{
	return (ft_strchr(args[i], '=') && args[i + 1]
		&& has_unclosed_quotes(args[i]));
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
		if (should_merge_export_value(args, i))
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
