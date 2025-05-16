#include "../includes/mini.h"

void	free_big_malloc_cmds(size_t err_num, t_command_data **cmds, int i)
{
	if (!cmds)
		return ;
	if (i == -1)
	{
		while (cmds[++i])
		{
			if (cmds[i]->cmd_splitted)
				free_2d(cmds[i]->cmd_splitted);
			free(cmds[i]->in_file);
			free(cmds[i]->out_file);
			free(cmds[i]->cmd_full);
			if (cmds[i]->cmd_path && !err_num)
				free(cmds[i]->cmd_path);
			if (cmds[i]->delim)
				free_2d(cmds[i]->delim);
			free(cmds[i]);
		}
		free(cmds);
	}
}