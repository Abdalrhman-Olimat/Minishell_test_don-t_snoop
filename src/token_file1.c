/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_file1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:37:31 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/28 23:00:02 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	malloc_error1(void)
{
	write(2, "Error: Memory allocation failed\n", 32);
	return (0);
}

int	handle_quotes(t_tokenizer_state *state)
{
	int		qindex;
	char	quote;
	char	*quoted_buf;
	bool    is_double_quote;

	quote = state->input[state->i];
	is_double_quote = (quote == '\"');  // Check if it's a double quote
	quoted_buf = malloc(state->len + 1);
	qindex = 0;
	if (!quoted_buf)
		return (malloc_error1());
	if (state->token_index > 0)
	{
		fush_token_buffer(state);
	}
	state->i++; // Skip the opening quote
	while (state->i < state->len && state->input[state->i] != quote)
		quoted_buf[qindex++] = state->input[state->i++];
	if (state->i < state->len && state->input[state->i] == quote)
		state->i++; // Skip the closing quote
	else
		return (unclosed_norm(state, quoted_buf));
	quoted_buf[qindex] = '\0';
	append_node(state->head, quoted_buf, TYPE_WORD);
	set_node_quoted(state->head, is_double_quote);  // Set the quote flag
	free(quoted_buf);
	return (1);
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
		if (handle_metacharacters(state))
			return (1);
	}
	state->token_buf[state->token_index++] = state->input[state->i++];
	return (1);
}

int	initialize_tokenizer_state(t_tokenizer_state *state, char *input, int len)
{
	state->input = input;
	state->len = len;
	state->i = 0;
	state->token_buf = malloc(len + 1);
	state->token_index = 0;
	state->head = malloc(sizeof(t_input *));
	state->in_quotes = 0;
	state->quote_char = 0;
	state->shell = NULL;  // Initialize shell pointer to NULL
	if (!state->token_buf || !state->head)
	{
		free(state->token_buf);
		free(state->head);
		return (0);
	}
	*state->head = NULL;
	return (1);
}

t_input	*tokenizer(t_shell *shell, char *input, int len)
{
	t_tokenizer_state	state;
	t_input				*result;

	if (!initialize_tokenizer_state(&state, input, len))
		return (NULL);
	state.shell = shell;  // Store reference to shell in tokenizer state
	while (state.i < state.len)
	{
		if (input[state.i] == '\'' || input[state.i] == '\"')
		{
			if (!handle_quotes(&state))
				return (cleanup_tokenizer(&state));
		}
		else if (!process_token(&state))
		{
			return (cleanup_tokenizer(&state));
		}
	}
	if (state.in_quotes)
	{
		write(2, "Error: Unclosed quote\n", 22);
		return (cleanup_tokenizer(&state));
	}
	if (state.token_index > 0)
	{
		state.token_buf[state.token_index] = '\0';
		append_node(state.head, state.token_buf, TYPE_WORD);
	}
	result = *state.head;
	cleanup_tokenizer_state(&state);
	return (result);
}
