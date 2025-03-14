// #include "../includes/mini.h"

// static int is_redirection(int type)
// {
//     return (type == TYPE_REDIR_IN || type == TYPE_REDIR_OUT ||
//             type == TYPE_HEREDOC || type == TYPE_APPEND);
// }

// int syntax_checker(t_input *tokens)
// {
//     t_input *current = tokens;
//     int has_word = 0;         // Tracks if the current command segment has a word
//     t_input *last_token = NULL; // Keeps track of the last token for error context

//     // Handle empty input
//     if (!tokens)
//         return (1); // Empty input is often handled elsewhere; here we allow it

//     while (current != NULL)
//     {
//         if (current->type == TYPE_WORD)
//         {
//             has_word = 1; // A word validates the current command segment
//         }
//         else if (is_redirection(current->type))
//         {
//             // Redirection must be followed by a word
//             if (current->next == NULL || current->next->type != TYPE_WORD)
//             {
//                 ft_putstr_fd("minishell: syntax error near unexpected token ", 2);
//                 if (current->next == NULL)
//                     ft_putstr_fd("`newline'\n", 2);
//                 else
//                 {
//                     ft_putstr_fd("`", 2);
//                     ft_putstr_fd(current->next->string, 2);
//                     ft_putstr_fd("'\n", 2);
//                 }
//                 return (0);
//             }
//             // Skip the word after the redirection (e.g., "< file" moves past "file")
//             current = current->next;
//         }
//         else if (current->type == TYPE_PIPE)
//         {
//             // Pipe requires a preceding command with at least one word
//             if (has_word == 0)
//             {
//                 ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
//                 return (0);
//             }
//             has_word = 0; // Reset for the next command segment
//         }
//         else
//         {
//             // Unexpected token type (safety check for invalid types)
//             ft_putstr_fd("minishell: syntax error: unexpected token\n", 2);
//             return (0);
//         }
//         last_token = current;
//         current = current->next;
//     }

//     // After traversal, ensure the last command segment isn’t empty
//     if (has_word == 0)
//     {
//         if (last_token != NULL && last_token->type == TYPE_PIPE)
//             ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
//         else
//             ft_putstr_fd("minishell: syntax error: incomplete command\n", 2);
//         return (0);
//     }

//     return (1); // Syntax is valid
// }
