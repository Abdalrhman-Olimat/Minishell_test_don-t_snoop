/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:35:14 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/22 01:26:05 by aeleimat         ###   ########.fr       */
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

/*
//  Helper: Returns 1 if the token string is enclosed in single quotes.
//  In that case, we skip parameter expansion.

int is_single_quoted(const char *str)
{
	int len = ft_strlen(str);
	return (len >= 2 && str[0] == '\'' && str[len - 1] == '\'');
}

//   Helper: Returns 1 if the token string is enclosed in matching quotes
//(either single or double).
//   Such tokens will have only their first and last characters removed
//during quote removal.
 
int is_quoted(const char *str)
{
	int len = ft_strlen(str);
	if (len < 2)
		return (0);
	if ((str[0] == '\'' && str[len - 1] == '\'') ||
		(str[0] == '\"' && str[len - 1] == '\"'))
		return (1);
	return (0);
}
char *expand_exit_status(const char *str, size_t *i, size_t *j,
size_t *cap, char *result, int exit_status)

 // Expands the $? special parameter to the current exit status
 // Updates position indices and reallocates buffer if needed
 // Returns updated result buffer or NULL on failure
 //
{
	*i += 2; // Skip "$?"
	char status_str[16];
	sprintf(status_str, "%d", exit_status);////////////////////
	size_t status_len = ft_strlen(status_str);
	// Ensure buffer is large enough
	while (*j + status_len + 1 >= *cap)
	{
		*cap *= 2;
		result = ft_realloc(result, *cap);
		if (!result)
			return NULL;
	}
	ft_strcpy(&result[*j], status_str);
	*j += status_len;
	return result;
}
char *expand_digit_parameter(const char *str, size_t *i, size_t *j,
size_t *cap, char *result)
//  Expands digit-based parameters like $0, $1, etc.
//  $0 is replaced with "minishell", while other digits are preserved
//  Updates position indices and reallocates buffer if needed
//  Returns updated result buffer or NULL on failure
{
	(*i)++; // skip '$'
	size_t digit_start = *i;
	// Collect all consecutive digits
	while (str[*i] && isdigit(str[*i]))
		(*i)++;
	size_t digit_count = *i - digit_start;
	// If the first digit is '0', replace it with "minishell"
	if (str[digit_start] == '0')
	{
		char *shellname = "minishell";
		size_t shell_len = strlen(shellname);
		while (*j + shell_len + 1 >= *cap)
		{
			*cap *= 2;
			result = ft_realloc(result, *cap);
			if (!result)
				return NULL;
		}
		ft_strcpy(&result[*j], shellname);
		*j += shell_len;
	}
	// Append any remaining digits after the first one
	if (digit_count > 1)
	{
		size_t rest_len = digit_count - 1;
		while (*j + rest_len + 1 >= *cap)
		{
			*cap *= 2;
			result = ft_realloc(result, *cap);
			if (!result)
				return NULL;
		}
		strncpy(&result[*j], str + digit_start + 1, rest_len);
		*j += rest_len;
	}
	return result;
}
char *expand_environment_variable(const char *str, size_t *i, size_t
*j, size_t *cap, char *result)
// Expands standard environment variables like $HOME, $PATH, etc.
// Looks up the variable value using getenv()
// Updates position indices and reallocates buffer if needed
// Returns updated result buffer or NULL on failure
{
	(*i)++; // Skip the '$'
	size_t var_start = *i;
	while (str[*i] && (isalnum(str[*i]) || str[*i] == '_'))
		(*i)++;
	size_t var_len = *i - var_start;
	char var_name[var_len + 1];
	strncpy(var_name, str + var_start, var_len);
	var_name[var_len] = '\0';
	char *env_value = getenv(var_name);
	if (!env_value)
		env_value = ""; // Substitute empty string if not found
	size_t env_len = strlen(env_value);
	while (*j + env_len + 1 >= *cap)
	{
		*cap *= 2;
		result = ft_realloc(result, *cap);
		if (!result)
			return NULL;
	}
	ft_strcpy(&result[*j], env_value);
	*j += env_len;
	return result;
}//27
//  earlier versions of expand_tokens
//  Parameter Expansion:
//  Scans the string for occurrences of a '$'. The special case of "$?" is
//replaced
//  with the shell's exit status from t_shell->exit_status.
//  Regular variables (starting with a letter or '_') are looked up via getenv(
//  Additionally, if '$' is followed by a digit, we handle it specially:
//    - If the first digit is '0', replace it with "minishell" and append any
//	remaining digits.
//    - Otherwise, skip the first digit and append any remaining digits.
// 
char *parameter_expansion(const char *str, int exit_status)
{
	size_t len;
	size_t cap;
	char *result;
	size_t i;
	size_t j;
	len = ft_strlen(str);
	cap = len * 2 + 1;
	result = malloc(cap);
	i = 0;
	j = 0;
	if (!result)
		return NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			// Handle "$?" expansion.
			if (str[i + 1] == '?')
			{
				result = expand_exit_status(str, &i, &j, &cap, result,
				exit_status);
				if (!result)
					return NULL;
				continue;
			}
			// Handle digit-based parameters, e.g. "$1", "$023", etc.
			if (str[i + 1] && isdigit(str[i + 1]))
			{
				result = expand_digit_parameter(str, &i, &j, &cap, result);
				if (!result)
					return NULL;
				continue;
			}
			// Handle standard variable names: $VAR
			(must start with a letter or '_')
			if (str[i + 1] && (isalpha(str[i + 1]) || str[i + 1] == '_'))
			{
				result = expand_environment_variable(str, &i, &j, &cap, result)
				if (!result)
					return NULL;
				continue;
			}
			else
			{
				// If '$' is not followed by a valid identifier or digit,
				copy it literally.
				result[j++] = str[i++];
			}
		}
		else
		{
			result[j++] = str[i++];
		}
		if (j + 1 >= cap)
		{
			cap *= 2;
			result = ft_realloc(result, cap);
			if (!result)
				return NULL;
		}
	}
	result[j] = '\0';
	return result;
}
*/