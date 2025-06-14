/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:12:40 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/14 10:27:59 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static void	parent_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
		/* We'll handle the newline in the prompt reset */
	}
}

int	processing_helper(t_shell *shell, t_command_data *cmd, int delem_index)
{
	if (FT)
	{
		cmd->fd_of_heredoc = -1;
		cmd->index_of_heredoc = 0;
	}
	return (0);
}

int	process_heredoc(t_shell *shell, t_command_data *cmd, int delem_index)
{
	int	pipe_fd[2];
	int	pid;
	int	status;

	if (pipe(pipe_fd) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
	{
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (1);
	}
	if (pid == 0)
	{
		signal(SIGINT, heredoc_signal_handler);
		signal(SIGQUIT, SIG_IGN);
		close(pipe_fd[0]);
		handle_heredoc_input(pipe_fd[1], cmd, delem_index);
		close(pipe_fd[1]);
		exit(0);
	}
	else
	{
		signal(SIGINT, parent_signal_handler);
		signal(SIGQUIT, SIG_IGN);
		close(pipe_fd[1]);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 130)
		{
			close(pipe_fd[0]);
			cmd->fd_of_heredoc = -1;
			cmd->skip_all_execution = true;
			shell->exit_status = 130;
			shell->heredoc_interrupted = true;
			return (1);
		}
		if (g_signal == 130)
		{
			close(pipe_fd[0]);
			cmd->fd_of_heredoc = -1;
			cmd->skip_all_execution = true;
			shell->exit_status = 130;
			shell->heredoc_interrupted = true;
			return (1);
		}
		cmd->fd_of_heredoc = pipe_fd[0];
	}
	return (0);
}
