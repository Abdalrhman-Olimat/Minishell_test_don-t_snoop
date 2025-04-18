/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_file1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:37:31 by aeleimat          #+#    #+#             */
/*   Updated: 2025/04/16 16:26:14 by aeleimat         ###   ########.fr       */
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

    quote = state->input[state->i];
    quoted_buf = malloc(state->len + 1);
    qindex = 0;
    if (!quoted_buf)
        return (malloc_error1());
    
    // Include the opening quote in the buffer
    quoted_buf[qindex++] = state->input[state->i++];
    
    // Collect characters inside quotes
    while (state->i < state->len && state->input[state->i] != quote)
        quoted_buf[qindex++] = state->input[state->i++];
    
    if (state->i < state->len && state->input[state->i] == quote)
        quoted_buf[qindex++] = state->input[state->i++]; // Include closing quote
    else
        return (unclosed_norm(state, quoted_buf));
    
    quoted_buf[qindex] = '\0';
    
    // Add quoted content to current token buffer
    int i = 0;
    while (quoted_buf[i] != '\0')
        state->token_buf[state->token_index++] = quoted_buf[i++];
    
    free(quoted_buf);
    return (1);
}

int	process_token(t_tokenizer_state *state)
{
    if (state->input[state->i] == ' ' || state->input[state->i] == '\t')
    {
        handle_whitespace(state);
        return (1);
    }
    
    // Check for metacharacters anywhere, not just at the beginning
    if (state->input[state->i] == '|' || state->input[state->i] == '<'
            || state->input[state->i] == '>')
    {
        // If we have content in the buffer, flush it first
        if (state->token_index > 0)
            fush_token_buffer(state);
            
        // Then handle the metacharacter
        if (handle_metacharacters(state))
            return (1);
    }
    
    if (state->input[state->i] == '\'' || state->input[state->i] == '\"')
    {
        if (!handle_quotes(state))
        {
            free(state->token_buf);
            free(state->head);
            return (0);
        }
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
	if (!state->token_buf || !state->head)
	{
		free(state->token_buf);
		free(state->head);
		return (0);
	}
	*state->head = NULL;
	return (1);
}

t_input	*tokenizer(char *input, int len)
{
	t_tokenizer_state	state;
	t_input				*result;

	if (!initialize_tokenizer_state(&state, input, len))
		return (NULL);
	while (state.i < state.len)
	{
		if (!process_token(&state))
			return (NULL);
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
