#include "../includes/mini.h"

int change_redirections(t_command_data *command, int *stdin_backup, int *stdout_backup)
{
	int	fd;

	*stdout_backup = dup(STDOUT_FILENO);
	*stdin_backup = dup(STDIN_FILENO);
	if (command->content_analyze.is_there_infile)
	{
		fd = open(command->in_file, O_RDONLY);
		if (fd == -1)
			exit_err_str("File isn't exist or can't open.");
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (command->content_analyze.is_there_outfile)
	{
		fd = open(command->out_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (fd == -1)
			exit_err_str("File not found or not exist.");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	// setup_io_continued func;
	if (command->content_analyze.is_there_appendfile)
	{
		fd = open(command->out_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			exit_err_str("File not found or not exist.");
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (command->content_analyze.is_there_heredoc)
	{
		dup2(command->fd_of_heredoc, STDIN_FILENO);
		close(command->fd_of_heredoc);
	}
}
