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

#include <signal.h>

typedef struct s_input {
    char *string;
    int type;
    struct s_input *next;
} t_input;


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



#endif