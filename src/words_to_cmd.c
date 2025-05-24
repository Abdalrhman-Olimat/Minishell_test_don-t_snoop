#include "../includes/mini.h"

int	words_to_cmd(t_shell *shell, t_input *token, t_command_data **cmd, int *cmd_i)
{
	if (cmd[*cmd_i]->cmd_full[0] == '\0')
	{
		ft_strlcpy(cmd[*cmd_i]->cmd_full, token->string, MAXIMUM_CMD_SIZE);
	}
	else
	{
		ft_strlcat(cmd[*cmd_i]->cmd_full, " ", MAXIMUM_CMD_SIZE);
		ft_strlcat(cmd[*cmd_i]->cmd_full, token->string, MAXIMUM_CMD_SIZE);
	}
	return (0);
}

/*
int	words_to_cmd(t_shell *shell, t_input *token, t_command_data **cmd, int *cmd_i)
{
	char *full_cmd;
	
	ft_strlcat(cmd[*cmd_i]->cmd_full, " ", MAXIMUM_CMD_SIZE);
	ft_strlcat(cmd[*cmd_i]->cmd_full, token->string, MAXIMUM_CMD_SIZE);
	full_cmd = ft_strtrim(cmd[*cmd_i]->cmd_full, " \t\n\v\f\r");
	free (cmd[*cmd_i]->cmd_full);
	cmd[*cmd_i]->cmd_full = full_cmd;
}
*/