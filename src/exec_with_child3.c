#include "../includes/mini.h"

void	free_and_fetch_pth(t_shell *sh, t_command_data *cmd)
{
    if (sh->analyzing_data.path)
        free_paths_shell(sh);
    sh->analyzing_data.path = fetch_path(sh, 0);
}

void handle_failure_of_pth(t_shell *sh, t_command_data *cmd)
{
    if (!sh->analyzing_data.path)
       handle_path_failure(sh, cmd);
}