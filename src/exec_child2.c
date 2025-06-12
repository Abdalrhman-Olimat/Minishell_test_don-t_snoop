/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:45:06 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 04:45:22 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	redir_fd(const char *file, int flags, int std_fd)
{
	int	fd;

	fd = open(file, flags, 0644);
	if (fd == -1)
		exit_err_str("File not found");
	dup2(fd, std_fd);
	close(fd);
}

void	handle_redirections(t_command_data *cmd)
{
	if (cmd->content_analyze.is_there_infile)
		redir_fd(cmd->in_file, O_RDONLY, STDIN_FILENO);
	if (cmd->content_analyze.is_there_outfile)
		redir_fd(cmd->out_file, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
	if (cmd->content_analyze.is_there_appendfile)
		redir_fd(cmd->out_file, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
}

int	connect_pipe_input(t_command_data *cmd, t_pipe_data *pipe, int i)
{
	if (i > 0 && pipe->prev_pipe[0] != -1
		&& !cmd->content_analyze.is_there_heredoc
		&& !cmd->content_analyze.is_there_infile)
	{
		dup2(pipe->prev_pipe[0], STDIN_FILENO);
	}
	return (0);
}
