/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:24:52 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/30 05:14:04 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int g_exit_status = 0;

void init_shell(t_shell *shell, char **envp)
{
    // Zero out the entire structure to avoid uninitialized memory reads
    ft_memset(shell, 0, sizeof(t_shell));
    
    // Then set specific values
    shell->exit_status = 0;
    shell->tokens = NULL;
    shell->tokens_header = NULL;
    shell->cmds = NULL;
    shell->analyzing_data.args = NULL;
    shell->analyzing_data.cmds_count = 0;
    shell->heredoc_tracker.count = 0;
    
    alloc_envp(shell, envp);
    shell->analyzing_data.path = fetch_path(shell, 0);
    if (!shell->analyzing_data.path)
    {
        perror("Failed to fetch PATH");
        free_envp(shell);
        exit(1);
    }
    setup_signals_interactive();
}

void reset_shell(t_shell *shell)
{
    if (shell->tokens)
    {
        free_list(shell->tokens);
        shell->tokens = NULL;
    }
}

/* 
 * Clean up all allocated resources in the shell
 * This prevents memory leaks when the program exits
 */
void cleanup_shell(t_shell *shell)
{
    if (!shell)
        return;
        
    // Free token list
    reset_shell(shell);
    
    // Free shell->tokens_header if it exists
    if (shell->tokens_header)
    {
        free_list(shell->tokens_header);
        shell->tokens_header = NULL;
    }
    
    // Free command structures if they exist
    if (shell->cmds && shell->analyzing_data.cmds_count > 0)
    {
        free_cmds_all(shell->cmds, shell->analyzing_data.cmds_count, 0);
        shell->cmds = NULL;
    }
    
    // Free arguments array if it exists
    if (shell->analyzing_data.args)
    {
        if (shell->tokens)
        {
            free_token_array(shell->analyzing_data.args, count_tokens(shell->tokens));
        }
        else
        {
            // If args exist but tokens don't, free args directly
            free(shell->analyzing_data.args);
        }
        shell->analyzing_data.args = NULL;
    }
    
    // Free environment and paths
    free_both_envp_paths(shell);
}

char *get_input(void) 
{
    char *input = readline("minishell> ");
    if (input == NULL) {
        printf("exit\n");
        return NULL;
    }
    if (ft_strlen(input) > 0)
        add_history(input);
    return input;
}

void mini_loop(t_shell *shell)
{
    while (1)
    {
        shell->exit_status = g_exit_status;
        setup_signals_interactive();
        char *input = get_input();
        if (!input)
            break;
        int len = ft_strlen(input);
        if (len > 0)
        {
            // Initialize heredoc tracker before tokenizing
            shell->heredoc_tracker.count = 0;
            shell->tokens = tokenizer(shell, input, len);
            if (!shell->tokens) {
                free(input);
                continue;
            }
            if (syntax_checker(shell->tokens) == 0)
            {
                free_list(shell->tokens);
                shell->tokens = NULL; // Important: set to NULL after freeing
                free(input);
                continue;
            }
            // Initialize pointers to NULL before using them
            shell->cmds = NULL;
            shell->analyzing_data.args = NULL;
            shell->tokens_header = NULL;
            
            expand_tokens(shell);
            // print_tokens(shell->tokens); // For debugging
            play_after_tokens(shell);       // Execute the command
            
            // Comprehensive cleanup of all resources
            // Cleanup token_header after processing
            if (shell->tokens_header) {
                free_list(shell->tokens_header);
                shell->tokens_header = NULL;
            }
            
            // Cleanup any command structures
            if (shell->cmds && shell->analyzing_data.cmds_count > 0) {
                free_cmds_all(shell->cmds, shell->analyzing_data.cmds_count, 0);
                shell->cmds = NULL;
            }
            
            // Free args array if it still exists
            if (shell->analyzing_data.args) {
                if (shell->tokens) {
                    int count = count_tokens(shell->tokens);
                    free_token_array(shell->analyzing_data.args, count);
                } else {
                    free(shell->analyzing_data.args);
                }
                shell->analyzing_data.args = NULL;
            }
            
            // Ensure all tracked heredoc nodes are freed
            free_tracked_heredoc_nodes(&shell->heredoc_tracker);
            shell->heredoc_tracker.count = 0;
            
            setup_signals_exec();
            setup_signals_interactive();
            reset_shell(shell);
        }
        // Don't forget to free the input string
        free(input);
    }
    reset_shell(shell);
    clear_history();
}

int main(int argc, char **argv, char **envp)
{
    t_shell shell;
    
    init_shell(&shell, envp);
    mini_loop(&shell);
    cleanup_shell(&shell); // Ensure all allocated memory is freed before exit
    free_tracked_heredoc_nodes(&shell.heredoc_tracker); // Free any tracked heredoc nodes
    return (shell.exit_status);
}
