#include "../includes/mini.h"



/* ---------- Expander Implementation ---------- */

void	*ft_realloc(void *ptr, size_t newsize)
{
	char	*newptr;
	size_t	cursize;

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



/*
 * Helper: Returns 1 if the token string is enclosed in single quotes.
 * In that case, we skip parameter expansion.
 */
int is_single_quoted(const char *str) {
    int len = strlen(str);
    return (len >= 2 && str[0] == '\'' && str[len - 1] == '\'');
}

/*
 * Helper: Returns 1 if the token string is enclosed in matching quotes (either single or double).
 * Such tokens will have only their first and last characters removed during quote removal.
 */
int is_quoted(const char *str) {
    int len = strlen(str);
    if (len < 2)
        return 0;
    if ((str[0] == '\'' && str[len - 1] == '\'') ||
        (str[0] == '\"' && str[len - 1] == '\"'))
        return 1;
    return 0;
}

/*
 * Parameter Expansion:
 * Scans the string for occurrences of a '$'. The special case of "$?" is replaced
 * with the shell's exit status from t_shell->exit_status.
 * Regular variables (starting with a letter or '_') are looked up via getenv().
 */
/*
 * Parameter Expansion:
 * Scans the string for occurrences of a '$'. The special case of "$?" is replaced
 * with the shell's exit status from t_shell->exit_status.
 * Regular variables (starting with a letter or '_') are looked up via getenv().
 * Additionally, if '$' is followed by a digit, we handle it specially:
 *   - If the first digit is '0', expand it to "-bash" then append any remaining digits.
 *   - Otherwise, skip the first digit and append any remaining digits.
 */
/*
 * Parameter Expansion:
 * Scans the string for occurrences of a '$'. The special case of "$?" is replaced
 * with the shell's exit status (passed via exit_status).
 * Regular variables (starting with a letter or '_') are looked up via getenv().
 * Additionally, if '$' is followed by a digit, we handle it specially:
 *   - If the first digit is '0', replace it with "minishell" and append any remaining digits.
 *   - Otherwise, skip the first digit and append any remaining digits.
 */
char *parameter_expansion(const char *str, int exit_status) {
    size_t len = strlen(str);
    size_t cap = len * 2 + 1;  // Start with an initial capacity.
    char *result = malloc(cap);
    if (!result)
        return NULL;
    size_t i = 0, j = 0;
    
    while (str[i]) {
        if (str[i] == '$') {
            // Handle "$?" expansion.
            if (str[i + 1] == '?') {
                i += 2;  // Skip "$?"
                char status_str[16];
                sprintf(status_str, "%d", exit_status);
                size_t status_len = strlen(status_str);
                while (j + status_len + 1 >= cap) {
                    cap *= 2;
                    result = ft_realloc(result, cap);
                    if (!result)
                        return NULL;
                }
                strcpy(&result[j], status_str);
                j += status_len;
                continue;
            }
            // Handle digit-based parameters, e.g. "$1", "$023", etc.
            if (str[i + 1] && isdigit(str[i + 1])) {
                i++; // skip '$'
                size_t digit_start = i;
                // Collect all consecutive digits.
                while (str[i] && isdigit(str[i]))
                    i++;
                size_t digit_count = i - digit_start;
                // If the first digit is '0', replace it with "minishell".
                if (str[digit_start] == '0') {
                    char *shellname = "minishell";
                    size_t shell_len = strlen(shellname);
                    while (j + shell_len + 1 >= cap) {
                        cap *= 2;
                        result = ft_realloc(result, cap);
                        if (!result)
                            return NULL;
                    }
                    strcpy(&result[j], shellname);
                    j += shell_len;
                }
                // Append any remaining digits after the first one.
                if (digit_count > 1) {
                    size_t rest_len = digit_count - 1;
                    while (j + rest_len + 1 >= cap) {
                        cap *= 2;
                        result = ft_realloc(result, cap);
                        if (!result)
                            return NULL;
                    }
                    strncpy(&result[j], str + digit_start + 1, rest_len);
                    j += rest_len;
                }
                continue;
            }
            // Handle standard variable names: $VAR (must start with letter or '_').
            if (str[i + 1] && (isalpha(str[i + 1]) || str[i + 1] == '_')) {
                i++;  // Skip the '$'
                size_t var_start = i;
                while (str[i] && (isalnum(str[i]) || str[i] == '_'))
                    i++;
                size_t var_len = i - var_start;
                char var_name[var_len + 1];
                strncpy(var_name, str + var_start, var_len);
                var_name[var_len] = '\0';
                
                char *env_value = getenv(var_name);
                if (!env_value)
                    env_value = "";  // Substitute empty string if not found.
                size_t env_len = strlen(env_value);
                while (j + env_len + 1 >= cap) {
                    cap *= 2;
                    result = ft_realloc(result, cap);
                    if (!result)
                        return NULL;
                }
                strcpy(&result[j], env_value);
                j += env_len;
            } else {
                // If '$' is not followed by a valid identifier or digit, copy it literally.
                result[j++] = str[i++];
            }
        } else {
            result[j++] = str[i++];
        }
        if (j + 1 >= cap) {
            cap *= 2;
            result = ft_realloc(result, cap);
            if (!result)
                return NULL;
        }
    }
    result[j] = '\0';
    return result;
}

/*
 * Expander:
 * Iterates over all tokens in the shell's token list.
 * First, process parameter expansion for tokens that are not single-quoted.
 * Then, perform quote removal on tokens that start and end with a quote.
 */
void expand_tokens(t_shell *shell) {
    int changed;
    int pass = 0;
    const int MAX_PASSES = 5;
    t_input *node;
    
    // Repeatedly scan for parameter expansions.
    do {
        changed = 0;
        for (node = shell->tokens; node != NULL; node = node->next) {
            if (node->type == TYPE_WORD) {
                if (!is_single_quoted(node->string) && strchr(node->string, '$')) {
                    char *expanded = parameter_expansion(node->string, shell->exit_status);
                    if (!expanded) {
                        fprintf(stderr, "Memory allocation error during expansion.\n");
                        exit(EXIT_FAILURE);
                    }
                    if (strcmp(expanded, node->string) != 0) {
                        free(node->string);
                        node->string = expanded;
                        changed = 1;
                    } else {
                        free(expanded);
                    }
                }
            }
        }
        pass++;
    } while (changed && pass < MAX_PASSES);
    
    // Quote removal: remove only the first and last character if the token is quoted.
    for (node = shell->tokens; node != NULL; node = node->next) {
        if (node->type == TYPE_WORD && is_quoted(node->string)) {
            int len = strlen(node->string);
            char *stripped = malloc(len - 1);  // (len-2) characters + NUL
            if (!stripped) {
                fprintf(stderr, "Memory allocation error during quote removal.\n");
                exit(EXIT_FAILURE);
            }
            strncpy(stripped, node->string + 1, len - 2);
            stripped[len - 2] = '\0';
            free(node->string);
            node->string = stripped;
        }
    }
}
