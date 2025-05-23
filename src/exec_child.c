#include "../includes/mini.h"

int exec_child_setting(t_command_data *command, t_pipe_data *pipe_data, int i, int j)
{
	int	fd;

	fd = -1;
	if (i > 0 && pipe_data->prev_pipe[0] != -1 && 
		!command->content_analyze.is_there_heredoc &&
		!command->content_analyze.is_there_infile)
	dup2(pipe_data->prev_pipe[0], STDIN_FILENO);
	if (i > 0 && pipe_data->prev_pipe[0] != -1)
	{
		close(pipe_data->prev_pipe[0]);
		if (pipe_data->prev_pipe[1] != -1)
			close(pipe_data->prev_pipe[1]);
	}
	if (command->content_analyze.is_there_heredoc)
	{
		dup2(command->fd_of_heredoc, STDIN_FILENO);
		close(command->fd_of_heredoc);
	}
	// clean_main_command_fds();
	j = 0;
	while (command->main_cmd[j])
	{
		if (command->main_cmd[j] != command && 
			command->main_cmd[j]->content_analyze.is_there_heredoc
			&& command->main_cmd[j]->fd_of_heredoc != -1)
		close(command->main_cmd[j]->fd_of_heredoc);
		j++;
	}
	if (command->content_analyze.is_there_pipe)
	{
		dup2(pipe_data->pipe_fd[1], STDOUT_FILENO);
		close(pipe_data->pipe_fd[0]);
		close(pipe_data->pipe_fd[1]);
	}

	// setup_io_child_continued func;
	if (command->content_analyze.is_there_infile)
	{
		fd = open(command->in_file, O_RDONLY);
		if (fd == -1)
			exit_err_str("File not found or can't be opened");
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (command->content_analyze.is_there_outfile)
	{
		fd = open(command->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			exit_err_str("File not found");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (command->content_analyze.is_there_appendfile)
	{
		fd = open(command->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			exit_err_str("File not found");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}

	// Maybe Set Signal Handlers Here
}
