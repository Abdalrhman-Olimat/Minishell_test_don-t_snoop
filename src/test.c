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




#define TYPE_WORD 0      // Regular word (e.g., "echo", "cat")
#define TYPE_PIPE 1      // |
#define TYPE_REDIR_IN 2  // <
#define TYPE_REDIR_OUT 3 // >
#define TYPE_HEREDOC 4   // <<
#define TYPE_APPEND 5    // >>

typedef struct s_input {
    char *string;
    int type;
    struct s_input *next;
} t_input;



t_input *create_node(char *str, int type)
{
    t_input *new_node = malloc(sizeof(t_input));
    if (!new_node)
        return NULL;
    new_node->string = strdup(str);
    if (!new_node->string) {
        free(new_node);
        return NULL;
    }
    new_node->type = type;
    new_node->next = NULL;
    return new_node;
}

void append_node(t_input **head, char *str, int type)
{
    t_input *new_node = create_node(str, type);
    if (!new_node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    if (!*head)
    {
        *head = new_node;
        return;
    }
    t_input *tmp = *head;
    while (tmp->next)
        tmp = tmp->next;
    tmp->next = new_node;
}

void free_list(t_input *head)
{
    t_input *tmp;
    while (head) {
        tmp = head;
        head = head->next;
        free(tmp->string);
        free(tmp);
    }
}


t_input *tokenizer(char *input, int len)
{
    t_input *head = NULL;
    int i = 0;
    char token_buf[len + 1];  // Maximum token size is the full input length.
    int token_index = 0;
    
    while (i < len)
    {
        // Skip whitespace; flush token buffer if needed.
        if (input[i] == ' ' || input[i] == '\t')
        {
            if (token_index > 0)
            {
                token_buf[token_index] = '\0';
                append_node(&head, token_buf, TYPE_WORD);
                token_index = 0;
            }
            i++;
            continue;
        }
        
        // Handle metacharacters if we're not building a token.
        if ((input[i] == '|' || input[i] == '<' || input[i] == '>') && token_index == 0)
        {
            if (input[i] == '<' && (i + 1 < len && input[i + 1] == '<')) {
                append_node(&head, "<<", TYPE_HEREDOC);
                i += 2;
                continue;
            }
            if (input[i] == '>' && (i + 1 < len && input[i + 1] == '>')) {
                append_node(&head, ">>", TYPE_APPEND);
                i += 2;
                continue;
            }
            if (input[i] == '|') {
                append_node(&head, "|", TYPE_PIPE);
                i++;
                continue;
            }
            if (input[i] == '<') {
                append_node(&head, "<", TYPE_REDIR_IN);
                i++;
                continue;
            }
            if (input[i] == '>') {
                append_node(&head, ">", TYPE_REDIR_OUT);
                i++;
                continue;
            }
        }
        
        // Handle quotes: include the quotes in the token.
        if (input[i] == '\'' || input[i] == '\"') {
            char quote = input[i];
            // Flush any token in progress.
            if (token_index > 0) {
                token_buf[token_index] = '\0';
                append_node(&head, token_buf, TYPE_WORD);
                token_index = 0;
            }
            char quoted_buf[len + 1];
            int qindex = 0;
            // Copy the opening quote.
            quoted_buf[qindex++] = input[i++];
            // Copy everything until the matching closing quote.
            while (i < len && input[i] != quote) {
                quoted_buf[qindex++] = input[i++];
            }
            // If matching quote found, copy it.
            if (i < len && input[i] == quote)
                quoted_buf[qindex++] = input[i++];
            else {
                fprintf(stderr, "Error: Unclosed quote\n");
                break;
            }
            quoted_buf[qindex] = '\0';
            append_node(&head, quoted_buf, TYPE_WORD);
            continue;
        }
        
        // Otherwise, accumulate the character in the token buffer.
        token_buf[token_index++] = input[i++];
    }
    
    // Flush any remaining token in the buffer.
    if (token_index > 0) {
        token_buf[token_index] = '\0';
        append_node(&head, token_buf, TYPE_WORD);
    }
    
    return head;
}

char *get_input(void) {
    char *input = readline("minishell> ");
    if (input == NULL) {
        printf("exit\n");
        exit(0);
    }
    if (ft_strlen(input) > 0)
        add_history(input);
    return input;
}

void print_tokens(t_input *head)
{
    t_input *tmp = head;
    while (tmp) {
        printf("Token: %s, Type: %d\n", tmp->string, tmp->type);
        tmp = tmp->next;
    }
}

int main(void) {
    while (1)
    {
        char *input = get_input();
        int len = ft_strlen(input);
        if (len > 0)
        {
            t_input *tokens = tokenizer(input, len);
            print_tokens(tokens);
            free_list(tokens);
        }
        free(input);
    }
    return 0;
}
