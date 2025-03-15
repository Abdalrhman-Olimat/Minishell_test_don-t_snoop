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







char *get_input(void) 
{
    char *input = readline("\001\033[32m\002minishell>\001\033[33m\002 ");
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
    // char *a = malloc(sizeof(char) * 11); // Allocate enough memory for the string and null terminator
    // strcpy(a, "abdalrhman");
    // free(a);

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
            
            if (!shell.tokens) {
                free(input);
                continue; // Skip execution on tokenizer error.
            }
            
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