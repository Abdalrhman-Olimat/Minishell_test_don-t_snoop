/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/18 15:35:14 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/18 15:53:17 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

/* ---------- Expander Implementation ---------- */

/*
 * Structure to hold all state information for token expansion
 * Keeps related variables grouped together for better code organization
 */

typedef struct s_expander_context
{
	t_input		*node;
	size_t		src_len;
	size_t		i;
	size_t		status_len;
	size_t		var_len;
	size_t		buf_size;
	size_t		j;
	size_t		name_len;
	size_t		var_start;
	size_t		env_len;
	int			is_heredoc_delimiter;
	int			in_double;
	int			in_single;
	int			exit_status;
	char		*source;
	char		*expanded;
	char		status_str[16];
	char		var_name[4096];
	char		*env_value;
	const char	*shell_name;
}	t_expander_context;

void	*ft_realloc(void *ptr, size_t newsize)
{
	size_t	cursize;
	char	*newptr;

	if (ptr == 0)
		return (malloc(newsize));
	cursize = sizeof(ptr);
	if (newsize <= cursize)
		return (ptr);
	newptr = malloc(newsize);
	ft_memcpy(ptr, newptr, cursize);
	free(ptr);
	return (newptr);
}

char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	i = 0;
	while (src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
		dst[i] = '\0';
	}
	return (dst);
}

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	while (src[i] && i < n)
	{
		dst[i] = src[i];
		i++;
	}
	while (i < n)
	{
		dst[i] = '\0';
		i++;
	}
	return (dst);
}

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
	if (ctx->node->type == TYPE_HEREDOC
		&& ctx->node->string && ft_strcmp(ctx->node->string, "<<") == 0)
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
 * Converts an integer to a string representation
 * Handles zero and negative numbers correctly
 * Returns the length of the resulting string
 */
int	int_to_string(int value, char *buffer)
{
	int		i;
	int		tmp;
	int		len;
	int		is_neg;
	char	buf[16];

	i = 0;
	tmp = value;
	len = 0;
	is_neg = 0;
	if (value == 0)
	{
		buffer[i++] = '0';
		buffer[i] = '\0';
		return i;
	}
	if (value < 0)
	{
		is_neg = 1;
		tmp = -tmp;
	}
	while (tmp > 0 && len < 15)
	{
		buf[len++] = (tmp % 10) + '0';
		tmp /= 10;
	}
	if (is_neg && len < 15)
		buf[len++] = '-';
	while (len > 0)
		buffer[i++] = buf[--len];
	buffer[i] = '\0';
	return (i);
}
/*
 * Processes the $? special parameter, expanding it to the current exit status
 * Updates buffer position indices and ensures sufficient buffer capacity
 * Returns 1 if expansion was successful, 0 on memory allocation failure
 */

 int	process_exit_status(t_expander_context *ctx)
{
	ctx->status_len = int_to_string(ctx->exit_status, ctx->status_str);
	if (ctx->j + ctx->status_len >= ctx->buf_size)
	{
		ctx->buf_size = (ctx->j + ctx->status_len) * 2;
		ctx->expanded = ft_realloc(ctx->expanded, ctx->buf_size);
		if (!ctx->expanded)
		{
			ft_putstr_fd("Memory reallocation error during expansion.\n", 2);
			return (0);
		}
	}
	ft_strncpy(ctx->expanded + ctx->j, ctx->status_str, ctx->status_len);
	ctx->j += ctx->status_len;
	ctx->i += 2;
	
	return (1);
}
/*
 * Processes environment variables like $HOME, $USER, etc.
 * Extracts the variable name, looks up its value, and adds to buffer
 * Updates buffer position indices and ensures sufficient capacity
 * Returns 1 if expansion was successful, 0 on memory allocation failure
 */
int process_env_variable(t_expander_context *ctx)
{
	ctx->var_start = ctx->i + 1;
	ctx->i++;
	while (ctx->i < ctx->src_len && 
		  (ft_isalnum(ctx->source[ctx->i]) || ctx->source[ctx->i] == '_'))
		ctx->i++;
	ctx->var_len = ctx->i - ctx->var_start;
	ft_strncpy(ctx->var_name, ctx->source + ctx->var_start, ctx->var_len);
	ctx->var_name[ctx->var_len] = '\0';
	ctx->env_value = getenv(ctx->var_name);
	if (ctx->env_value)
	{
		ctx->env_len = ft_strlen(ctx->env_value);
		if (ctx->j + ctx->env_len >= ctx->buf_size)
		{
			ctx->buf_size = (ctx->j + ctx->env_len) * 2;
			ctx->expanded = ft_realloc(ctx->expanded, ctx->buf_size);
			if (!ctx->expanded)
			{
				ft_putstr_fd("Memory reallocation error during expansion.\n", 2);
				return 0;
			}
		}
		ft_strncpy(ctx->expanded + ctx->j, ctx->env_value, ctx->env_len);
		ctx->j += ctx->env_len;
	}
	return 1;
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
		if (ctx->j + ctx->name_len >= ctx->buf_size)
		{
			ctx->buf_size = (ctx->j + ctx->name_len) * 2;
			ctx->expanded = ft_realloc(ctx->expanded, ctx->buf_size);
			if (!ctx->expanded)
			{
				ft_putstr_fd("Memory reallocation error during expansion.\n", 2);
				return (0);
			}
		}
		ft_strncpy(ctx->expanded + ctx->j, ctx->shell_name, ctx->name_len);
		ctx->j += ctx->name_len;
	}
	return (1);
}
/*
 * Processes variable expansion for $?, $NAME, $0, etc.
 * Handles all variable types and updates buffer appropriately
 * Returns 1 on success, 0 on memory allocation failure
 */
