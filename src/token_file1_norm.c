/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_file1_norm.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 21:39:14 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/16 21:47:02 by aeleimat         ###   ########.fr       */
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
	free_list(*state->head);
	free(state->token_buf);
	free(state->head);
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
	}
	return (1);
}
