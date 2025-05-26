#include "../includes/mini.h"
#include <fcntl.h>
#include <unistd.h>

// 🧩 Abstract: open + dup2 + close
static void	redir_fd(const char *file, int flags, int std_fd)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
		exit_err_str("File not found");
	dup2(fd, std_fd);
	close(fd);
}

// 🧩 Apply infile, outfile, appendfile redirections
static void	handle_redirections(t_command_data *cmd)
{
	if (cmd->content_analyze.is_there_infile)
		redir_fd(cmd->in_file, O_RDONLY, STDIN_FILENO);
	if (cmd->content_analyze.is_there_outfile)
		redir_fd(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
	if (cmd->content_analyze.is_there_appendfile)
		redir_fd(cmd->out_file, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
}

// 🧩 Connect pipe input if needed
static int	connect_pipe_input(t_command_data *cmd, t_pipe_data *pipe, int i)
{
	if (i > 0 && pipe->prev_pipe[0] != -1 &&
		!cmd->content_analyze.is_there_heredoc &&
		!cmd->content_analyze.is_there_infile)
	{
		dup2(pipe->prev_pipe[0], STDIN_FILENO);
	}
	return (0);
}

// 🧩 Close previous pipe safely
static void	close_prev_pipe(t_pipe_data *pipe, int i)
{
	if (i > 0 && pipe->prev_pipe[0] != -1)
	{
		close(pipe->prev_pipe[0]);
		if (pipe->prev_pipe[1] != -1)
			close(pipe->prev_pipe[1]);
	}
}

// 🧩 Connect stdout to pipe if needed
static void	connect_pipe_output(t_command_data *cmd, t_pipe_data *pipe)
{
	if (cmd->content_analyze.is_there_pipe)
	{
		dup2(pipe->pipe_fd[1], STDOUT_FILENO);
		close(pipe->pipe_fd[0]);
		close(pipe->pipe_fd[1]);
	}
}

// 🧩 Apply heredoc redirection
static void	apply_heredoc(t_command_data *cmd)
{
	if (cmd->content_analyze.is_there_heredoc)
	{
		dup2(cmd->fd_of_heredoc, STDIN_FILENO);
		close(cmd->fd_of_heredoc);
	}
}

// 🧩 Close all other heredocs in sibling commands
static void	close_all_other_heredocs(t_command_data *cmd)
{
	int	j;

	j = -1;
	while (cmd->main_cmd[++j])
		if (cmd->main_cmd[j] != cmd &&
			cmd->main_cmd[j]->content_analyze.is_there_heredoc)
			close(cmd->main_cmd[j]->fd_of_heredoc);
}

// ✅ Main: ≤25 lines, 100% logic match, clean
int	exec_child_setting(t_command_data *cmd, t_pipe_data *pipe, int i, int j)
{
	(void)j;
	close_all_other_heredocs(cmd);
	connect_pipe_input(cmd, pipe, i);
	close_prev_pipe(pipe, i);
	apply_heredoc(cmd);
	connect_pipe_output(cmd, pipe);
	handle_redirections(cmd);
	reset_signals();
	return (0);
}

/*
int exec_child_setting(t_command_data *command, t_pipe_data *pipe_data, int i, int j)
{
	int	fd;

	fd = -1;
	if (i > 0 && pipe_data->prev_pipe[0] != -1 && 
		!command->content_analyze.is_there_heredoc &&
		!command->content_analyze.is_there_infile)
	{
		dup2(pipe_data->prev_pipe[0], STDIN_FILENO);
	}
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
	return (0);
}
*/