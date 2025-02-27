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

/*int main()
{
char *input;

while ((input = readline("minishell>")) != NULL)
{
	if (*input)
	{
		printf("You entered: %s\n", input);
	}
	free(input);
}
return 0;

}*/

/*

tokenizer
void tokenizer(char *input,int len)
if '
if "
if < > 
if |
if &

*/
// typedef struct  s_input
// {
//     char *command;
//     int type;
//     struct t_node	*next;
// } t_input;

// void tokenizer(t_input a,char *input,int len)
// {
// 	int i = -1;
// 	while(i++ < len)
// 	{
// 	 while (input[i] == ' ' || input[i] == '\t')
// 	 i++;
// 	 while (ft_isalpha(input[i]))
// 	 {
// 		a.command = ft_strjoin(a.command,input[i]);
// 		i++;
// 	 }
// 	 if(input[i] == 39 )//'
// 	 	while (input[i] != 39)
// 		{
// 			/* code */
// 		}

// 	}
// }
// char *get_input(void)
// {
// 	char *input = readline("minishell> ");  // Prompt is included here, not just NULL
// 	if (input == NULL) {
// 		printf("exit\n");
// 		exit(0);  // Exit if input is NULL (e.g., CTRL+D)
// 	}
// 	if (ft_strlen(input) > 0) {
// 		add_history(input);  // Add non-empty input to history
// 	}
// 	return input;
// }

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
//     // //...
// 	t_input *a;
	
// 	while (1) {
// 		char *input = get_input();  // Get input with prompt
// 		if (ft_strlen(input) > 0)
// 		{   // Process non-empty input only
// 			//printf("You entered: %s\n", input);
// 			// Future: Tokenize input here
// 			tokenizer(*a, input, ft_strlen(input));
// 		}
// 		free(input);  // Clean up memory
// 	}
// 	return 0;
// }








// // Token types
// #define TYPE_WORD 0      // Regular word (e.g., "cat", "text")
// #define TYPE_PIPE 1      // |
// #define TYPE_REDIR_IN 2  // <
// #define TYPE_REDIR_OUT 3 // >
// #define TYPE_HEREDOC 4   // <<
// #define TYPE_APPEND 5    // >>

// // Node structure for the linked list
// typedef struct s_input
// {
//     char *string;
//     int type;
//     struct s_input *next;
// } t_input;

// // Function to calculate string length (assuming ft_strlen is custom)
// size_t ft_strlen(const char *s)
// {
//     size_t len = 0;
//     while (s[len])
//         len++;
//     return len;
// }

// // Add a new node to the linked list
// t_input *create_node(char *str, int type)
// {
//     t_input *new_node = malloc(sizeof(t_input));
//     if (!new_node)
//         return NULL;
//     new_node->string = strdup(str); // Duplicate string to avoid pointer issues
//     new_node->type = type;
//     new_node->next = NULL;
//     return new_node;
// }

// // Append a node to the end of the list
// void append_node(t_input **head, char *str, int type)
// {
//     t_input *new_node = create_node(str, type);
//     if (!*head)
//     {
//         *head = new_node;
//         return;
//     }
//     t_input *tmp = *head;
//     while (tmp->next)
//         tmp = tmp->next;
//     tmp->next = new_node;
// }

// // Free the linked list
// void free_list(t_input *head)
// {
//     t_input *tmp;
//     while (head)
//     {
//         tmp = head;
//         head = head->next;
//         free(tmp->string);
//         free(tmp);
//     }
// }

// // Tokenizer function
// t_input *tokenizer(char *input, int len)
// {
//     t_input *head = NULL;
//     int i = 0;
//     char *start;

//     while (i < len)
//     {
//         // Skip whitespace
//         while (i < len && (input[i] == ' ' || input[i] == '\t'))
//             i++;
//         if (i >= len)
//             break;

//         start = &input[i];

//         // Handle quotes
//         if (input[i] == '"' || input[i] == '\'')
//         {
//             char quote = input[i];
//             i++;
//             start = &input[i];
//             while (i < len && input[i] != quote)
//                 i++;
//             if (i < len)
//             {
//                 input[i] = '\0'; // Temporarily terminate for strdup
//                 append_node(&head, start, TYPE_WORD);
//                 input[i] = quote; // Restore original character
//                 i++; // Skip closing quote
//             }
//             continue;
//         }

//         // Handle metacharacters
//         if (input[i] == '|')
//         {
//             append_node(&head, "|", TYPE_PIPE);
//             i++;
//         }
//         else if (input[i] == '<' && input[i + 1] == '<')
//         {
//             append_node(&head, "<<", TYPE_HEREDOC);
//             i += 2;
//         }
//         else if (input[i] == '>' && input[i + 1] == '>')
//         {
//             append_node(&head, ">>", TYPE_APPEND);
//             i += 2;
//         }
//         else if (input[i] == '<')
//         {
//             append_node(&head, "<", TYPE_REDIR_IN);
//             i++;
//         }
//         else if (input[i] == '>')
//         {
//             append_node(&head, ">", TYPE_REDIR_OUT);
//             i++;
//         }
//         else
//         {
//             // Handle words (non-metacharacters)
//             while (i < len && input[i] != ' ' && input[i] != '\t' && 
//                    input[i] != '|' && input[i] != '<' && input[i] != '>')
//                 i++;
//             if (i > (start - input))
//             {
//                 char tmp = input[i];
//                 input[i] = '\0'; // Temporarily terminate
//                 append_node(&head, start, TYPE_WORD);
//                 input[i] = tmp; // Restore
//             }
//         }
//     }
//     return head;
// }

