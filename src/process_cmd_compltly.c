#include "../includes/mini.h"

int process_cmd_compltly(t_shell *shell, int cmd_iter, t_pipe_data *pipe_data)
{
	int	is_child;
	int	stdin_backup;
	int	stdout_backup;

	shell->cmds[cmd_iter]->main_cmd = shell->cmds;
	is_child = shell->cmds[cmd_iter]->content_analyze.is_there_pipe 
				|| (cmd_iter > 0 && shell->cmds[cmd_iter - 1]->content_analyze.is_there_pipe);
	if (shell->cmds[cmd_iter]->skip_cmd)
		return (skip_piped_cmd(shell->cmds[cmd_iter], pipe_data));
	if (!is_child)
	{
		handle_no_pipes_command(shell->cmds[cmd_iter], &stdin_backup, &stdout_backup);
		if (is_built_in(shell->cmds[cmd_iter]))
		{
			exec_builtin(shell, shell->cmds[cmd_iter], &stdin_backup, &stdout_backup);	
			return (0);
		}
	}
	*(pipe_data->got_forked) = true;

	shell->cmds[cmd_iter]->content_analyze.stdin_backup = stdin_backup;
	shell->cmds[cmd_iter]->content_analyze.stdout_backup = stdout_backup;
	exec_with_child(shell, shell->cmds[cmd_iter], pipe_data, cmd_iter);
		// exec_with_child(shell->cmds[i], pipe_data, i);
	switch_pipes(pipe_data->pipe_fd, pipe_data->prev_pipe, shell->cmds, cmd_iter);
}
