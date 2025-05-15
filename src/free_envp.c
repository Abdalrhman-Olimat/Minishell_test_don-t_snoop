#include "../includes/mini.h"

void free_envp(t_shell *shell)
{
    int i = 0;
    if (!shell || !shell->middle_some.envp)
        return;
    while (shell->middle_some.envp[i])
    {
        free(shell->middle_some.envp[i]);
        i++;
    }
    free(shell->middle_some.envp);
    shell->middle_some.envp = NULL;
}