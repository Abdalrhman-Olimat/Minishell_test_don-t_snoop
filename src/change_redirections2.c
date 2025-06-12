/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_redirections2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 03:51:16 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 03:51:17 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	redirect_to_append(t_command_data *cmd)
{
	int	fd;

	fd = open(cmd->out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		exit_err_str("Cannot append to file.");
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	redirect_to_heredoc(t_command_data *cmd)
{
	dup2(cmd->fd_of_heredoc, STDIN_FILENO);
	close(cmd->fd_of_heredoc);
}

void	redirect_append_or_heredoc(t_command_data *cmd)
{
	if (cmd->content_analyze.is_there_appendfile)
		redirect_to_append(cmd);
	if (cmd->content_analyze.is_there_heredoc)
		redirect_to_heredoc(cmd);
}
