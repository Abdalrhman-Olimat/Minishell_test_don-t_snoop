/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_file1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:37:31 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/16 21:44:30 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	malloc_error1(void)
{
	write(2, "Error: Memory allocation failed\n", 32);
	return (0);
}

int	create_quoted_node(t_tokenizer_state *state, char *quoted_buf,
		bool is_double_quote)
{
	append_node(state->head, quoted_buf, TYPE_WORD);
	set_node_quoted(state->head, is_double_quote);
	free(quoted_buf);
	return (1);
}

int	handle_quotes(t_tokenizer_state *state)
{
	int		qindex;
	char	quote;
	char	*quoted_buf;
	bool	is_double_quote;

	quote = state->input[state->i];
	quoted_buf = malloc(state->len + 1);
	qindex = 0;
	is_double_quote = (quote == '\"');
	if (!quoted_buf)
		return (malloc_error1());
	if (state->token_index > 0)
	{
		fush_token_buffer(state);
	}
	state->i++; /* Skip the opening quote */
	while (state->i < state->len && state->input[state->i] != quote)
		quoted_buf[qindex++] = state->input[state->i++];
	if (state->i < state->len && state->input[state->i] == quote)
		state->i++; /* Skip the closing quote */
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
	state.shell = shell;
	while (state.i < state.len)
	{
		if (!process_token(&state))
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
