/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play_after_tokens.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 05:54:29 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 19:52:41 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static t_input	*copy_of_tokens(t_shell *shell, t_input *head)
{
	t_input	*new_tokens;
	t_input	*current_node;
	t_input	*last_new;
	t_input	*new_node;

	if (!initialize_token_copy(shell, head, &new_tokens, &last_new))
		return (NULL);
	current_node = head;
	while (current_node != NULL)
	{
		new_node = create_token_node_copy(current_node);
		if (new_node == NULL)
		{
			free_list(new_tokens);
			return (NULL);
		}
		if (new_tokens == NULL)
			new_tokens = new_node;
		else
			last_new->next = new_node;
		last_new = new_node;
		current_node = current_node->next;
	}
	return (new_tokens);
}

static void	cleanup_tokens_and_cmds(t_shell *shell)
{
	if (shell->tokens)
	{
		free_list(shell->tokens);
		shell->tokens = NULL;
	}
	if (shell->cmds && shell->analyzing_data.cmds_count > 0)
	{
		free_cmds_all(shell->cmds, shell->analyzing_data.cmds_count, 0);
		shell->cmds = NULL;
	}
}

static void	handle_args_allocation_failure(t_shell *shell)
{
	ft_putstr_fd("Unfortunately .. an error occoured -> failed\
        in memory allocation for args\n",
		2);
	if (shell->tokens_header)
	{
		free_list(shell->tokens_header);
		shell->tokens_header = NULL;
	}
}

static void	cleanup_analyzing_args(t_shell *shell)
{
	int	token_count;

	if (shell->analyzing_data.args && shell->tokens_header)
	{
		token_count = count_tokens(shell->tokens_header);
		free_token_array(shell->analyzing_data.args, token_count);
		shell->analyzing_data.args = NULL;
	}
	else if (shell->analyzing_data.args)
	{
		free(shell->analyzing_data.args);
		shell->analyzing_data.args = NULL;
	}
}

void	play_after_tokens(t_shell *shell)
{
	char			**args;
	t_shell_returns	result;

	if (!shell || !shell->tokens)
		return ;
	args = tokens_to_array(shell->tokens);
	normalize_linked_list(shell->tokens);
	shell->tokens_header = copy_of_tokens(shell, shell->tokens);
	if (!args)
	{
		handle_args_allocation_failure(shell);
		return ;
	}
	shell->analyzing_data.args = args;
	result = cmds(shell, 1, 0);
	
	/* Don't proceed with command execution if we got SHELL_EXIT during heredoc */
	if (result == SHELL_EXIT || shell->heredoc_interrupted)
	{
		cleanup_analyzing_args(shell);
		cleanup_tokens_and_cmds(shell);
		return;
	}
	
	cleanup_analyzing_args(shell);
	cleanup_tokens_and_cmds(shell);
}
