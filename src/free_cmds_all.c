#include "../includes/mini.h"

static void	free_single_cmd_node(t_command_data *cmd)
{
	if (!cmd)
		return;
	if (cmd->cmd_full)
		free(cmd->cmd_full);
	if (cmd->in_file)
		free(cmd->in_file);
	if (cmd->out_file)
		free(cmd->out_file);
	if (cmd->delim)
		free(cmd->delim);
	free(cmd);
}

void	free_cmds_all(t_command_data **cmds, short count, int start_index)
{
	short index;

	index = start_index;
	while (index < count)
	{
		// free_single_cmd_node(cmds[index]); TODO FREE
		index++;
	}
	free(cmds);
}

/*
void	free_cmds_all(t_command_data **cmds, short count, int i)
{
	int j;

	j = 0;
	while (i > 0 && j < count)
	{
		if (NULL != cmds[i])
		{
			free(cmds[i]->cmd_full);
			free(cmds[i]->in_file);
			free(cmds[i]->out_file);
			free(cmds[i]->delim);
			free(cmds[i]);
		}
		i++;
	}
	free(cmds);
}
*/