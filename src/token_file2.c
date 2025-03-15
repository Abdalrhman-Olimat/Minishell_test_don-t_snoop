/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_file2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 09:34:44 by aeleimat          #+#    #+#             */
/*   Updated: 2025/03/15 09:35:45 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	fush_token_buffer(t_tokenizer_state *state)
{
	state->token_buf[state->token_index] = '\0';
	append_node(state->head, state->token_buf, TYPE_WORD);
	state->token_index = 0;
}

void	handle_whitespace(t_tokenizer_state *state)
{
	if (state->token_index > 0)
		fush_token_buffer(state);
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
