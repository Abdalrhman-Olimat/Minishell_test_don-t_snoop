#include "../includes/mini.h"

char **fetch_path(t_shell *shell, int i)
{
	char **paths;
	
	while (NULL != shell->middle_some.envp[i])
	{
		if (ft_strncmp(shell->middle_some.envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(shell->middle_some.envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

