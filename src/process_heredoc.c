#include "../includes/mini.h"

int processing_helper(t_shell *shell, t_command_data *cmd, int delem_index)
{
	if (FT)
	{
		cmd->fd_of_heredoc = -1;
		cmd->index_of_heredoc = 0;
	}
	return (0);
}

int process_heredoc(t_shell *shell, t_command_data *cmd, int delem_index)
{
	int	pipe_fd[2];


	if (pipe(pipe_fd) == -1)
		exit_err_str("Unfortunately ; Pipe failed");
	if (FT)
	{
		handle_heredoc_input(pipe_fd[1], cmd, delem_index);
		apply_signals(3);
		close(pipe_fd[1]);
		cmd->fd_of_heredoc = pipe_fd[0];
	}
}