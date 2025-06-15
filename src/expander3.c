/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 01:06:05 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/22 01:28:35 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

/*
 * Processes the $? special parameter, expanding it to the current exit status
 * Updates buffer position indices and ensures sufficient buffer capacity
 * Returns 1 if expansion was successful, 0 on memory allocation failure
 */
int	process_exit_status(t_expander_context *ctx)
{
	ctx->status_len = int_to_string(ctx->exit_status, ctx->status_str);
	if (!ensure_capacity(ctx, ctx->status_len))
		return (0);
	ft_strncpy(ctx->expanded + ctx->j, ctx->status_str, ctx->status_len);
	ctx->j += ctx->status_len;
	ctx->i += 2;
	return (1);
}

/*
 * Ensures the expansion buffer has enough capacity for additional characters
 * Reallocates the buffer if needed, doubling its size or making it big enough
 * Returns 1 on success, 0 on memory allocation failure
 */
int	ensure_capacity(t_expander_context *ctx, size_t additional)
{
	if (ctx->j + additional >= ctx->buf_size)
	{
		ctx->buf_size = (ctx->j + additional) * 2;
		ctx->expanded = ft_realloc(ctx->expanded, ctx->buf_size);
		if (!ctx->expanded)
		{
			ft_putstr_fd("Memory reallocation error during expansion.\n", 2);
			return (0);
		}
	}
	return (1);
}

/*
 * Processes environment variables like $HOME, $USER, etc.
 * Extracts the variable name, looks up its value, and adds to buffer
 * Updates buffer position indices and ensures sufficient capacity
 * Returns 1 if expansion was successful, 0 on memory allocation failure
 */
int	process_env_variable(t_expander_context *ctx)
{
	ctx->var_start = ctx->i + 1;
	ctx->i++;
	while (ctx->i < ctx->src_len && (ft_isalnum(ctx->source[ctx->i])
			|| ctx->source[ctx->i] == '_'))
		ctx->i++;
	ctx->var_len = ctx->i - ctx->var_start;
	ft_strncpy(ctx->var_name, ctx->source + ctx->var_start, ctx->var_len);
	ctx->var_name[ctx->var_len] = '\0';
	ctx->env_value = get_env_value(ctx->var_name, ctx->envp);
	if (ctx->env_value)
	{
		ctx->env_len = ft_strlen(ctx->env_value);
		if (!ensure_capacity(ctx, ctx->env_len))
			return (0);
		ft_strncpy(ctx->expanded + ctx->j, ctx->env_value, ctx->env_len);
		ctx->j += ctx->env_len;
	}
	return (1);
}

/*
 * Processes positional parameters like $0, $1, etc.
 * $0 expands to "minishell", $1-$9 expand to empty strings
 * Updates buffer position indices and ensures sufficient capacity
 * Returns 1 if expansion was successful, 0 on memory allocation failure
 */
int	process_digit_parameter(t_expander_context *ctx)
{
	char	digit;

	ctx->i++;
	digit = ctx->source[ctx->i];
	ctx->i++;
	if (digit == '0')
	{
		ctx->shell_name = "minishell";
		ctx->name_len = ft_strlen(ctx->shell_name);
		if (!ensure_capacity(ctx, ctx->name_len))
			return (0);
		ft_strncpy(ctx->expanded + ctx->j, ctx->shell_name, ctx->name_len);
		ctx->j += ctx->name_len;
	}
	return (1);
}
