#include "../includes/mini.h"

void free_envp(t_shell *shell)
{
    int i = 0;
    if (!shell || !shell->analyzing_data.envp)
        return;
    while (shell->analyzing_data.envp[i])
    {
        free(shell->analyzing_data.envp[i]);
        i++;
    }
    free(shell->analyzing_data.envp);
    shell->analyzing_data.envp = NULL;
}