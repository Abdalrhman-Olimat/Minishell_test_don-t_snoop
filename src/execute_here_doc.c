/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_here_doc.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:12:40 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 04:32:23 by aeleimat         ###   ########.fr       */
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
	if (FT > 0)
	{
		if (rlt_slm && shell->cmds[i]->content_analyze.is_there_heredoc)
		{
			j = 0;
			while (rlt_slm && shell->cmds[i]->delim[j]
				&& j <= shell->cmds[i]->index_of_heredoc
				&& (shell->cmds[i]->skip_all_execution == false))
			{
				tell_to_stop(shell->cmds[i]);
				process_heredoc(shell, shell->cmds[i], j);
				j++;
			}
		}
	}
	if (shell->cmds[i]->skip_all_execution)
		return (close_wth_free(FT, shell->cmds, shell->cmds[i]->fd_of_heredoc));
	return (0);
}

int	execute_here_doc(t_shell *shell, int i, int j, size_t rlt_slm)
{
	i++;
	if (!rlt_slm || !shell->cmds[i])
	{
		return (3);
	}
	while (shell->cmds[i])
	{
		iter_on_herdoc(shell, i, j, rlt_slm);
		i++;
	}
	return (3);
}
