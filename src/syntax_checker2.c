/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 00:45:52 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/15 00:47:57 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	print_syntax_error_token(t_input *current)
/*
 * Prints a syntax error message for unexpected tokens with specific formatting
 * Returns 0 to indicate an error condition
 */
{
	ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
	if (current->next == NULL)
		ft_putstr_fd("`newline'\n", 2);
	else
	{
		ft_putstr_fd("`", 2);
		ft_putstr_fd(current->next->string, 2);
		ft_putstr_fd("'\n", 2);
	}
	return (0);
}

int	is_redirection(int type)
/*
 * Checks if the token type is any kind of redirection operator
 * Returns 1 for redirections, 0 otherwise
 */
{
	return (type == TYPE_REDIR_IN || type == TYPE_REDIR_OUT
		|| type == TYPE_HEREDOC || type == TYPE_APPEND);
}

int	print_incomplete_command_error(t_input *last_token)
/*
 * Prints an error message for incomplete commands
 * Special handling for pipe as the last token
 */
{
	if (last_token != NULL && last_token->type == TYPE_PIPE)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else
		ft_putstr_fd("minishell: syntax error: incomplete command\n", 2);
	return (0);
}

int	print_pipe_error(void)
/*
 * Prints an error message for pipe syntax errors
 * (typically pipe at start or two pipes with no command between them)
 */
{
	ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	return (0);
}

int	print_unexpected_token_error(void)
/*
 * Prints a generic error message for unexpected tokens
 */
{
	ft_putstr_fd("minishell: syntax error: unexpected token\n", 2);
	return (0);
}
