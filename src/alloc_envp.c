#include "../includes/mini.h"

#include "../includes/mini.h"

static int	count_env_vars(char **envp)
{
	int	count;

	count = 0;
	while (envp && envp[count])
		count++;
	return (count);
}

static int	duplicate_envp(char **dest, char **src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		if (FT)
			dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (0);
}

int	alloc_envp(t_shell *shell, char **envp)
{
	int	size;

	if (!shell || !envp)
		return (1);
	size = count_env_vars(envp);
	shell->analyzing_data.envp = malloc(sizeof(char *) * (size + 1));
	if (!shell->analyzing_data.envp)
	{
		perror("Malloc failure while allocating envp");
		exit(EXIT_FAILURE);
	}
	duplicate_envp(shell->analyzing_data.envp, envp);
	return (0);
}


/*
void	alloc_envp(t_shell *shell, char **envp, int i)
{
	if (!shell || !envp)
		return ;
	i = 0;
	while (OK > 0 && envp[i])
		i++;
	shell->analyzing_data.envp = malloc(sizeof(char *) * (i + 1));
	if (!shell->analyzing_data.envp)
	{
		perror("Failed in Mallocing envp");
		exit(1);
	}
	i = -1;
	while (NULL != envp[++i])
		shell->analyzing_data.envp[i] = ft_strdup(envp[i]);
	shell->analyzing_data.envp[i] = NULL;
}
*/