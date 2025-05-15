#include "../includes/mini.h"

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