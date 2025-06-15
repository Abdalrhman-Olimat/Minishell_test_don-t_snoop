/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 20:40:06 by ahirzall          #+#    #+#             */
/*   Updated: 2025/06/15 20:40:07 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	processing_helper(t_shell *shell, t_command_data *cmd, int delem_index)
{
	if (FT)
	{
		cmd->fd_of_heredoc = -1;
		cmd->index_of_heredoc = 0;
	}
	return (0);
}

void	parent_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_signal = 130;
	}
}

int	validate_heredoc_params(t_shell *shell, t_command_data *cmd,
		int delem_index)
{
	if (cmd == NULL || cmd->delim == NULL || cmd->delim[delem_index] == NULL)
	{
		write(2, "Error: Invalid heredoc configuration\n", 36);
		shell->exit_status = 1;
		shell->heredoc_interrupted = true;
		return (1);
	}
	return (0);
}

int	create_pipe_and_fork(int *pipe_fd, int *pid)
{
	if (pipe(pipe_fd) == -1)
	{
		perror("pipe");
		return (1);
	}
	*pid = fork();
	if (*pid == -1)
	{
		perror("fork");
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		return (1);
	}
	return (0);
}

void	handle_child_process(int *pipe_fd, t_command_data *cmd, int delem_index)
{
	signal(SIGINT, heredoc_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	close(pipe_fd[0]);
	handle_heredoc_input(pipe_fd[1], cmd, delem_index);
	close(pipe_fd[1]);
	exit(0);
}
