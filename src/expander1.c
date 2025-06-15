/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:35:14 by aeleimat          #+#    #+#             */
/*   Updated: 2025/06/15 20:07:35 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

/* ---------- Expander Implementation ---------- */

/*
 * Determines the type of variable reference and processes it accordingly
 * Checks if the character after $ is a letter/underscore or digit
 * Calls the appropriate processing function based on the type
 * Returns 1 on successful processing, 0 on error
 */
int	process_variable_by_type(t_expander_context *ctx)
{
	if (ft_isalpha(ctx->source[ctx->i + 1])
		|| ctx->source[ctx->i + 1] == '_')
	{
		if (!process_env_variable(ctx))
			return (0);
		return (1);
	}
	if (ft_isdigit(ctx->source[ctx->i + 1]))
	{
		if (!process_digit_parameter(ctx))
			return (0);
		return (1);
	}
	return (0);
}
/*
 * Processes variable expansion for $?, $NAME, $0, etc.
 * Handles all variable types and updates buffer appropriately
 * Returns 1 on success, 0 on memory allocation failure
 */

int	process_variable(t_expander_context *ctx)
{
	if (ctx->source[ctx->i] == '$'
		&& !ctx->in_single && ctx->i + 1 < ctx->src_len)
	{
		if (ctx->source[ctx->i + 1] == '?')
		{
			if (!process_exit_status(ctx))
				return (0);
			return (1);
		}
		if (process_variable_by_type(ctx))
			return (1);
		ctx->expanded[ctx->j++] = ctx->source[ctx->i++];
		return (1);
	}
	return (0);
}

/*
 * Copies a regular character from source to expanded buffer
 * Ensures there's enough capacity in the buffer before copying
 * Updates both source and destination indices
 * Returns 1 on success, 0 on memory allocation failure
 */
int	copy_regular_char(t_expander_context *ctx)
{
	if (ctx->j + 1 >= ctx->buf_size)
	{
		ctx->buf_size *= 2;
		ctx->expanded = ft_realloc(ctx->expanded, ctx->buf_size);
		if (!ctx->expanded)
		{
			ft_putstr_fd("Memory reallocation error during expansion.\n", 2);
			return (0);
		}
	}
	ctx->expanded[ctx->j++] = ctx->source[ctx->i++];
	return (1);
}
/*
 * Prepares a token for expansion by:
 * 1. Checking if the token should be skipped
 * 2. Initializing the expansion buffer if needed
 * 
 * Returns:
 * - 1 if the token is ready for expansion
 * - 0 if we should skip to the next token
 * Exits on memory allocation failure
 */

int	prepare_token_for_expansion(t_expander_context *ctx)
{
	if (should_skip_expansion(ctx))
	{
		ctx->node = ctx->node->next;
		return (0);
	}
	if (!initialize_expansion_buffer(ctx))
		exit(EXIT_FAILURE);
	return (1);
}
/*
 * Expander:
 * Iterates over all tokens in the shell's token list.
 * First, process parameter expansion for tokens that are not single-quoted.
 * Then, perform quote removal on tokens that start and end with a quote.
 */

void	expand_tokens(t_shell *shell)
{
	t_expander_context	ctx;

	ft_memset(&ctx, 0, sizeof(ctx));
	ctx.exit_status = shell->exit_status;
	ctx.is_heredoc_delimiter = 0;
	ctx.envp = shell->analyzing_data.envp;
	ctx.node = shell->tokens;
	while (ctx.node != NULL)
	{
		if (!prepare_token_for_expansion(&ctx))
			continue ;
		while (ctx.i < ctx.src_len)
		{
			if (handle_quotes_expander(&ctx))
				continue ;
			if (process_variable(&ctx))
				continue ;
			if (!copy_regular_char(&ctx))
				exit(EXIT_FAILURE);
		}
		ctx.expanded[ctx.j] = '\0';
		free(ctx.node->string);
		ctx.node->string = ctx.expanded;
		ctx.node = ctx.node->next;
	}
	
}