int process_variable(t_expander_context *ctx)
{
	if (ctx->source[ctx->i] == '$' && !ctx->in_single && ctx->i + 1 < ctx->src_len)
	{
		if (ctx->source[ctx->i + 1] == '?')
		{
			if (!process_exit_status(ctx))
				return (0);
			return (1);
		}
		if (ft_isalpha(ctx->source[ctx->i + 1]) || ctx->source[ctx->i + 1] == '_')
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
		ctx->expanded[ctx->j++] = ctx->source[ctx->i++];
		return 1;
	}
	return (0);
}
/*
 * Expander:
 * Iterates over all tokens in the shell's token list.
 * First, process parameter expansion for tokens that are not single-quoted.
 * Then, perform quote removal on tokens that start and end with a quote.
 */
void expand_tokens(t_shell *shell)
{
	t_expander_context ctx;
	
	ft_memset(&ctx, 0, sizeof(ctx));
	ctx.exit_status = shell->exit_status;
	ctx.is_heredoc_delimiter = 0;
	for (ctx.node = shell->tokens; ctx.node != NULL; ctx.node = ctx.node->next)
	{
		if (should_skip_expansion(&ctx))
			continue;
		if (!initialize_expansion_buffer(&ctx))
			exit(EXIT_FAILURE);
		while (ctx.i < ctx.src_len)
		{
			if (handle_quotes_expander(&ctx))
				continue;
			if (process_variable(&ctx))
				continue;
			if (ctx.j + 1 >= ctx.buf_size)
			{
				ctx.buf_size *= 2;
				ctx.expanded = ft_realloc(ctx.expanded, ctx.buf_size);
				if (!ctx.expanded)
				{
					ft_putstr_fd("Memory reallocation error during expansion.\n", 2);
					exit(EXIT_FAILURE);
				}
			}
			ctx.expanded[ctx.j++] = ctx.source[ctx.i++];
		}
		ctx.expanded[ctx.j] = '\0';
		free(ctx.node->string);
		ctx.node->string = ctx.expanded;
	}
}

