#include "../includes/mini.h"

static void initialize_null_fields(t_command_data *cmd)
{
	cmd->fd_of_heredoc = -1;
	cmd->cmd_splitted = NULL;
	cmd->cmd_path = NULL;
	cmd->cmd_full = NULL;
	cmd->in_file = NULL;
	cmd->out_file = NULL;
	cmd->delim = NULL;
}

static int allocate_fields(t_command_data *cmd)
{
	cmd->cmd_full = ft_calloc(MAXIMUM_CMD_SIZE, sizeof(char));
	cmd->in_file = ft_calloc(FILENAME_MAX, sizeof(char));
	cmd->out_file = ft_calloc(FILENAME_MAX, sizeof(char));
	cmd->delim = ft_calloc(10, sizeof(char*));  // Allocate for up to 10 heredoc delimiters
	if (!cmd->cmd_full || !cmd->in_file || !cmd->out_file || !cmd->delim)
		return (0);
	cmd->cmd_full[0] = '\0';
	return (1);
}

static void free_partial_allocs(t_command_data *cmd)
{
	if (cmd->cmd_full)
		free(cmd->cmd_full);
	if (cmd->in_file)
		free(cmd->in_file);
	if (cmd->out_file)
		free(cmd->out_file);
	if (cmd->delim)
		free(cmd->delim);
}

t_shell_returns prepare_command_struct(t_shell *shell, int i, int j)
{
	t_command_data *cmd;

	if (!shell->cmds[i] || j <= 0)
		return (SHELL_FAILURE);
	cmd = shell->cmds[i];
	ft_bzero(cmd, sizeof(t_command_data));
	initialize_null_fields(cmd);
	if (!allocate_fields(cmd))
	{
		free_partial_allocs(cmd);
		return (SHELL_FAILURE);
	}
	return (SHELL_SUCCESS);
}

