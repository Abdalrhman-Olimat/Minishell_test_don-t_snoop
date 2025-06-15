/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_child.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:09:24 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:04:33 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static void	close_prev_pipe(t_pipe_data *pipe, int i)
{
	if (i > 0 && pipe->prev_pipe[0] != -1)
	{
		close(pipe->prev_pipe[0]);
		pipe->prev_pipe[0] = -1;
		if (pipe->prev_pipe[1] != -1)
		{
			close(pipe->prev_pipe[1]);
			pipe->prev_pipe[1] = -1;
		}
	}
}

static void	connect_pipe_output(t_command_data *cmd, t_pipe_data *pipe)
{
	if (cmd->content_analyze.is_there_pipe)
	{
		dup2(pipe->pipe_fd[1], STDOUT_FILENO);
		close(pipe->pipe_fd[0]);
		close(pipe->pipe_fd[1]);
	}
}

static void	apply_heredoc(t_command_data *cmd)
{
	if (cmd->content_analyze.is_there_heredoc)
	{
		dup2(cmd->fd_of_heredoc, STDIN_FILENO);
		close(cmd->fd_of_heredoc);
	}
}

static void	close_all_other_heredocs(t_command_data *cmd)
{
	int	j;

	j = -1;
	while (cmd->main_cmd[++j])
		if (cmd->main_cmd[j] != cmd
			&& cmd->main_cmd[j]->content_analyze.is_there_heredoc)
			close(cmd->main_cmd[j]->fd_of_heredoc);
}

int	exec_child_setting(t_command_data *cmd, t_pipe_data *pipe, int i, int j)
{
	(void)j;
	connect_pipe_input(cmd, pipe, i);
	close_prev_pipe(pipe, i);
	apply_heredoc(cmd);
	close_all_other_heredocs(cmd);
	connect_pipe_output(cmd, pipe);
	handle_redirections(cmd);
	return (0);
}