// /*
//  * Helper: Returns 1 if the token string is enclosed in single quotes.
//  * In that case, we skip parameter expansion.
//  */
// int is_single_quoted(const char *str)
// {
// 	int len = ft_strlen(str);
// 	return (len >= 2 && str[0] == '\'' && str[len - 1] == '\'');
// }
// /*
//  * Helper: Returns 1 if the token string is enclosed in matching quotes (either single or double).
//  * Such tokens will have only their first and last characters removed during quote removal.
//  */
// int is_quoted(const char *str)
// {
// 	int len = ft_strlen(str);
// 	if (len < 2)
// 		return (0);
// 	if ((str[0] == '\'' && str[len - 1] == '\'') ||
// 		(str[0] == '\"' && str[len - 1] == '\"'))
// 		return (1);
// 	return (0);
// }
//char *expand_exit_status(const char *str, size_t *i, size_t *j, size_t *cap, char *result, int exit_status)
//
//  // Expands the $? special parameter to the current exit status
//  // Updates position indices and reallocates buffer if needed
//  // Returns updated result buffer or NULL on failure
//  //
// {
// 	*i += 2; // Skip "$?"
// 	char status_str[16];
// 	sprintf(status_str, "%d", exit_status);//////////////////////////////////////////////////
// 	size_t status_len = ft_strlen(status_str);
// 	// Ensure buffer is large enough
// 	while (*j + status_len + 1 >= *cap)
// 	{
// 		*cap *= 2;
// 		result = ft_realloc(result, *cap);
// 		if (!result)
// 			return NULL;
// 	}
// 	ft_strcpy(&result[*j], status_str);
// 	*j += status_len;
// 	return result;
// }
// char *expand_digit_parameter(const char *str, size_t *i, size_t *j, size_t *cap, char *result)
// //  Expands digit-based parameters like $0, $1, etc.
// //  $0 is replaced with "minishell", while other digits are preserved
// //  Updates position indices and reallocates buffer if needed
// //  Returns updated result buffer or NULL on failure
// {
//     (*i)++; // skip '$'
//     size_t digit_start = *i;
//     // Collect all consecutive digits
//     while (str[*i] && isdigit(str[*i]))
//         (*i)++;
//     size_t digit_count = *i - digit_start;
//     // If the first digit is '0', replace it with "minishell"
//     if (str[digit_start] == '0')
//     {
//         char *shellname = "minishell";
//         size_t shell_len = strlen(shellname);
//         while (*j + shell_len + 1 >= *cap)
//         {
//             *cap *= 2;
//             result = ft_realloc(result, *cap);
//             if (!result)
//                 return NULL;
//         }
//         ft_strcpy(&result[*j], shellname);
//         *j += shell_len;
//     }
//     // Append any remaining digits after the first one
//     if (digit_count > 1)
//     {
//         size_t rest_len = digit_count - 1;
//         while (*j + rest_len + 1 >= *cap)
//         {
//             *cap *= 2;
//             result = ft_realloc(result, *cap);
//             if (!result)
//                 return NULL;
//         }
//         strncpy(&result[*j], str + digit_start + 1, rest_len);
//         *j += rest_len;
//     }
//     return result;
// }
// char *expand_environment_variable(const char *str, size_t *i, size_t *j, size_t *cap, char *result)
// // Expands standard environment variables like $HOME, $PATH, etc.
// // Looks up the variable value using getenv()
// // Updates position indices and reallocates buffer if needed
// // Returns updated result buffer or NULL on failure
// {
//     (*i)++; // Skip the '$'
//     size_t var_start = *i;
//     while (str[*i] && (isalnum(str[*i]) || str[*i] == '_'))
//         (*i)++;
//     size_t var_len = *i - var_start;
//     char var_name[var_len + 1];
//     strncpy(var_name, str + var_start, var_len);
//     var_name[var_len] = '\0';
//     char *env_value = getenv(var_name);
//     if (!env_value)
//         env_value = ""; // Substitute empty string if not found
//     size_t env_len = strlen(env_value);
//     while (*j + env_len + 1 >= *cap)
//     {
//         *cap *= 2;
//         result = ft_realloc(result, *cap);
//         if (!result)
//             return NULL;
//     }
//     ft_strcpy(&result[*j], env_value);
//     *j += env_len;
//     return result;
// }//27
// * earlier versions of expand_tokens
// * Parameter Expansion:
// * Scans the string for occurrences of a '$'. The special case of "$?" is replaced
// * with the shell's exit status from t_shell->exit_status.
// * Regular variables (starting with a letter or '_') are looked up via getenv().
// * Additionally, if '$' is followed by a digit, we handle it specially:
// *   - If the first digit is '0', replace it with "minishell" and append any remaining digits.
// *   - Otherwise, skip the first digit and append any remaining digits.
// *
// char *parameter_expansion(const char *str, int exit_status)
// {
// 	size_t len;
// 	size_t cap;
// 	char *result;
// 	size_t i;
// 	size_t j;
// 	len = ft_strlen(str);
// 	cap = len * 2 + 1;
// 	result = malloc(cap);
// 	i = 0;
// 	j = 0;
// 	if (!result)
// 		return NULL;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			// Handle "$?" expansion.
// 			if (str[i + 1] == '?')
// 			{
// 				result = expand_exit_status(str, &i, &j, &cap, result, exit_status);
// 				if (!result)
// 					return NULL;
// 				continue;
// 			}
// 			// Handle digit-based parameters, e.g. "$1", "$023", etc.
// 			if (str[i + 1] && isdigit(str[i + 1]))
// 			{
// 				result = expand_digit_parameter(str, &i, &j, &cap, result);
// 				if (!result)
// 					return NULL;
// 				continue;
// 			}
// 			// Handle standard variable names: $VAR (must start with letter or '_')
// 			if (str[i + 1] && (isalpha(str[i + 1]) || str[i + 1] == '_'))
// 			{
// 				result = expand_environment_variable(str, &i, &j, &cap, result);
// 				if (!result)
// 					return NULL;
// 				continue;
// 			}
// 			else
// 			{
// 				// If '$' is not followed by a valid identifier or digit, copy it literally.
// 				result[j++] = str[i++];
// 			}
// 		}
// 		else
// 		{
// 			result[j++] = str[i++];
// 		}
// 		if (j + 1 >= cap)
// 		{
// 			cap *= 2;
// 			result = ft_realloc(result, cap);
// 			if (!result)
// 				return NULL;
// 		}
// 	}
// 	result[j] = '\0';
// 	return result;
// }
