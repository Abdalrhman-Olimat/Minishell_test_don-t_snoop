#include "../includes/mini.h"

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