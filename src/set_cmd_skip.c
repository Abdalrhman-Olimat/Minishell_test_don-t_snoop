#include "../includes/mini.h"

void	set_status_skip(t_shell *shell, t_command_data **cmd, int *cmd_i, int status)
{
	cmd[*cmd_i]->skip_cmd = true;
	shell->exit_status = status;
}