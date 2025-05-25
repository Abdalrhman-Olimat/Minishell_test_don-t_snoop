/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:24:52 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/22 02:04:58 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int g_exit_status = 0;

void init_shell(t_shell *shell, char **envp)
{
    shell->exit_status = 0;
    shell->tokens = NULL;
    alloc_envp(shell, envp);
    shell->analyzing_data.path = fetch_path(shell, 0);
    if (!shell->analyzing_data.path)
    {
        perror("Failed to fetch PATH");
        free_envp(shell);
        exit(1);
    }
    // Set up signal handling
    setup_signals_interactive();
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
        // Update shell exit status from global
        shell->exit_status = g_exit_status;
        
        // Set up interactive signal handling before readline
        setup_signals_interactive();
        
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
            // print_tokens(shell->tokens); // For debugging
            play_after_tokens(shell);       // Execute the command
            // print_tokens(shell->tokens); // For debugging
            
            // Set up execution signal handling before running commands
            setup_signals_exec();
            
            //play_after_tokens(shell);   // Execute the command
            
            // Reset signals after execution
            setup_signals_interactive();
            
            reset_shell(shell);
        }
        // free(input); // double free when i do: [ls -la | ls -la]
    }
    reset_shell(shell);
    clear_history();
}

int main(int argc, char **argv, char **envp)
{
    t_shell shell;
    
    init_shell(&shell, envp);
    mini_loop(&shell);
    
    return shell.exit_status;
}
