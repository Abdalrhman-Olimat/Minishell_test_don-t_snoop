/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_cleanup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 05:42:15 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/30 14:48:54 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

/*
 * This function performs a comprehensive cleanup of all dynamically
 * allocated memory in a child process before it exits.
 * 
 * It's designed to ensure no memory leaks are reported when a child
 * process exits through execve or direct exit calls.
 */
void	cleanup_child_process(t_shell *shell)
{
	t_input *tmp;
	t_input *current;
	int i;

	// Free token list
	if (shell->tokens)
	{
		current = shell->tokens;
		while (current)
		{
			tmp = current->next;
			if (current->string)
				free(current->string);
			free(current);
			current = tmp;
		}
		shell->tokens = NULL;
	}

	// Free token_header
	if (shell->tokens_header)
	{
		current = shell->tokens_header;
		while (current)
		{
			tmp = current->next;
			if (current->string)
				free(current->string);
			free(current);
			current = tmp;
		}
		shell->tokens_header = NULL;
	}

	// Free any tracked heredoc nodes
	for (i = 0; i < shell->heredoc_tracker.count && i < 100; i++)
	{
		if (shell->heredoc_tracker.nodes[i])
		{
			if (shell->heredoc_tracker.nodes[i]->string)
				free(shell->heredoc_tracker.nodes[i]->string);
			free(shell->heredoc_tracker.nodes[i]);
		}
	}
	shell->heredoc_tracker.count = 0;

	// Free args array if it exists
	if (shell->analyzing_data.args)
	{
		for (i = 0; shell->analyzing_data.args[i]; i++)
			free(shell->analyzing_data.args[i]);
		free(shell->analyzing_data.args);
		shell->analyzing_data.args = NULL;
	}

	// Clean up any expansion buffers
	// They'll be in dynamically allocated memory that might not be tracked
}
