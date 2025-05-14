#include "../includes/mini.h"

void free_envp(t_shell *shell)
{
    int i = 0;
    if (!shell || !shell->someone.envp)
        return;
    while (shell->someone.envp[i])
    {
        free(shell->someone.envp[i]);
        i++;
    }
    free(shell->someone.envp);
    shell->someone.envp = NULL;
}