// // Get input from readline
// char *get_input(void)
// {
//     char *input = readline("minishell> ");
//     if (input == NULL)
//     {
//         printf("exit\n");
//         exit(0);
//     }
//     if (ft_strlen(input) > 0)
//         add_history(input);
//     return input;
// }

// // Print the token list (for debugging)
// void print_tokens(t_input *head)
// {
//     t_input *tmp = head;
//     while (tmp)
//     {
//         printf("Token: '%s', Type: %d\n", tmp->string, tmp->type);
//         tmp = tmp->next;
//     }
// }

// int main(void)
// {
//     while (1)
//     {
//         char *input = get_input();
//         if (ft_strlen(input) > 0)
//         {
//             t_input *tokens = tokenizer(input, ft_strlen(input));
//             print_tokens(tokens); // Debug output
//             free_list(tokens);    // Clean up token list
//         }
//         free(input); // Clean up readline input
//     }
//     return 0;
// }







/*chat*/





#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

#define TYPE_WORD 0      // Regular word
#define TYPE_PIPE 1      // |
#define TYPE_REDIR_IN 2  // <
#define TYPE_REDIR_OUT 3 // >
#define TYPE_HEREDOC 4   // <<
#define TYPE_APPEND 5    // >>

typedef struct s_input
{
    char *string;
    int type;
    struct s_input *next;
} t_input;

size_t ft_strlen(const char *s)
{
    size_t len = 0;
    while (s[len])
        len++;
    return len;
}

