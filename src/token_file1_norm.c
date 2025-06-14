/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_file1_norm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:39:14 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/14 11:08:32 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

t_input	*cleanup_tokenizer(t_tokenizer_state *state)
/*
 * Cleans up resources used by the tokenizer
 * Frees the token list, buffer, and head pointer
 * Returns NULL to indicate failure in the calling function
 */
{
	if (state && state->head && *state->head)
	{
		free_list(*state->head);
		*state->head = NULL;
	}
	if (state && state->token_buf)
	{
		free(state->token_buf);
		state->token_buf = NULL;
	}
	if (state && state->head)
	{
		free(state->head);
		state->head = NULL;
	}
	return (NULL);
}

void	cleanup_tokenizer_state(t_tokenizer_state *state)
{
	free(state->token_buf);
	free(state->head);
}

int	handle_quote_in_token(t_tokenizer_state *state)
{
	char	quote;

	quote = state->input[state->i];
	state->token_buf[state->token_index++] = state->input[state->i++];
	if (!state->in_quotes)
	{
		state->in_quotes = 1;
		state->quote_char = quote;
	}
	else if (state->quote_char == quote)
	{
		state->in_quotes = 0;
		if (state->quote_char == '\"')
		{
		}
	}
	return (1);
}

int	handle_quotes(t_tokenizer_state *state)
{
	int		qindex;
	char	quote;
	char	*quoted_buf;
	bool	is_double_quote;

	quote = state->input[state->i];
	is_double_quote = (quote == '\"');
	quoted_buf = malloc(state->len + 1);
	qindex = 0;
	if (!quoted_buf)
		return (malloc_error1());
	if (state->token_index > 0)
	{
		fush_token_buffer(state);
	}
	state->i++;
	while (state->i < state->len && state->input[state->i] != quote)
		quoted_buf[qindex++] = state->input[state->i++];
	if (state->i < state->len && state->input[state->i] == quote)
		state->i++;
	else
		return (unclosed_norm(state, quoted_buf));
	quoted_buf[qindex] = '\0';
	return (create_quoted_node(state, quoted_buf, is_double_quote));
}

int	process_token(t_tokenizer_state *state)
{
	char	quote;

	quote = state->input[state->i];
	if ((state->input[state->i] == ' ' || state->input[state->i] == '\t')
		&& !state->in_quotes)
	{
		handle_whitespace(state);
		return (1);
	}
	if (state->input[state->i] == '\'' || state->input[state->i] == '\"')
		return (handle_quote_in_token(state));
	if (!state->in_quotes && (state->input[state->i] == '|'
			|| state->input[state->i] == '<' || state->input[state->i] == '>'))
	{
		if (state->token_index > 0)
		{
			state->token_buf[state->token_index] = '\0';
			append_node(state->head, state->token_buf, TYPE_WORD);
			state->token_index = 0;
		}
		/* Call handle_metacharacters which handles double tokens like << and >> */
		if (handle_metacharacters(state))
			return (1);
	}
	state->token_buf[state->token_index++] = state->input[state->i++];
	return (1);
}
