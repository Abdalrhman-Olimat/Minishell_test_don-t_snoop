#include "../includes/mini.h"

int switch_pipes(int *pipe_fd, int *prev_pipe, t_command_data **cmd, int i)
{
	if (i > 0 && cmd[i - 1]->content_analyze.is_there_pipe)
	{
		close(prev_pipe[0]);
		if (prev_pipe[1] != -1)
			close(prev_pipe[1]);
	}
	if (cmd[i]->content_analyze.is_there_pipe)
	{
		if (cmd[i + 1] && (cmd[i + 1]->content_analyze.is_there_infile 
			|| cmd[i + 1]->content_analyze.is_there_heredoc))
		{
			close(pipe_fd[1]);
			prev_pipe[0] = pipe_fd[0];
			prev_pipe[1] = -1;
		}
		else
		{
			prev_pipe[0] = pipe_fd[0];
			prev_pipe[1] = pipe_fd[1];
		}
	}
	else
	{
		prev_pipe[0] = -1;
		prev_pipe[1] = -1;
	}
	return (0);
}
