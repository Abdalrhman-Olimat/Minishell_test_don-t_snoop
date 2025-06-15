/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:04:49 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/22 01:06:57 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

/*
 * Determines if a token should be expanded based on:
 * 1. If it's a heredoc marker (<<)
 * 2. If it's a heredoc delimiter token
 * 3. If it's not a WORD token
 * 
 * Returns:
 * - 1 if token should be skipped (don't expand)
 * - 0 if token should be expanded
 */
int	should_skip_expansion(t_expander_context *ctx)
{
	if (ctx->node->type == TYPE_HEREDOC && ctx->node->string
		&& ft_strcmp(ctx->node->string, "<<") == 0)
	{
		ctx->is_heredoc_delimiter = 1;
		return (1);
	}
	if (ctx->is_heredoc_delimiter)
	{
		ctx->is_heredoc_delimiter = 0;
		return (1);
	}
	if (ctx->node->type != TYPE_WORD)
		return (1);
	return (0);
}

int	initialize_expansion_buffer(t_expander_context *ctx)
{
	ctx->source = ctx->node->string;
	ctx->src_len = ft_strlen(ctx->source);
	ctx->buf_size = ctx->src_len * 8 + 1;
	ctx->expanded = malloc(ctx->buf_size);
	if (!ctx->expanded)
	{
		ft_putstr_fd("Memory allocation error during expansion.\n", 2);
		return (0);
	}
	ctx->i = 0;
	ctx->j = 0;
	ctx->in_single = 0;
	ctx->in_double = 0;
	return (1);
}
/*
 * Processes quotes during token expansion
 * Updates quote state flags and advances position past the quote character
 * Returns 1 if a quote was processed, 0 otherwise
 */

int	handle_quotes_expander(t_expander_context *ctx)
{
	if (ctx->source[ctx->i] == '\'' && !ctx->in_double)
	{
		ctx->in_single = !ctx->in_single;
		ctx->i++;
		return (1);
	}
	if (ctx->source[ctx->i] == '\"' && !ctx->in_single)
	{
		ctx->in_double = !ctx->in_double;
		ctx->i++;
		return (1);
	}
	return (0);
}

/*
 * Extracts digits from a number into a buffer and reverses them
 * Handles the negative sign placement and digit reversal
 * Updates the output buffer with the final string
 * Returns the number of characters written
 */
int	convert_digits_to_string(int tmp, int is_neg, char *buffer, int i)
{
	int		len;
	char	buf[16];

	len = 0;
	while (tmp > 0 && len < 15)
	{
		buf[len++] = (tmp % 10) + '0';
		tmp /= 10;
	}
	if (is_neg && len < 15)
		buf[len++] = '-';
	while (len > 0)
		buffer[i++] = buf[--len];
	return (i);
}

/*
 * Converts an integer to a string representation
 * Handles zero and negative numbers correctly
 * Returns the length of the resulting string
 */
int	int_to_string(int value, char *buffer)
{
	int	i;
	int	tmp;
	int	is_neg;

	i = 0;
	tmp = value;
	is_neg = 0;
	if (value == 0)
	{
		buffer[i++] = '0';
		buffer[i] = '\0';
		return (i);
	}
	if (value < 0)
	{
		is_neg = 1;
		tmp = -tmp;
	}
	i = convert_digits_to_string(tmp, is_neg, buffer, i);
	buffer[i] = '\0';
	return (i);
}
