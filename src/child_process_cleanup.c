/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_process_cleanup.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmad <ahmad@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 05:42:15 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/14 17:36:09 by ahmad            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static t_input	*free_input_list(t_input *head)
{
	t_input	*current;
	t_input	*tmp;

	current = head;
	while (current)
	{
		tmp = current->next;
		if (current->string)
			free(current->string);
		free(current);
		current = tmp;
	}
	return (NULL);
}

static char	**free_string_array(char **array)
{
	int	i;

	if (!array)
		return (NULL);
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

void	cleanup_child_process(t_shell *shell)
{
	int	i;

	if (shell->tokens)
		shell->tokens = free_input_list(shell->tokens);
	if (shell->tokens_header)
		shell->tokens_header = free_input_list(shell->tokens_header);
	i = 0;
	while (i < shell->heredoc_tracker.count && i < 100)
	{
		if (shell->heredoc_tracker.nodes[i])
		{
			if (shell->heredoc_tracker.nodes[i]->string)
				free(shell->heredoc_tracker.nodes[i]->string);
			free(shell->heredoc_tracker.nodes[i]);
		}
		i++;
	}
	shell->heredoc_tracker.count = 0;
	shell->analyzing_data.args = free_string_array(shell->analyzing_data.args);
}
