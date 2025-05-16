/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:24:52 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/16 23:03:26 by aeleimat         ###   ########.fr       */
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




void init_shell(t_shell *shell, char **envp)
{
    shell->exit_status = 0;
    shell->tokens = NULL;
    alloc_envp(shell, envp, 0);
    shell->analyzing_data.path = fetch_path(shell, 0);
    if (!shell->analyzing_data.path)
    {
        perror("Failed to fetch PATH");
        free_envp(shell);
        exit(1);
    }
    
}

void reset_shell(t_shell *shell)
{
    if (shell->tokens)
    {
        free_list(shell->tokens);
        shell->tokens = NULL;
    }
    // Reset any other state between commands
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

void mini_loop(t_shell *shell)
{
    while (1)
    {
        char *input = get_input();
        if (!input)
            break;
        int len = ft_strlen(input);
        if (len > 0)
        {
            shell->tokens = tokenizer(input, len);
            if (!shell->tokens) {
                free(input);
                continue;
            }
            if (syntax_checker(shell->tokens) == 0)
            {
                free_list(shell->tokens);
                free(input);
                continue;
            }
            expand_tokens(shell);
            print_tokens(shell->tokens); // For debugging
            //play_after_tokens(shell);       // Execute the command
            reset_shell(shell);
        }
        free(input);
    }
    reset_shell(shell);
    clear_history();
}

int main(int argc, char **argv, char **envp)
{
    t_shell shell;
    
    
    init_shell(&shell, envp);
    //signal shit should be here
    mini_loop(&shell);
    
    return shell.exit_status;
}
