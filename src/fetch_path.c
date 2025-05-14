#include "../includes/mini.h"

char **fetch_path(t_shell *shell, int i)
{
	char **paths = getenv("PATH");
	
	while (NULL != shell->someone.envp[i])
	{
		if (ft_strncmp(shell->someone.envp[i], "PATH=", 5) == 0)
		{
			paths = ft_split(shell->someone.envp[i] + 5, ':');
			return (paths);
		}
		i++;
	}
	return (NULL);
}

