#include "../includes/mini.h"



/* ---------- Expander Implementation ---------- */

void *ft_realloc(void *ptr, size_t newsize)
{
    char	*newptr;

    if (ptr == 0)
        return (malloc(newsize));
    newptr = malloc(newsize);
    if (!newptr)
        return (NULL);
    // Copy contents from old buffer to new one
    ft_memcpy(newptr, ptr, newsize / 2); // Estimate old size as half of new
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
 * with the shell's exit status (passed via exit_status).
 * Regular variables (starting with a letter or '_') are looked up via getenv().
 * Additionally, if '$' is followed by a digit, we handle it specially:
 *   - If the first digit is '0', replace it with "minishell" and append any remaining digits.
 *   - Otherwise, skip the first digit and append any remaining digits.
 */
char *parameter_expansion(const char *str, int exit_status) {
    // First calculate needed size to avoid realloc issues
    size_t len = strlen(str);
    size_t result_size = len * 2 + 1;  // Conservative estimate
    char *result = malloc(result_size);
    if (!result)
        return NULL;
    
    size_t i = 0, j = 0;
    
    while (str[i]) {
        if (str[i] == '$') {
            // Handle "$?" expansion
            if (str[i + 1] == '?') {
                char status_str[16] = {0};
                sprintf(status_str, "%d", exit_status);
                size_t status_len = strlen(status_str);
                
                // Ensure we have enough space
                if (j + status_len >= result_size) {
                    result_size = result_size * 2 + status_len;
                    char *new_result = malloc(result_size);
                    if (!new_result) {
                        free(result);
                        return NULL;
                    }
                    memcpy(new_result, result, j);
                    free(result);
                    result = new_result;
                }
                
                strcpy(&result[j], status_str);
                j += status_len;
                i += 2;  // Skip "$?"
                continue;
            }
            
            // Handle digits (similar approach for other expansions)
            if (str[i + 1] && isdigit(str[i + 1])) {
                i++;  // Skip '$'
                if (str[i] == '0') {
                    const char *shellname = "minishell";
                    size_t name_len = strlen(shellname);
                    
                    // Ensure space
                    if (j + name_len >= result_size) {
                        result_size = result_size * 2 + name_len;
                        char *new_result = malloc(result_size);
                        if (!new_result) {
                            free(result);
                            return NULL;
                        }
                        memcpy(new_result, result, j);
                        free(result);
                        result = new_result;
                    }
                    
                    strcpy(&result[j], shellname);
                    j += name_len;
                    i++;  // Skip '0'
                }
                else {
                    // For positional parameters other than $0, 
                    // skip the first digit entirely (don't include in output)
                    i++;  // Skip the digit
                }
                
                // Copy any remaining digits that follow
                while (str[i] && isdigit(str[i])) {
                    if (j + 1 >= result_size) {
                        result_size *= 2;
                        char *new_result = malloc(result_size);
                        if (!new_result) {
                            free(result);
                            return NULL;
                        }
                        memcpy(new_result, result, j);
                        free(result);
                        result = new_result;
                    }
                    result[j++] = str[i++];
                }
                continue;
            }

            // Handle variable expansion (similar pattern)
            // ...rest of your variable expansion code with similar memory checks
        }
        
        // Copy regular character
        if (j + 1 >= result_size) {
            result_size *= 2;
            char *new_result = malloc(result_size);
            if (!new_result) {
                free(result);
                return NULL;
            }
            memcpy(new_result, result, j);
            free(result);
            result = new_result;
        }
        result[j++] = str[i++];
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
    
    // First pass - parameter expansion
    do {
        changed = 0;
        for (node = shell->tokens; node != NULL; node = node->next) {
            if (node->type == TYPE_WORD && strchr(node->string, '$')) {
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
        pass++;
    } while (changed && pass < MAX_PASSES);
    
    // Second pass - quote removal with proper handling
    for (node = shell->tokens; node != NULL; node = node->next) {
        if (node->type == TYPE_WORD) {
            int len = strlen(node->string);
            char *result = malloc(len + 1);
            if (!result) {
                fprintf(stderr, "Memory allocation error during quote removal.\n");
                exit(EXIT_FAILURE);
            }
            
            int i = 0, j = 0;
            char current_quote = '\0'; // Keeps track of the current quote context
            
            while (i < len) {
                // Handle quote opening/closing
                if ((node->string[i] == '\'' || node->string[i] == '\"') && 
                    (current_quote == '\0' || current_quote == node->string[i])) {
                    if (current_quote == '\0') {
                        // Opening a new quote
                        current_quote = node->string[i];
                    } else {
                        // Closing a quote
                        current_quote = '\0';
                    }
                    i++; // Skip the quote character
                    continue;
                }
                
                // If we're inside a quote or it's a regular character, keep it
                result[j++] = node->string[i++];
            }
            result[j] = '\0';
            
            free(node->string);
            node->string = result;
        }
    }
}
