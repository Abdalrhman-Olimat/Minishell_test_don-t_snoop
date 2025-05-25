#include "../includes/mini.h"

static int is_path_var(char *entry)
{
	return (entry && ft_strncmp(entry, "PATH=", 5) == 0);
}

static char **split_path_value(char *entry)
{
	if (!entry)
		return (NULL);
	return (ft_split(entry + 5, ':'));
}

char **fetch_path(t_shell *shell, int i)
{
	char **paths;

	while (shell->analyzing_data.envp[i])
	{
		if (is_path_var(shell->analyzing_data.envp[i]))
		{
			paths = split_path_value(shell->analyzing_data.envp[i]);
			return (paths);
		}
		i++;
	}
	return (NULL);
}


/*
char **fetch_path(t_shell *shell, int i)
{
	char **paths;
	
	while (NULL != shell->analyzing_data.envp[i])
	{
		if (ft_strncmp(shell->analyzing_data.envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(shell->analyzing_data.envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}
*/