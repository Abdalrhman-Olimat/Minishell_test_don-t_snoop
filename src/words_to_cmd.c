#include "../includes/mini.h"

int	words_to_cmd(t_shell *shell, t_input *token, t_command_data **cmd, int *cmd_i)
{
	ft_strlcat(cmd[*cmd_i]->cmd_full, " ", MAXIMUM_CMD_SIZE);
	ft_strlcat(cmd[*cmd_i]->cmd_full, token->string, MAXIMUM_CMD_SIZE);
}