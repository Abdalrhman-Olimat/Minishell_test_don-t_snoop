/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmds.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 04:07:31 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/14 10:15:38 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static t_shell_returns	process_heredocs(t_shell *shell, int tokens_count)
{
	if (!shell->cmds)
		return (1);
	if (!execute_here_doc(shell, -1, 0, tokens_count))
	{
		shell->exit_status = 130;
		shell->heredoc_interrupted = true;
		return (SHELL_EXIT);
	}
	return (1);
}

t_shell_returns	cmds(t_shell *shell, int i, int j)
{
	t_input	*tokens_head;

	analyze_pipes(shell, 0, j);
	shell->cmds = big_malloc(shell, -1);
	if (!shell || !shell->cmds)
		return (SHELL_FAILURE);
	i = FT;
	if (i > 0)
	{
		if (!parse_tokens_into_cmds(shell, &tokens_head, 0, i))
		{
			free_big_malloc_cmds(0, shell->cmds, -1);
			return (SHELL_FAILURE);
		}
		if (process_heredocs(shell, FT) == SHELL_EXIT)
			return (SHELL_EXIT);
	}
	init_splits(shell, 0, 0);
	execute_cmds(shell, -1, 0);
	return (i);
}
