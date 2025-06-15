/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahirzall <ahirzall@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:12:40 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:18:35 by ahirzall         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static int	tell_to_stop(t_command_data *cmds)
{
	if (cmds->fd_of_heredoc != -1)
	{
		close(cmds->fd_of_heredoc);
		cmds->fd_of_heredoc = -1;
	}
	return (0);
}

static int	handle_heredoc_interruption(t_shell *shell, t_command_data *cmd)
{
	cmd->skip_all_execution = true;
	shell->heredoc_interrupted = true;
	shell->exit_status = 130;
	return (1);
}

static int	process_single_heredoc(t_shell *shell, t_command_data *cmd, int j)
{
	tell_to_stop(cmd);

	if (process_heredoc(shell, cmd, j))
		return (handle_heredoc_interruption(shell, cmd));

	if (g_signal == 130)
		return (handle_heredoc_interruption(shell, cmd));

	return (0);
}

static int	process_all_heredocs(t_shell *shell, t_command_data *cmd, size_t rlt_slm)
{
	int j = 0;

	while (rlt_slm && cmd->delim[j]
		&& j <= cmd->index_of_heredoc
		&& !cmd->skip_all_execution)
	{
		if (process_single_heredoc(shell, cmd, j))
			return (1);
		j++;
	}
	return (0);
}

static int	should_process_heredoc(t_shell *shell, int i, size_t rlt_slm)
{
	return (FT > 0 && shell->cmds && shell->cmds[i]
		&& rlt_slm && shell->cmds[i]->content_analyze.is_there_heredoc);
}

static int	iter_on_herdoc(t_shell *shell, int i, int j, size_t rlt_slm)
{
	if (should_process_heredoc(shell, i, rlt_slm))
	{
		if (process_all_heredocs(shell, shell->cmds[i], rlt_slm))
			return (1);
	}

	if (shell->cmds && shell->cmds[i] && shell->cmds[i]->skip_all_execution)
		return (close_wth_free(FT, shell->cmds, shell->cmds[i]->fd_of_heredoc));

	return (0);
}

int	execute_here_doc(t_shell *shell, int i, int j, size_t rlt_slm)
{
	i++;
	if (!rlt_slm || !shell->cmds || !shell->cmds[i])
		return (3);
	while (shell->cmds && shell->cmds[i])
	{
		if (shell->heredoc_interrupted)
		{
			shell->exit_status = 130;
			return (0);
		}
		if (iter_on_herdoc(shell, i, j, rlt_slm))
		{
			shell->heredoc_interrupted = true;
			shell->exit_status = 130;
			return (0);
		}
		if (g_signal == 130)
		{
			shell->heredoc_interrupted = true;
			shell->exit_status = 130;
			return (0);
		}
		i++;
	}
	return (3);
}
