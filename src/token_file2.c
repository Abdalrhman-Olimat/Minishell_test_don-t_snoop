/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_file2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 09:34:44 by aeleimat          #+#             */
/*   Updated: 2025/04/26 10:10:21 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	handle_whitespace(t_tokenizer_state *state)
/*
 * Processes whitespace characters in the input
 * Finalizes current token if needed and skips consecutive whitespace
 * May add a space to the next token if appropriate
 */
{
	if (state->token_index > 0)
		fush_token_buffer(state);
	while (state->i < state->len && (state->input[state->i] == ' '
			|| state->input[state->i] == '\t'))
		state->i++;
	if (state->i < state->len && state->input[state->i] != '|'
		&& state->input[state->i] != '<' && state->input[state->i] != '>'
		&& state->input[state->i] != '\'' && state->input[state->i] != '\"')
	{
		state->token_buf[state->token_index++] = ' ';
	}
}

int	handle_metacharacters2(t_tokenizer_state *state)
/*
 * Handles single metacharacters (|, <, >)
 * Creates appropriate token and advances the input position
 * Returns 1 if a metacharacter was handled, 0 otherwise
 */
{
	if (state->input[state->i] == '|')
	{
		append_node(state->head, "|", TYPE_PIPE);
		state->i++;
		return (1);
	}
	if (state->input[state->i] == '<')
	{
		append_node(state->head, "<", TYPE_REDIR_IN);
		state->i++;
		return (1);
	}
	if (state->input[state->i] == '>')
	{
		append_node(state->head, ">", TYPE_REDIR_OUT);
		state->i++;
		return (1);
	}
	return (0);
}

static int	append_heredoc_node(t_tokenizer_state *state, const char *node_text,
		int node_type)
{
	t_input	*node;
	t_input	*tmp;

	if (!state->head)
		return (0);
		
	/* Create node with the heredoc token */
	node = create_node(node_text, node_type);
	if (!node)
		return (0);
		
	/* Track heredoc node for proper cleanup */
	if (state->shell)
		track_heredoc_node(&state->shell->heredoc_tracker, node);
		
	/* Append to the list */
	if (!*state->head)
		*state->head = node;
	else
	{
		tmp = *state->head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = node;
	}
	return (1);
}

int	handle_metacharacters(t_tokenizer_state *state)
/*
 * Handles all metacharacters including compound ones (<<, >>)
 * Delegates to handle_metacharacters2 for single metacharacters
 * Returns 1 if a metacharacter was handled, 0 otherwise
 */
{
	/* First check for double metacharacters '<<' and '>>' */
	if (state->i + 1 < state->len)
	{
		/* Check for '<<' heredoc operator */
		if (state->input[state->i] == '<' && state->input[state->i + 1] == '<')
		{
			if (!append_heredoc_node(state, "<<", TYPE_HEREDOC))
				return (0);
			state->i += 2;
			return (1);
		}
		
		/* Check for '>>' append operator */
		if (state->input[state->i] == '>' && state->input[state->i + 1] == '>')
		{
			if (state->head)
			{
				append_node(state->head, ">>", TYPE_APPEND);
			}
			state->i += 2;
			return (1);
		}
	}
	
	/* For single metacharacters */
	return (handle_metacharacters2(state));
}

int	unclosed_norm(t_tokenizer_state *state, char *quoted_buf)
/*
 * Handles unclosed quote error condition
 * Frees allocated resources and returns error code
 */
{
	write(2, "Error: Unclosed quote\n", 23);
	if (state && state->head && *state->head)
	{
		free_list(*state->head);
		*state->head = NULL;
	}
	free(quoted_buf);
	return (0);
}
