#include "../includes/mini.h"

static void	free_single_cmd_node(t_command_data *cmd)
{
	if (!cmd)
		return;
	
	// Use a safer approach with try-free pattern
	
	// Free basic string fields - avoid freeing NULL or invalid pointers
	if (cmd->cmd_full && cmd->cmd_full != (char *)0x1 && 
        cmd->cmd_full != (char *)0x2 && cmd->cmd_full != (char *)0x3)
		free(cmd->cmd_full);
        
	if (cmd->in_file && cmd->in_file != (char *)0x1 && 
        cmd->in_file != (char *)0x2 && cmd->in_file != (char *)0x3)
		free(cmd->in_file);
        
	if (cmd->out_file && cmd->out_file != (char *)0x1 && 
        cmd->out_file != (char *)0x2 && cmd->out_file != (char *)0x3)
		free(cmd->out_file);
        
	if (cmd->path_var && cmd->path_var != (char *)0x1 && 
        cmd->path_var != (char *)0x2 && cmd->path_var != (char *)0x3)
		free(cmd->path_var);
        
	if (cmd->cmd_path && cmd->cmd_path != (char *)0x1 && 
        cmd->cmd_path != (char *)0x2 && cmd->cmd_path != (char *)0x3)
		free(cmd->cmd_path);
	
	// Free arrays/2D arrays with safety check
	if (cmd->cmd_splitted && cmd->cmd_splitted != (char **)0x1 && 
        cmd->cmd_splitted != (char **)0x2 && cmd->cmd_splitted != (char **)0x3)
		free_2d_arr(cmd->cmd_splitted);
	
	// Free heredoc delimiters (each string in the array and then the array itself)
	if (cmd->delim && cmd->delim != (char **)0x1 && 
		cmd->delim != (char **)0x2 && cmd->delim != (char **)0x3)
	{
		int i = 0;
		while (cmd->delim && cmd->delim[i] != NULL)
		{
			if (cmd->delim[i] != (char *)0x1 && cmd->delim[i] != (char *)0x2 && 
                cmd->delim[i] != (char *)0x3)
				free(cmd->delim[i]);
			i++;
		}
		free(cmd->delim);
	}
	
	// Free the command structure itself
	free(cmd);
}

void	free_cmds_all(t_command_data **cmds, short count, int start_index)
{
	short index;

	if (!cmds)
		return;
	
	// Make sure start_index is valid
	if (start_index < 0)
		start_index = 0;
	
	index = start_index;
	while (index < count)
	{
		if (cmds[index])
			free_single_cmd_node(cmds[index]);
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