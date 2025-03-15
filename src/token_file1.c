/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_file1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:37:31 by aeleimat          #+#    #+#             */
/*   Updated: 2025/03/15 08:54:19 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	handle_whitespace(t_tokenizer_state *state)
{
	if (state->token_index > 0)
	{
		state->token_buf[state->token_index] = '\0';
		append_node(state->head, state->token_buf, TYPE_WORD);
		state->token_index = 0;
	}
	state->i++;
}

int	handle_metacharacters2(t_tokenizer_state *state)
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

int	handle_metacharacters(t_tokenizer_state *state)
{
	if (state->input[state->i] == '<'
		&& (state->i + 1 < state->len && state->input[state->i + 1] == '<'))
	{
		append_node(state->head, "<<", TYPE_HEREDOC);
		state->i += 2;
		return (1);
	}
	if (state->input[state->i] == '>'
		&& (state->i + 1 < state->len && state->input[state->i + 1] == '>'))
	{
		append_node(state->head, ">>", TYPE_APPEND);
		state->i += 2;
		return (1);
	}
	return (handle_metacharacters2(state));
}

int	unclosed_norm(t_tokenizer_state *state, char *quoted_buf)
{
	write(2, "Error: Unclosed quote\n", 23);
	free_list(*state->head);
	free(quoted_buf);
	return (0);
}

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

	quote = state->input[state->i];
	quoted_buf = malloc(state->len + 1);
	qindex = 0;
	if (!quoted_buf)
		return (malloc_error1());
	if (state->token_index > 0)
	{
		state->token_buf[state->token_index] = '\0';
		append_node(state->head, state->token_buf, TYPE_WORD);
		state->token_index = 0;
	}
	quoted_buf[qindex++] = state->input[state->i++];
	while (state->i < state->len && state->input[state->i] != quote)
		quoted_buf[qindex++] = state->input[state->i++];
	if (state->i < state->len && state->input[state->i] == quote)
		quoted_buf[qindex++] = state->input[state->i++];
	else
		return (unclosed_norm(state, quoted_buf));
	quoted_buf[qindex] = '\0';
	append_node(state->head, quoted_buf, TYPE_WORD);
	free(quoted_buf);
	return (1);
}

t_input	*tokenizer(char *input, int len)
{
	t_tokenizer_state	state;
	t_input				*result;

	result = *state.head;
	state.input = input;
	state.len = len;
	state.i = 0;
	state.token_buf = malloc(len + 1);
	state.token_index = 0;
	state.head = malloc(sizeof(t_input *));
	*state.head = NULL;
	if (!state.token_buf || !state.head)
	{
		free(state.token_buf);
		free(state.head);
		return (NULL);
	}
	while (state.i < state.len)
	{
		if (state.input[state.i] == ' ' || state.input[state.i] == '\t')
		{
			handle_whitespace(&state);
			continue ;
		}
		if ((state.input[state.i] == '|' || state.input[state.i] == '<'
				|| state.input[state.i] == '>') && state.token_index == 0)
		{
			if (handle_metacharacters(&state))
			{
				continue ;
			}
		}
		if (state.input[state.i] == '\'' || state.input[state.i] == '\"')
		{
			if (!handle_quotes(&state))
			{
				free(state.token_buf);
				free(state.head);
				return (NULL);
			}
			continue ;
		}
		state.token_buf[state.token_index++] = state.input[state.i++];
	}
	if (state.token_index > 0)
	{
		state.token_buf[state.token_index] = '\0';
		append_node(state.head, state.token_buf, TYPE_WORD);
	}
	result = *state.head;
	free(state.token_buf);
	free(state.head);
	return (result);
}
