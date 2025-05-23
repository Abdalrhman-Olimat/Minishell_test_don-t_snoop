#include "../includes/mini.h"

int free_both_envp_paths(t_shell *shell)
{
	if (shell->analyzing_data.envp)
		free_envp(shell);
	if (shell->analyzing_data.path)
		free_paths_shell(shell);
	return (0);
}


