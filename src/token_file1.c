/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_file1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:37:31 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/12 06:42:22 by aeleimat         ###   ########.fr       */
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
	state->shell = NULL;
	if (!state->token_buf || !state->head)
	{
		free(state->token_buf);
		free(state->head);
		return (0);
	}
	*state->head = NULL;
	return (1);
}

static t_input	*finalize_tokenization(t_tokenizer_state *state)
{
	t_input	*result;

	if (state->in_quotes)
	{
		write(2, "Error: Unclosed quote\n", 22);
		return (cleanup_tokenizer(state));
	}
	if (state->token_index > 0)
	{
		state->token_buf[state->token_index] = '\0';
		append_node(state->head, state->token_buf, TYPE_WORD);
	}
	result = *(state->head);
	cleanup_tokenizer_state(state);
	return (result);
}

t_input	*tokenizer(t_shell *shell, char *input, int len)
{
	t_tokenizer_state	state;

	if (!initialize_tokenizer_state(&state, input, len))
		return (NULL);
	state.shell = shell;
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
	return (finalize_tokenization(&state));
}
