#include "../includes/mini.h"

int execute_cmds(t_shell *shell, int i, int j)
{
	t_pipe_data pipe_data;

	init_execution_data(&pipe_data);
	while (shell->cmds[++i])
	{
		// printf("shell->cmds[%d] = %s\n", i, shell->cmds[i]->cmd_full);
		process_cmd_compltly(shell, i, &pipe_data);
	}
	full_close_pipes(&pipe_data);
	set_all_signals();
	// Signals shit
	if (pipe_data.got_forked)
		wait_children(shell, shell->cmds, 0, 0);
	return (0);
}