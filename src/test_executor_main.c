/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_executor_main.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:24:52 by aeleimat          #+#    #+#             */
/*   Updated: 2025/03/17 12:49:06 by aeleimat         ###   ########.fr       */
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


int count_args(t_input *tokens)
{
    int count = 0;
    t_input *tmp = tokens;
    while (tmp && tmp->type != TYPE_PIPE) {
        if (tmp->type == TYPE_REDIR_IN ||
            tmp->type == TYPE_REDIR_OUT ||
            tmp->type == TYPE_HEREDOC  ||
            tmp->type == TYPE_APPEND) {
            // Skip both the redirection operator and its file token.
            tmp = tmp->next;
            if (tmp)
                tmp = tmp->next;
            continue;
        }
        if (tmp->type == TYPE_WORD)
            count++;
        tmp = tmp->next;
    }
    return count;
}


 /*----- Built-in Command Stubs -----
  * These functions implement our built-in commands.
  * In a real shell these would be fully featured; here are simple stub implementations.
  */
 int ft_echo(char **argv) {
     int i = 1;
     int suppress_newline = 0;
 
     if (!argv[1]) {
         printf("\n");
         return 0;
     }
     /* Consume all leading -n options */
     while (argv[i] && strcmp(argv[i], "-n") == 0) {
         suppress_newline = 1;
         i++;
     }
     while (argv[i]) {
         printf("%s", argv[i]);
         if (argv[i + 1])
             printf(" ");
         i++;
     }
     if (!suppress_newline)
         printf("\n");
     return 0;
 }
 
 int ft_cd(char **argv, t_shell *shell) {
     /* Stub: in a real shell you'd call chdir() and update shell->env accordingly */
     if (!argv[1]) {
         fprintf(stderr, "cd: missing operand\n");
         return 1;
     }
     if (argv[2]) {
         fprintf(stderr, "cd: too many arguments\n");
         return 1;
     }
     if (chdir(argv[1]) != 0) {
         perror("cd");
         return 1;
     }
     return 0;
 }
 
 int ft_pwd(void) {
     char cwd[1024];
     if (!getcwd(cwd, sizeof(cwd))) {
         perror("getcwd");
         return 1;
     }
     printf("%s\n", cwd);
     return 0;
 }
 
 int ft_export(char **argv, t_shell *shell) {
     /* Stub: You would update your environment. */
     printf("export built-in executed\n");
     return 0;
 }
 
 int ft_unset(char **argv, t_shell *shell) {
     /* Stub: You would remove variables from your environment. */
     printf("unset built-in executed\n");
     return 0;
 }
 
 int ft_env(char **argv, char **env) {
     if (argv[1] != NULL) {
         fprintf(stderr, "env: too many arguments\n");
         return 1;
     }
     for (int i = 0; env[i] != NULL; i++)
         printf("%s\n", env[i]);
     return 0;
 }
 
 int ft_exit(char **argv, t_shell *shell)
 {
     /* Stub: For now, simply print "exit" and exit.
      * Your real implementation would inspect arguments.
      */
     printf("exit\n");
     exit(shell->exit_status);
     return 0; /* Unreachable */
 }
 
 /*----- Helper: Check if a command is a built-in -----*/
 int is_builtin(const char *cmd) {
     if (!cmd)
         return 0;
     if (strcmp(cmd, "echo") == 0 ||
         strcmp(cmd, "cd") == 0 ||
         strcmp(cmd, "pwd") == 0 ||
         strcmp(cmd, "export") == 0 ||
         strcmp(cmd, "unset") == 0 ||
         strcmp(cmd, "env") == 0 ||
         strcmp(cmd, "exit") == 0)
     {
         return 1;
     }
     return 0;
 }
 
 /*----- Helper: Execute the built-in command -----*/
 int execute_builtin(t_cmd *cmd, t_shell *shell) {
     if (strcmp(cmd->argv[0], "echo") == 0)
         return ft_echo(cmd->argv);
     else if (strcmp(cmd->argv[0], "cd") == 0)
         return ft_cd(cmd->argv, shell);
     else if (strcmp(cmd->argv[0], "pwd") == 0)
         return ft_pwd();
     else if (strcmp(cmd->argv[0], "export") == 0)
         return ft_export(cmd->argv, shell);
     else if (strcmp(cmd->argv[0], "unset") == 0)
         return ft_unset(cmd->argv, shell);
     else if (strcmp(cmd->argv[0], "env") == 0)
         return ft_env(cmd->argv, shell->env);
     else if (strcmp(cmd->argv[0], "exit") == 0)
         return ft_exit(cmd->argv, shell);
     return 127;  // Should never reach here if is_builtin() is used correctly.
 }
 
 /*----- Helper: Count the number of commands in a pipeline -----*/
 int get_command_count(t_cmd *cmd) {
     int count = 0;
     while (cmd) {
         count++;
         cmd = cmd->next;
     }
     return count;
 }
 
 /*----- The Executor: Execute a Pipeline of Commands -----*/
 int execute_pipeline(t_cmd *cmd_list, t_shell *shell) {
     int num_cmds = get_command_count(cmd_list);
     if (num_cmds == 0)
         return -1;
     
     /* If there is exactly one command and it is built-in,
        execute it directly in the parent process so that it can affect shell state. */
     if (num_cmds == 1 && is_builtin(cmd_list->argv[0])) {
         shell->exit_status = execute_builtin(cmd_list, shell);
         return 0;
     }
     
     /* Otherwise, set up pipes for the pipeline. For n commands, we need n-1 pipes. */
     int pipe_count = num_cmds - 1;
     int pipefds[2 * pipe_count];  // Each pipe has two file descriptors.
     for (int i = 0; i < pipe_count; i++) {
         if (pipe(&pipefds[i * 2]) < 0) {
             perror("pipe");
             return -1;
         }
     }
     
     /* Fork child processes for each command */
     pid_t *pids = malloc(sizeof(pid_t) * num_cmds);
     if (!pids) {
         perror("malloc");
         return -1;
     }
     
     int i = 0;
     t_cmd *current = cmd_list;
     while (current) {
         pid_t pid = fork();
         if (pid < 0) {
             perror("fork");
             free(pids);
             return -1;
         }
         
         if (pid == 0) {  /* Child Process */
             /* If not the first command, redirect STDIN to the previous pipe's read end */
             if (i != 0) {
                 if (dup2(pipefds[(i - 1) * 2], STDIN_FILENO) < 0) {
                     perror("dup2 stdin");
                     exit(EXIT_FAILURE);
                 }
             }
             /* If not the last command, redirect STDOUT to the current pipe's write end */
             if (current->next != NULL) {
                 if (dup2(pipefds[i * 2 + 1], STDOUT_FILENO) < 0) {
                     perror("dup2 stdout");
                     exit(EXIT_FAILURE);
                 }
             }
             /* Handle input redirection if specified */
             if (current->input_file) {
                 int fd_in = open(current->input_file, O_RDONLY);
                 if (fd_in < 0) {
                     perror("open input_file");
                     exit(EXIT_FAILURE);
                 }
                 if (dup2(fd_in, STDIN_FILENO) < 0) {
                     perror("dup2 input_file");
                     exit(EXIT_FAILURE);
                 }
                 close(fd_in);
             }
             /* Handle output redirection if specified */
             if (current->output_file) {
                 int fd_out;
                 if (current->append)
                     fd_out = open(current->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
                 else
                     fd_out = open(current->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                 if (fd_out < 0) {
                     perror("open output_file");
                     exit(EXIT_FAILURE);
                 }
                 if (dup2(fd_out, STDOUT_FILENO) < 0) {
                     perror("dup2 output_file");
                     exit(EXIT_FAILURE);
                 }
                 close(fd_out);
             }
             /* Close all pipe file descriptors in the child */
             for (int j = 0; j < 2 * pipe_count; j++)
                 close(pipefds[j]);
             
             /* If this command is built-in, execute it and exit with its return code.
              * (In a pipeline, built-ins are executed in children but will not
              * affect the parent's shell state.) */
             if (is_builtin(current->argv[0])) {
                 exit(execute_builtin(current, shell));
             }
             
             /* Otherwise, execute an external command */
             execvp(current->argv[0], current->argv);
             perror("execvp");
             exit(EXIT_FAILURE);
         }
         /* Parent: record the child’s PID */
         pids[i++] = pid;
         current = current->next;
     }
     
     /* Parent: close all pipe file descriptors */
     for (int j = 0; j < 2 * pipe_count; j++)
         close(pipefds[j]);
     
     /* Parent: wait for all child processes */
     int status;
     while (wait(&status) > 0)
         ;
     
     /* Update the shell's exit status with that of the last child */
     shell->exit_status = WEXITSTATUS(status);
     free(pids);
     return 0;
 }
 
 /*----- End of Executor Code -----
  *
  * Usage:
  *   After you have tokenized and parsed the command(s) into a linked list of t_cmd,
  *   store that list in shell->commands.
  *
  *   Then, to execute the pipeline, call:
  *
  *       execute_pipeline(shell->commands, shell);
  *
  *   This executor supports both external commands and built-in commands.
  *   When there’s a single built-in (like cd) running alone, it is executed in the
  *   parent process so that its effects (e.g. changing directories) are preserved.
  *
  *   When commands (built-in or external) appear in a pipeline, each is executed in
  *   its own child process.
  *
  *   The shell's global exit status (used for $?) is updated with the exit code of the
  *   last command executed.
  *
  * You can expand and modify this code as needed.
  */
 




















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


// int main(void)
// {
//     // char *a = malloc(sizeof(char) * 11); // Allocate enough memory for the string and null terminator
//     // strcpy(a, "abdalrhman");
//     // free(a);

//     while (1)
//     {
//         char *input = get_input();
//         if (!input)
//             break;  // Handle EOF (Ctrl+D) gracefully.

//         int len = ft_strlen(input);
//         if (len > 0)
//         {
//             // Initialize shell state.
//             t_shell shell;
//             shell.exit_status = 0;  // Set an initial exit status. Update this value when a command runs.
//             shell.tokens = tokenizer(input, len);
            
//             if (!shell.tokens) {
//                 free(input);
//                 continue; // Skip execution on tokenizer error.
//             }
            
//             if (syntax_checker(shell.tokens) == 0)
//             {
//                 free_list(shell.tokens);
//                 free(input);
//                 continue; // Skip execution on syntax error.
//             }
//             // Proceed with further processing/execution.
//             expand_tokens(&shell);
//             //print_tokens(shell.tokens); // print tokens after expansion.
//             /*executor*/
            
//             free_list(shell.tokens);
//         }
//         free(input);
//     }
    
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>

/* 
 * Assume the following functions and structures are defined:
 *   - get_input(), ft_strlen(), tokenizer(), syntax_checker(), expand_tokens(), 
 *     parse_commands(), execute_pipeline(), free_list(), free_cmd_list().
 *   - The structures: t_input, t_cmd, t_shell.
 */
t_cmd *parse_commands(t_input *tokens) {
    t_cmd *head = NULL;
    t_cmd *last_cmd = NULL;

    while (tokens) {
        // Allocate a new command structure.
        t_cmd *cmd = malloc(sizeof(t_cmd));
        if (!cmd)
            exit(EXIT_FAILURE);
        cmd->input_file = NULL;
        cmd->output_file = NULL;
        cmd->append = 0;
        cmd->next = NULL;

        // Count the number of arguments for this command.
        int argc = count_args(tokens);
        cmd->argv = malloc(sizeof(char *) * (argc + 1));  // +1 for NULL terminator.
        if (!cmd->argv)
            exit(EXIT_FAILURE);

        int arg_index = 0;
        // Process tokens until a pipe is encountered or end-of-list.
        while (tokens && tokens->type != TYPE_PIPE) {
            if (tokens->type == TYPE_REDIR_IN ||
                tokens->type == TYPE_REDIR_OUT ||
                tokens->type == TYPE_HEREDOC ||
                tokens->type == TYPE_APPEND) {
                int redir_type = tokens->type;
                tokens = tokens->next; // Move to file token.
                if (tokens && tokens->type == TYPE_WORD) {
                    if (redir_type == TYPE_REDIR_IN)
                        cmd->input_file = strdup(tokens->string);
                    else { // Handles TYPE_REDIR_OUT and TYPE_APPEND
                        cmd->output_file = strdup(tokens->string);
                        cmd->append = (redir_type == TYPE_APPEND) ? 1 : 0;
                    }
                }
                tokens = tokens->next; // Skip file token.
                continue;
            }
            else if (tokens->type == TYPE_WORD) {
                cmd->argv[arg_index++] = strdup(tokens->string);
            }
            tokens = tokens->next;
        }
        cmd->argv[arg_index] = NULL;  // NULL-terminate the argv array.

        // If there's a TYPE_PIPE, skip it to start next command.
        if (tokens && tokens->type == TYPE_PIPE)
            tokens = tokens->next;

        if (!head)
            head = cmd;
        else
            last_cmd->next = cmd;
        last_cmd = cmd;
    }
    return head;
}
void free_cmd_list(t_cmd *cmd_list) {
    t_cmd *tmp;
    int i;
    while (cmd_list) {
        tmp = cmd_list;
        cmd_list = cmd_list->next;
        // Free argv array.
        if (tmp->argv) {
            for (i = 0; tmp->argv[i] != NULL; i++) {
                free(tmp->argv[i]);
            }
            free(tmp->argv);
        }
        if (tmp->input_file)
            free(tmp->input_file);
        if (tmp->output_file)
            free(tmp->output_file);
        free(tmp);
    }
}

int main(void)
{
    while (1)
    {
        char *input = get_input();  // Read input from the user.
        if (!input)
            break;  // Handle EOF (e.g. Ctrl+D) gracefully.

        int len = ft_strlen(input);
        if (len > 0)
        {
            t_shell shell;
            shell.exit_status = 0;  // Initialize exit status.
            // You may initialize shell.env from your environment if needed.
            shell.env = NULL;  // For example purposes; update as necessary.
            
            // Tokenize the input.
            shell.tokens = tokenizer(input, len);
            if (!shell.tokens) {
                free(input);
                continue; // Skip execution if tokenizer error (e.g., unclosed quote).
            }
            
            // Check syntax.
            if (syntax_checker(shell.tokens) == 0)
            {
                free_list(shell.tokens);
                free(input);
                continue; // Skip execution on syntax error.
            }
            
            // Expand the tokens.
            expand_tokens(&shell);
            // Optionally, print tokens for debugging.
            //print_tokens(shell.tokens);
            
            // Parse the expanded token list into a command list.
            shell.commands = parse_commands(shell.tokens);
            
            // Execute the pipeline (which handles built-ins and external commands).
            execute_pipeline(shell.commands, &shell);
            
            // Free the allocated token list.
            free_list(shell.tokens);
            // Free the command list.
            free_cmd_list(shell.commands);
        }
        free(input);
    }
    
    return 0;
}

