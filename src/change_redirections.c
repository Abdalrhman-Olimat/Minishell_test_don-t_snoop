#include "../includes/mini.h"

static void	redirect_infile(t_command_data *cmd)
{
	int	fd;

	if (!cmd->content_analyze.is_there_infile)
		return ;
	fd = open(cmd->in_file, O_RDONLY);
	if (fd == -1)
		exit_err_str("Cannot open input file.");
	dup2(fd, STDIN_FILENO);
	close(fd);
}

static void	redirect_outfile(t_command_data *cmd)
{
	int	fd;

	if (!cmd->content_analyze.is_there_outfile)
		return ;
	fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		exit_err_str("Cannot open output file.");
	dup2(fd, STDOUT_FILENO);
	close(fd);
}


int	change_redirections(t_command_data *cmd, int *stdin_backup, int *stdout_backup)
{
	*stdout_backup = dup(STDOUT_FILENO);
	*stdin_backup = dup(STDIN_FILENO);
	redirect_infile(cmd);
	redirect_outfile(cmd);
	redirect_append_or_heredoc(cmd);
	return (0);
}


/*
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
	return (0);
}
*/
