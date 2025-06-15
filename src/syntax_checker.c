/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 00:10:30 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:35:48 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

static int	handle_word(int *has_word)
/*
 * Processes a word token
 * Sets has_word flag to indicate a command is present
 */
{
	*has_word = 1;
	return (1);
}

static int	handle_redirection(t_input **current)
/*
 * Processes a redirection token
 * Checks if there is a word following the redirection
 */
{
	if ((*current)->next == NULL || (*current)->next->type != TYPE_WORD)
		return (print_syntax_error_token(*current));
	*current = (*current)->next;
	return (1);
}

static int	handle_pipe(t_input *current, int *has_word)
/*
 * Processes a pipe token
 * Ensures a command exists before the pipe
 */
{
	if (*has_word == 0)
		return (print_pipe_error());
	*has_word = 0;
	return (1);
}

static int	handle_token(t_input **current, int *has_word)
/*
 * Determines token type and calls appropriate handler function
 * Returns status code from the handler
 */
{
	if ((*current)->type == TYPE_WORD)
		return (handle_word(has_word));
	else if (is_redirection((*current)->type))
		return (handle_redirection(current));
	else if ((*current)->type == TYPE_PIPE)
		return (handle_pipe(*current, has_word));
	else
		return (print_unexpected_token_error());
}

int	syntax_checker(t_input *tokens)
/*
 * Main syntax checking function
 * Processes all tokens in sequence, validating command structure
 * Returns 1 for valid syntax, 0 for errors
 */
{
	t_input		*current;
	t_input		*last_token;
	int			has_word;
	int			status;

	if (!tokens)
		return (1);
	current = tokens;
	last_token = NULL;
	has_word = 0;
	while (current != NULL)
	{
		status = handle_token(&current, &has_word);
		if (status != 1)
			return (status);
		last_token = current;
		current = current->next;
	}
	if (has_word)
		return (1);
	else
		return (print_incomplete_command_error(last_token));
}
