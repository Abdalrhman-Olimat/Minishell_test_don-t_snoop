#include "../includes/mini.h"

static bool has_pipe_relation(t_shell *sh, int i)
{
	return (sh->cmds[i]->content_analyze.is_there_pipe ||
			(i > 0 && sh->cmds[i - 1]->content_analyze.is_there_pipe));
}

static void restore_io_if_needed(int in_fd, int out_fd)
{
	if (in_fd != -1)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != -1)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
}

int process_cmd_compltly(t_shell *shell, int cmd_i, t_pipe_data *pipes)
{
	bool is_child;
	int in_bk;
	int out_bk;

	shell->cmds[cmd_i]->main_cmd = shell->cmds;
	is_child = has_pipe_relation(shell, cmd_i);
	if (shell->cmds[cmd_i]->skip_cmd)
		return (skip_piped_cmd(shell->cmds[cmd_i], pipes));
	if (!is_child)
	{
		handle_no_pipes_command(shell->cmds[cmd_i], &in_bk, &out_bk);
		if (is_built_in(shell->cmds[cmd_i]))
		{
			exec_builtin(shell, shell->cmds[cmd_i], &in_bk, &out_bk);
			restore_io_if_needed(in_bk, out_bk);
			return (0);
		}
	}
	shell->cmds[cmd_i]->content_analyze.stdin_backup = in_bk;
	shell->cmds[cmd_i]->content_analyze.stdout_backup = out_bk;
	exec_with_child(shell, shell->cmds[cmd_i], pipes, cmd_i);
	switch_pipes(pipes->pipe_fd, pipes->prev_pipe, shell->cmds, cmd_i);
	return (0);
}

/*
int process_cmd_compltly(t_shell *shell, int cmd_iter, t_pipe_data *pipe_data)
{
	bool	is_child;
	int	stdin_backup;
	int	stdout_backup;

	shell->cmds[cmd_iter]->main_cmd = shell->cmds;
	is_child = (shell->cmds[cmd_iter]->content_analyze.is_there_pipe) || 
				(cmd_iter > 0 && shell->cmds[cmd_iter - 1]->content_analyze.is_there_pipe);
	if (shell->cmds[cmd_iter]->skip_cmd)
		return (skip_piped_cmd(shell->cmds[cmd_iter], pipe_data));
	if (!is_child)
	{
		handle_no_pipes_command(shell->cmds[cmd_iter], &stdin_backup, &stdout_backup);
		if (is_built_in(shell->cmds[cmd_iter]))
		{
			exec_builtin(shell, shell->cmds[cmd_iter], &stdin_backup, &stdout_backup);	
			if (stdin_backup != -1)
			{
				dup2(stdin_backup, STDIN_FILENO);
				close(stdin_backup);
			}
			if (stdout_backup != -1)
			{
				dup2(stdout_backup, STDOUT_FILENO);
				close(stdout_backup);
			}
			return (0);
		}
	}

	shell->cmds[cmd_iter]->content_analyze.stdin_backup = stdin_backup;
	shell->cmds[cmd_iter]->content_analyze.stdout_backup = stdout_backup;
	exec_with_child(shell, shell->cmds[cmd_iter], pipe_data, cmd_iter);
		// exec_with_child(shell->cmds[i], pipe_data, i);
	switch_pipes(pipe_data->pipe_fd, pipe_data->prev_pipe, shell->cmds, cmd_iter);
	return (0);
}
*/
