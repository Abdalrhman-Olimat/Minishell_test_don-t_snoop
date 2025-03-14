/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:24:52 by aeleimat          #+#    #+#             */
/*   Updated: 2025/02/26 16:39:40 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"


// int main()
// {
// 	// Main loop
// 	// signal(SIGINT, SIG_IGN);  // Ignore SIGINT (CTRL+C) to allow ^C to exit gracefully
//     // signal(SIGQUIT, SIG_IGN);  // Ignore SIGQUIT (CTRL+\) to allow ^C to exit gracefully
//     // signal(SIGTSTP, SIG_IGN);  // Ignore SIGTSTP (CTRL+Z) to allow suspension of the shell
//     // signal(SIGTTIN, SIG_IGN);  // Ignore SIGTTIN (CTRL+T) to allow background jobs to continue
//     // signal(SIGTTOU, SIG_IGN);  // Ignore SIGTTOU (CTRL+O) to prevent suspension of the shell's foreground job
//     // signal(SIGCHLD, SIG_IGN);  // Ignore SIGCHLD (child process terminated) to prevent zombie processes
//     // // Add any other signal handlers here as needed







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
                // If '$' is not followed by a valid character, copy it literally.
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

char *get_input(void) 
{
    char *input = readline("minishell> ");
    if (input == NULL) {
        printf("exit\n");
        exit(0);
    }
    if (ft_strlen(input) > 0)
        add_history(input);
    return input;
}



int main(void)
{
    //int *a = calloc(500, 8);

    while (1)
    {
        char *input = get_input();
        if (!input)
            break;  // Handle EOF (Ctrl+D) gracefully.

        int len = ft_strlen(input);
        if (len > 0)
        {
            // Initialize shell state.
            t_shell shell;
            shell.exit_status = 0;  // Set an initial exit status. Update this value when a command runs.
            shell.tokens = tokenizer(input, len);
            
            
            if (syntax_checker(shell.tokens) == 0)
            {
                free_list(shell.tokens);
                free(input);
                continue; // Skip execution on syntax error.
            }
            // Proceed with further processing/execution.
            expand_tokens(&shell);
            print_tokens(shell.tokens); // Optional: print tokens after expansion.
            free_list(shell.tokens);
        }
        free(input);
    }
    return 0;
}