#include "../includes/mini.h"

void	full_close_pipes(t_pipe_data *pipe_data)
{
	if (pipe_data->prev_pipe[0] != -1)
	{
		close(pipe_data->prev_pipe[0]);
		pipe_data->prev_pipe[0] = -1;
	}
	if (pipe_data->pipe_fd[0] != -1)
	{
		close(pipe_data->pipe_fd[0]);
		pipe_data->pipe_fd[0] = -1;
	}
	if (pipe_data->pipe_fd[1] != -1)
	{
		close(pipe_data->pipe_fd[1]);
		pipe_data->pipe_fd[1] = -1;
	}
	if (pipe_data->prev_pipe[1] != -1)
	{
		close(pipe_data->prev_pipe[1]);
		pipe_data->prev_pipe[1] = -1;
	}
}