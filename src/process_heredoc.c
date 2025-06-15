/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:12:40 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:40:19 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	cleanup_cat_command(t_command_data *cmd)
{
	if (cmd->cmd_full && ft_strcmp(cmd->cmd_full, "cat") == 0)
	{
		free(cmd->cmd_full);
		cmd->cmd_full = NULL;
		if (cmd->cmd_splitted)
		{
			free(cmd->cmd_splitted[0]);
			free(cmd->cmd_splitted);
			cmd->cmd_splitted = NULL;
		}
	}
}

int	handle_interruption(int pipe_fd, t_shell *shell, t_command_data *cmd)
{
	close(pipe_fd);
	cmd->fd_of_heredoc = -1;
	cmd->skip_all_execution = true;
	shell->exit_status = 130;
	shell->heredoc_interrupted = true;
	cleanup_cat_command(cmd);
	return (1);
}

int	handle_parent_process(int *pipe_fd, int pid, t_shell *shell,
		t_command_data *cmd)
{
	int	status;

	signal(SIGINT, parent_signal_handler);
	signal(SIGQUIT, SIG_IGN);
	close(pipe_fd[1]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status) && (WEXITSTATUS(status) == 130))
		return (handle_interruption(pipe_fd[0], shell, cmd));
	if (g_signal == 130)
		return (handle_interruption(pipe_fd[0], shell, cmd));
	cmd->fd_of_heredoc = pipe_fd[0];
	return (0);
}

int	process_heredoc(t_shell *shell, t_command_data *cmd, int delem_index)
{
	int	pipe_fd[2];
	int	pid;

	if (validate_heredoc_params(shell, cmd, delem_index))
		return (1);
	if (create_pipe_and_fork(pipe_fd, &pid))
		return (1);
	if (pid == 0)
		handle_child_process(pipe_fd, cmd, delem_index);
	else
		return (handle_parent_process(pipe_fd, pid, shell, cmd));
	return (0);
}
