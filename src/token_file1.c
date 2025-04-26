/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_file1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/15 07:37:31 by aeleimat          #+#    #+#             */
/*   Updated: 2025/04/26 12:07:42 by aeleimat         ###   ########.fr       */
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
	if (state->token_index > 0)
	{
		fush_token_buffer(state);
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

int process_token(t_tokenizer_state *state)
{
    // Handle whitespace - always a token delimiter when not in quotes
    if ((state->input[state->i] == ' ' || state->input[state->i] == '\t') && 
        !state->in_quotes)
    {
        handle_whitespace(state);
        return (1);
    }
    
    // Handle quotes - toggle quote state
    if (state->input[state->i] == '\'' || state->input[state->i] == '\"')
    {
        char quote = state->input[state->i];
        
        // Add the quote character to the current token
        state->token_buf[state->token_index++] = state->input[state->i++];
        
        // If we're not already in quotes, start quote state with this quote type
        if (!state->in_quotes)
        {
            state->in_quotes = 1;
            state->quote_char = quote;
        }
        // If we're in quotes and this is the closing quote, end quote state
        else if (state->quote_char == quote)
        {
            state->in_quotes = 0;
        }
        
        return (1);
    }
    
    // Handle metacharacters only when not in quotes
    if (!state->in_quotes && (state->input[state->i] == '|' || 
        state->input[state->i] == '<' || state->input[state->i] == '>'))
    {
        // If we have content in the buffer, flush it first
        if (state->token_index > 0)
        {
            state->token_buf[state->token_index] = '\0';
            append_node(state->head, state->token_buf, TYPE_WORD);
            state->token_index = 0;
        }
        
        // Then handle the metacharacter
        if (handle_metacharacters(state))
            return (1);
    }
    
    // For all other characters, just add to current token
    state->token_buf[state->token_index++] = state->input[state->i++];
    return (1);
}

int	initialize_tokenizer_state(t_tokenizer_state *state, char *input, int len)
{
    // Existing initialization
    state->input = input;
    state->len = len;
    state->i = 0;
    state->token_buf = malloc(len + 1);
    state->token_index = 0;
    state->head = malloc(sizeof(t_input *));
    
    // Add these initializations
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

t_input	*tokenizer(char *input, int len)
{
    t_tokenizer_state	state;
    t_input				*result;

    if (!initialize_tokenizer_state(&state, input, len))
        return (NULL);
    while (state.i < state.len)
    {
        if (!process_token(&state))
        {
            free_list(*state.head);
            free(state.token_buf);
            free(state.head);
            return (NULL);
        }
    }
    
    // Check for unclosed quotes at the end of input
    if (state.in_quotes)
    {
        write(2, "Error: Unclosed quote\n", 22);
        free_list(*state.head);
        free(state.token_buf);
        free(state.head);
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
