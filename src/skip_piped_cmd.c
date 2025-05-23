#include "../includes/mini.h"


int skip_piped_cmd(t_command_data *command, t_pipe_data *pipe_data)
{
	command->p_id = -1;
	if (command->content_analyze.is_there_pipe)
	{
		if (command->content_analyze.is_there_pipe)
			if (pipe(pipe_data->pipe_fd) == -1)
			{
				close(pipe_data->pipe_fd[1]);
				pipe_data->prev_pipe[0] = pipe_data->pipe_fd[0];
				pipe_data->prev_pipe[1] = -1;
				exit_err_str("Pipe failed");
			}	
	}
	return (0);
}