t_input *create_node(char *str, int type)
{
    t_input *new_node = malloc(sizeof(t_input));
    if (!new_node)
        return NULL;
    new_node->string = strdup(str);
    if (!new_node->string)
    {
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
    while (head)
    {
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
    char *start;
    char buffer[1024];  // Buffer to build words with quotes
    int buf_index;

    while (i < len)
    {
        while (i < len && (input[i] == ' ' || input[i] == '\t'))
            i++;
        if (i >= len)
            break;

        // Handle metacharacters
        if (input[i] == '|')
        {
            append_node(&head, "|", TYPE_PIPE);
            i++;
        }
        else if (input[i] == '<')
        {
            if ((i + 1 < len) && (input[i + 1] == '<'))
            {
                append_node(&head, "<<", TYPE_HEREDOC);
                i += 2;
            }
            else
            {
                append_node(&head, "<", TYPE_REDIR_IN);
                i++;
            }
        }
        else if (input[i] == '>')
        {
            if ((i + 1 < len) && (input[i + 1] == '>'))
            {
                append_node(&head, ">>", TYPE_APPEND);
                i += 2;
            }
            else
            {
                append_node(&head, ">", TYPE_REDIR_OUT);
                i++;
            }
        }
        else
        {
            // Handle words, including embedded quotes
            buf_index = 0;
            start = &input[i];

            while (i < len && input[i] != ' ' && input[i] != '\t' &&
                   input[i] != '|' && input[i] != '<' && input[i] != '>')
            {
                if (input[i] == '"' || input[i] == '\'')
                {
                    char quote = input[i++];
                    buffer[buf_index++] = quote; // Store quote as part of the word

                    while (i < len && input[i] != quote)
                        buffer[buf_index++] = input[i++];
                    
                    if (i < len)
                        buffer[buf_index++] = input[i++]; // Store closing quote
                }
                else
                {
                    buffer[buf_index++] = input[i++];
                }
            }
            buffer[buf_index] = '\0'; // Null-terminate

            append_node(&head, buffer, TYPE_WORD);
        }
    }
    return head;
}

char *get_input(void)
{
    char *input = readline("minishell> ");
    if (input == NULL)
    {
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
    while (tmp)
    {
        printf("Token: %s, Type: %d\n", tmp->string, tmp->type);
        tmp = tmp->next;
    }
}

int main(void)
{
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




// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <readline/readline.h>
// #include <readline/history.h>

// #define TYPE_WORD 0      // Regular word
// #define TYPE_PIPE 1      // |
// #define TYPE_REDIR_IN 2  // <
// #define TYPE_REDIR_OUT 3 // >
// #define TYPE_HEREDOC 4   // <<
// #define TYPE_APPEND 5    // >>

// typedef struct s_input {
//     char *string;
//     int type;
//     struct s_input *next;
// } t_input;

// size_t ft_strlen(const char *s) {
//     size_t len = 0;
//     while (s[len])
//         len++;
//     return len;
// }

// t_input *create_node(char *str, int type) {
//     t_input *new_node = malloc(sizeof(t_input));
//     if (!new_node)
//         return NULL;
//     new_node->string = strdup(str);
//     if (!new_node->string) {
//         free(new_node);
//         return NULL;
//     }
//     new_node->type = type;
//     new_node->next = NULL;
//     return new_node;
// }

// void append_node(t_input **head, char *str, int type) {
//     t_input *new_node = create_node(str, type);
//     if (!new_node) {
//         fprintf(stderr, "Memory allocation failed\n");
//         exit(EXIT_FAILURE);
//     }
//     if (!*head) {
//         *head = new_node;
//         return;
//     }
//     t_input *tmp = *head;
//     while (tmp->next)
//         tmp = tmp->next;
//     tmp->next = new_node;
// }

// void free_list(t_input *head) {
//     t_input *tmp;
//     while (head) {
//         tmp = head;
//         head = head->next;
//         free(tmp->string);
//         free(tmp);
//     }
// }

// /*
//   The tokenizer works as follows:
//   1. Skip initial whitespace.
//   2. If the next character is a metacharacter (|, <, >) and not part of a word, process it as its own token.
//      (Also handling << and >>.)
//   3. Otherwise, start building a word token in a temporary buffer.
//      - While the current character is not whitespace:
//          • If a metacharacter is encountered and the token already has content, stop (so that metacharacters
//            outside of any quotes become separate tokens).
//          • If a quote is encountered, process the quoted segment:
//              – If this is the very first character in the token, omit the quotes.
//              – Otherwise, include the quote characters.
//          • Else, append the character.
//   4. Once the token is complete, append it as a TYPE_WORD node.
// */
// t_input *tokenizer(char *input, int len) {
//     t_input *head = NULL;
//     int i = 0;
//     while (i < len) {
//         // Skip whitespace
//         while (i < len && (input[i] == ' ' || input[i] == '\t'))
//             i++;
//         if (i >= len)
//             break;

//         /* 
//           If the current character is a metacharacter and we’re not in the middle of a word,
//           process it as a separate token.
//         */
//         if ((input[i] == '|' || input[i] == '<' || input[i] == '>')) {
//             if (input[i] == '<' && (i + 1 < len && input[i + 1] == '<')) {
//                 append_node(&head, "<<", TYPE_HEREDOC);
//                 i += 2;
//                 continue;
//             } else if (input[i] == '>' && (i + 1 < len && input[i + 1] == '>')) {
//                 append_node(&head, ">>", TYPE_APPEND);
//                 i += 2;
//                 continue;
//             } else if (input[i] == '|') {
//                 append_node(&head, "|", TYPE_PIPE);
//                 i++;
//                 continue;
//             } else if (input[i] == '<') {
//                 append_node(&head, "<", TYPE_REDIR_IN);
//                 i++;
//                 continue;
//             } else if (input[i] == '>') {
//                 append_node(&head, ">", TYPE_REDIR_OUT);
//                 i++;
//                 continue;
//             }
//         }

//         // Build a word token (may include quoted segments)
//         char token_buf[len + 1]; // worst-case size
//         int token_index = 0;
//         while (i < len && input[i] != ' ' && input[i] != '\t') {
//             /* 
//               If a metacharacter is encountered after some token content,
//               it should end the current token.
//             */
//             if ((input[i] == '|' || input[i] == '<' || input[i] == '>') && token_index > 0)
//                 break;
//             if (input[i] == '\"' || input[i] == '\'') {
//                 char quote = input[i];
//                 int at_start = (token_index == 0);
//                 // If the token starts with a quote, omit it from the token.
//                 if (!at_start) {
//                     token_buf[token_index++] = input[i];
//                 }
//                 i++; // skip the opening quote
//                 while (i < len && input[i] != quote) {
//                     token_buf[token_index++] = input[i];
//                     i++;
//                 }
//                 if (i < len && input[i] == quote) {
//                     if (!at_start) {
//                         token_buf[token_index++] = input[i];
//                     }
//                     i++; // skip the closing quote
//                 } else {
//                     fprintf(stderr, "Error: Unclosed quote\n");
//                     break;
//                 }
//             } else {
//                 token_buf[token_index++] = input[i];
//                 i++;
//             }
//         }
//         token_buf[token_index] = '\0';
//         if (token_index > 0)
//             append_node(&head, token_buf, TYPE_WORD);
//     }
//     return head;
// }

// char *get_input(void) {
//     char *input = readline("minishell> ");
//     if (input == NULL) {
//         printf("exit\n");
//         exit(0);
//     }
//     if (ft_strlen(input) > 0)
//         add_history(input);
//     return input;
// }

// void print_tokens(t_input *head) {
//     t_input *tmp = head;
//     while (tmp) {
//         printf("Token: %s, Type: %d\n", tmp->string, tmp->type);
//         tmp = tmp->next;
//     }
// }

// int main(void) {
//     while (1) {
//         char *input = get_input();
//         int len = ft_strlen(input);
//         if (len > 0) {
//             t_input *tokens = tokenizer(input, len);
//             print_tokens(tokens);
//             free_list(tokens);
//         }
//         free(input);
//     }
//     return 0;
// }

