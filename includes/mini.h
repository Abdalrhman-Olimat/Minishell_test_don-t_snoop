/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:23:49 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/15 00:48:40 by aeleimat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINI_H
# define MINI_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "../Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <linux/limits.h>
# include <signal.h>
# include <stdbool.h>

enum e_maxes
{
    MAXIMUM_FILENAME_SIZE = 4096,
    MAXIMUM_CMD_SIZE = 4096,
    MAXIMUM_ENV_NAME_SIZE = 4096
};

typedef enum e_shell_returns
{
    OK = 1000,
    SHELL_SUCCESS = 0,
    SHELL_FAILURE = 1,
    SHELL_EXIT = 2
} t_shell_returns;


typedef enum e_quote_state
{
    QUOTE_NONE,
    QUOTE_SINGLE,
    QUOTE_DOUBLE,
    QUOTE_BACKTICK
} t_quote_state;


typedef struct s_input
{
    char *string;
    int type;
    struct s_input *next;
}                           t_input;


typedef struct s_analyzing_data
{
    size_t pipe_count;       // Tracks the number of pipes
    size_t cmds_count;       // Tracks the number of pipes
    size_t  dirs_num;
    t_quote_state quote_state;  // Tracks the state of quotes (NONE, SINGLE, DOUBLE, BACKTICK)
    char    **args;  // Arguments for the command
    char    **envp;
    char    **path;
} t_analyzing_data;


typedef struct s_content_analyzing_results
{
	bool					is_there_pipe;
	bool					is_there_infile;
	bool					is_there_outfile;
	bool					is_there_appendfile;
	bool					is_there_heredoc;
	int						fd_of_heredoc;
} t_content_analyzing_results;



typedef struct s_command_data
{

	int						fd_of_heredoc;
	int						index_of_heredoc;
	int						builtin;
	int						skip_exec;
	int						skip_cmd;
	int						was_quoted;
	char					*cmd_full;
	char					**cmd_splitted;
	char					*in_file;
	char					*out_file;
	char					*cmd_path;
	char					**delim;
    char                    *path_var;
	struct s_command		**main_cmd;
    t_content_analyzing_results    content_analyze;

	pid_t					p_id;
}	t_command_data;

/* ---------- Shell State Structure ---------- 
   This encapsulates global shell state (exit status, token list, etc.)
*/
typedef struct s_shell
{
    int exit_status;  // Holds the exit status of the most recent foreground pipeline.
    t_input *tokens;
    t_analyzing_data   analyzing_data;
    // char                ***cmds;
    t_command_data    **cmds;
    
} t_shell;







typedef struct s_tokenizer_state {
    char *input;
    int len;
    int i;
    char *token_buf;
    int token_index;
    t_input **head;
    int     in_quotes;     // Add this: flag to track if we're inside quotes
    char    quote_char; 
} t_tokenizer_state;


#define TYPE_WORD 0      // Regular word (e.g., "echo", "cat")
#define TYPE_PIPE 1      // |
#define TYPE_REDIR_IN 2  // <
#define TYPE_REDIR_OUT 3 // >
#define TYPE_HEREDOC 4   // <<
#define TYPE_APPEND 5    // >>

t_input *create_node(char *str, int type);
void init_shell(t_shell *shell, char **envp);
void normalize_linked_list(t_input *head);
void	alloc_envp(t_shell *shell, char **envp, int i);
void free_envp(t_shell *shell);
char **fetch_path(t_shell *shell, int i);

void append_node(t_input **head, char *str, int type);
void free_list(t_input *head);
void print_tokens(t_input *head);
t_input *tokenizer(char *input, int len);
void	fush_token_buffer(t_tokenizer_state *state);
void	handle_whitespace(t_tokenizer_state *state);
int	handle_metacharacters2(t_tokenizer_state *state);
int	handle_metacharacters(t_tokenizer_state *state);
int	unclosed_norm(t_tokenizer_state *state, char *quoted_buf);
int syntax_checker(t_input *tokens);
t_command_data **big_malloc(t_shell *shell, int i);
void	free_cmds_all(t_command_data **cmds, short count, int i);



int ft_echo(char **argv);
int ft_env(char **argv, char **envp);
int ft_pwd(void);
void expand_tokens(t_shell *shell);


// strings 
int	count_tokens(t_input *head);
int	fill_token_array(char **array, t_input *head);
void	free_token_array(char **array, int until);
char	**tokens_to_array(t_input *head);
void	play_after_tokens(t_shell *shell);
void	print_args(char **args);
t_shell_returns	cmds(t_shell *shell, int i, int j);
int	analyze_pipes(t_shell *shell, int i, int j);
void analyze_cmds(t_shell *shell, int i, int j);
int my_strcmp(const char *s1, const char *s2);
int is_operator(const char *arg);
void	process_cmds(t_shell shell, int i , int j);
int count_max_commands(t_shell *shell);
t_command_data **big_malloc(t_shell *shell, int i);

int	print_syntax_error_token(t_input *current);
int	is_redirection(int type);
int	print_incomplete_command_error(t_input *last_token);
int	print_pipe_error(void);
int	print_unexpected_token_error(void);

#endif