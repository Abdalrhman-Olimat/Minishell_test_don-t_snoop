/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:23:49 by aeleimat          #+#    #+#             */
/*   Updated: 2025/02/26 15:51:38 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINI_H
# define MINI_H

# include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
# include <stdio.h>
# include "../Libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <linux/limits.h>
#include <signal.h>

typedef struct s_input {
    char *string;
    int type;
    struct s_input *next;
} t_input;

/* ---------- Shell State Structure ---------- 
   This encapsulates global shell state (exit status, token list, etc.)
*/
typedef struct s_shell {
    int exit_status;  // Holds the exit status of the most recent foreground pipeline.
    t_input *tokens;
} t_shell;


#define TYPE_WORD 0      // Regular word (e.g., "echo", "cat")
#define TYPE_PIPE 1      // |
#define TYPE_REDIR_IN 2  // <
#define TYPE_REDIR_OUT 3 // >
#define TYPE_HEREDOC 4   // <<
#define TYPE_APPEND 5    // >>

t_input *create_node(char *str, int type);
void append_node(t_input **head, char *str, int type);
void free_list(t_input *head);
void print_tokens(t_input *head);
t_input *tokenizer(char *input, int len);



int syntax_checker(t_input *tokens);
static int is_redirection(int type);



int ft_echo(char **argv);
int ft_env(char **argv, char **envp);
int ft_pwd(void);

#endif