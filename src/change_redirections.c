/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 03:51:12 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:01:20 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	change_redirections(t_command_data *cmd, int *stdin_backup,
		int *stdout_backup)
{
	*stdout_backup = dup(STDOUT_FILENO);
	*stdin_backup = dup(STDIN_FILENO);
	redirect_infile(cmd);
	redirect_outfile(cmd);
	redirect_append_or_heredoc(cmd);
	return (0);
}
