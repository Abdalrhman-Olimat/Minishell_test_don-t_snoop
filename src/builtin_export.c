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

static int	get_name_length(const char *var)
{
	int	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}

static int	find_env_var(char **envp, const char *name, int name_len)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, name_len) == 0 && envp[i][name_len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	update_env_var(char **envp, const char *var, int pos)
{
	free(envp[pos]);
	envp[pos] = ft_strdup(var);
}

static void	add_env_var(t_analyzing_data *analyze, const char *var)
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

static void	add_or_update(t_analyzing_data *analyze, const char *var)
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
	while (args[i] && (ft_strchr(args[i], '\'') == NULL
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
		if (ft_strchr(args[i], '=') == NULL
			&& args[i + 1] && args[i + 1][0] != '\0')
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
