/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:12:40 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:05:55 by aeleimat         ###   ########.fr       */
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

static int	iter_on_herdoc(t_shell *shell, int i, int j, size_t rlt_slm)
{
	if (FT > 0 && shell->cmds && shell->cmds[i])
	{
		if (rlt_slm && shell->cmds[i]->content_analyze.is_there_heredoc)
		{
			j = 0;
			while (rlt_slm && shell->cmds[i]->delim[j]
				&& j <= shell->cmds[i]->index_of_heredoc
				&& (shell->cmds[i]->skip_all_execution == false))
			{
				tell_to_stop(shell->cmds[i]);
				if (process_heredoc(shell, shell->cmds[i], j))
				{
					shell->cmds[i]->skip_all_execution = true;
					shell->heredoc_interrupted = true;
					shell->exit_status = 130;
					return (1);
				}
				if (g_signal == 130)
				{
					shell->cmds[i]->skip_all_execution = true;
					shell->heredoc_interrupted = true;
					shell->exit_status = 130;
					return (1);
				}
				j++;
			}
		}
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
