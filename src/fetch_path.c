#include "../includes/mini.h"

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

