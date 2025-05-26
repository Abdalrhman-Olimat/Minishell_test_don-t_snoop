/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeleimat <aeleimat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 11:23:49 by aeleimat          #+#    #+#             */
/*   Updated: 2025/05/25 16:51:32 by aeleimat         ###   ########.fr       */
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
# include <termios.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <signal.h>

//extern volatile sig_atomic_t	g_heredoc_interrupted = 0;
extern int g_exit_status;

enum e_maxes
{
    MAXIMUM_FILENAME_SIZE = 4096,
    MAXIMUM_CMD_SIZE = 4096,
    MAXIMUM_ENV_NAME_SIZE = 4096
};

typedef enum e_shell_returns
{
    OK = 1000,
    FT = 42,
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

typedef struct s_tokens_flags
{
    bool is_quoted;        // Indicates if the token is quoted
}                           t_tokens_flags;


typedef struct s_input
{
    char *string;
    int type;
    struct s_input *next;
    t_tokens_flags flags;

}                           t_input;


typedef struct s_analyzing_data
{
    t_quote_state quote_state;  // Tracks the state of quotes (NONE, SINGLE, DOUBLE, BACKTICK)
    size_t pipe_count;       // Tracks the number of pipes
    size_t cmds_count;       // Tracks the number of pipes
    size_t  dirs_num;
    char    **args;  // Arguments for the command
    char    **envp;
    char    **path;
    int     arg_index;
} t_analyzing_data;


typedef struct s_content_analyzing_results
{
	bool					is_there_pipe;
	bool					is_there_infile;
	bool					is_there_outfile;
	bool					is_there_appendfile;
	bool					is_there_heredoc;
	int						fd_of_heredoc;
    int                     stdin_backup;
    int                     stdout_backup;
} t_content_analyzing_results;



typedef struct s_command_data
{

	size_t					fd_of_heredoc;
	size_t					index_of_heredoc;
	size_t  				builtin;
	bool					skip_cmd;
	bool					skip_all_execution;
	int						was_quoted; // ?? when to use
	char					*cmd_full;
	char					**cmd_splitted;
	char					*in_file;
	char					*out_file;
	char					*cmd_path;
	char					**delim;
    char                    *path_var;
	struct s_command_data		**main_cmd;
    t_content_analyzing_results    content_analyze;
    int                     temp;

	pid_t					p_id;
}	t_command_data;

/* ---------- Shell State Structure ---------- 
   This encapsulates global shell state (exit status, token list, etc.)
*/
typedef struct s_temps
{
    int temp_i;
    int temp_i2;
    int temp_i3;
    double temp_d;
    bool temp_b;
    
} t_temps;

typedef struct s_shell
{
    int exit_status;  // Holds the exit status of the most recent foreground pipeline.
    t_input *tokens;
    t_input *tokens_header;
    t_analyzing_data   analyzing_data;
    // char                ***cmds;
    t_command_data    **cmds;
    t_temps           temps_vars;
    
} t_shell;



typedef struct s_tokenizer_state {
    char *input;
    int len;
    int i;
    char *token_buf;
    int token_index;
    t_input **head;
    int     in_quotes;     
    char    quote_char; 
} t_tokenizer_state;

typedef struct s_pipe_data
{
	int	pipe_fd[2];
	int	prev_pipe[2];
	bool	got_forked;
}	t_pipe_data;
/* ---------- Expander Implementation ---------- */

/*
 * Structure to hold all state information for token expansion
 * Keeps related variables grouped together for better code organization
 */

typedef struct s_expander_context
{
	t_input		*node;
	size_t		src_len;
	size_t		i;
	size_t		status_len;
	size_t		var_len;
	size_t		buf_size;
	size_t		j;
	size_t		name_len;
	size_t		var_start;
	size_t		env_len;
	int			is_heredoc_delimiter;
	int			in_double;
	int			in_single;
	int			exit_status;
	char		*source;
	char		*expanded;
	char		status_str[16];
	char		var_name[4096];
	char		*env_value;
	const char	*shell_name;
}	t_expander_context;

#define TYPE_WORD 0      // Regular word (e.g., "echo", "cat")
#define TYPE_PIPE 1      // |
#define TYPE_REDIR_IN 2  // <
#define TYPE_REDIR_OUT 3 // >
#define TYPE_HEREDOC 4   // <<
#define TYPE_APPEND 5    // >>

t_input *create_node(char *str, int type);
void init_shell(t_shell *shell, char **envp);
void normalize_linked_list(t_input *head);
int	alloc_envp(t_shell *shell, char **envp);
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
int	words_to_cmd(t_shell *shell, t_input *token, t_command_data **cmd, int *cmd_i);
void	free_cmds_all(t_command_data **cmds, short count, int i);
void	alert_err_of_file(char *filename);
void	set_status_skip(t_shell *shell, t_command_data **cmd, int *cmd_i, int status);
int handle_heredoc(t_shell *shell, t_input **token, t_command_data **cmd, int *cmd_i);
void	free_big_malloc_cmds(size_t err_num, t_command_data    **cmds, int i);
int	parse_tokens_into_cmds(t_shell *shell, t_input **tokens, int i , int j);
int	close_wth_free(size_t risgo_vsnot ,t_command_data **cmds, int fd);
void	exit_err_str(char *str);
int process_heredoc(t_shell *shell, t_command_data *cmd, int delem_index);
void	heredoc_signal_handler(int sig);
int	handle_interrupt_of_heredoc(size_t rlk,  t_command_data *cmd, bool is_rlm);
void handle_heredoc_input(int fd_outstream,  t_command_data *cmd, int delem_index);
void	apply_sig_action(int sig);
int apply_signals(int s_flg);
int execute_here_doc(t_shell *shell, int i, int j, size_t rlt_slm);
int process_token_word(size_t *splt_arg_index, t_shell *shell, t_input *current_token, t_command_data *cmds);
size_t	count_cmds_tokens(t_input *current_token);
int init_splits(t_shell *shell, size_t splt_arg_index, size_t cmd_index);
int skip_piped_cmd(t_command_data *command, t_pipe_data *pipe_data);
int	is_built_in(t_command_data *command);
int process_cmd_compltly(t_shell *shell, int i, t_pipe_data *pipe_data);
int change_redirections(t_command_data *command, int *stdin_backup, int *stdout_backup);
int handle_no_pipes_command(t_command_data *command, int *stdin_backup, int *stdout_backup);
int ft_cd(char **argv);
int execute_cmds(t_shell *shell, int i, int j);
int exec_builtin(t_shell *shell, t_command_data *command, int *stdin_backup, int *stdout_backup);
int	exec_child_setting(t_command_data *cmd, t_pipe_data *pipe, int i, int j);
int just_execute(t_shell *shell, t_command_data *command, int i);
int skip_piped_cmd(t_command_data *command, t_pipe_data *pipe_data);
char **copy_old_data(int old_len, int new_len, char **old_str);
void	free_2d_arr(char **string);
char **free_paths_shell(t_shell *shell);
char **free_path(char **paths);
int free_both_envp_paths(t_shell *shell);
int set_working_cmd(t_shell *shell, t_command_data *command);
int handle_expansion(t_shell *shell, t_command_data *command);
int switch_pipes(int *pipe_fd, int *older_pipe, t_command_data **cmd, int i);
void	full_close_pipes(t_pipe_data *pipe_data);
void	init_execution_data(t_pipe_data *pipe_data);
void exec_with_child(t_shell *shell, t_command_data *command, t_pipe_data *pipe_data, int cmd_iter);
size_t count_tokens_till_pipe(t_input *current_token);
void advanced_symbols_check(t_shell *shell, t_input **tokens, int *itereator_of_cmd);
int increase_heredoc_index(t_command_data **cmd, int *cmd_i);
int handle_redir_in(t_shell *shell, t_input **token, int *cmd_i, t_command_data **cmd);
int handle_redir_out(t_shell *shell, t_input **token, t_command_data **cmd, int *cmd_i);
int handle_append(t_shell *shell, t_input **token, t_command_data **cmd, int *cmd_i);
int wait_children(t_shell *shell, t_command_data **cmd_list, int i, pid_t waited);
int	get_2d_len(char **arr);
int	append_args_safely(char ***args_ref, char **suffix, int skip);
char	**realloc_2d_appending(char **old, int old_size, int new_size);
int add_remaining_arguments(char ***base, char **original);
void update_command_and_path(t_shell *shell, t_command_data *cmd, char **new_tokens);
int was_expansion_needed(t_command_data *cmd);
char **split_primary_argument(t_command_data *cmd);
int calculate_new_lengths(char ***args_ref, char **suffix, int skip, int *orig_len, int *added_len);
char **allocate_expanded_args(char **original, char **suffix, int skip);
int copy_suffix(char **args, char **suffix, int start_index, int skip);
void redirect_append_or_heredoc(t_command_data *cmd);
void redirect_to_heredoc(t_command_data *cmd);
void redirect_to_append(t_command_data *cmd);
int	get_2d_len(char **arr);
int copy_one_by_one(char **dst, char **src, int *dst_i, int *src_i);




int ft_echo(char **argv);
int ft_env(char **argv, char **envp);
int ft_pwd(void);
void expand_tokens(t_shell *shell);


// strings 
int	count_tokens(t_input *head);
int	fill_token_array(char **array, t_input *head, int i);
void	free_token_array(char **array, int until);
char	**tokens_to_array(t_input *head);
void	play_after_tokens(t_shell *shell);
void	print_args(char **args);
t_shell_returns	cmds(t_shell *shell, int i, int j);
int	analyze_pipes(t_shell *shell, int i, int j);
void analyze_cmds(t_shell *shell, int i, int j);
int my_strcmp(const char *s1, const char *s2);
int is_operator(const char *arg);
int count_max_commands(t_shell *shell);
t_command_data **big_malloc(t_shell *shell, int i);

int	print_syntax_error_token(t_input *current);
int	is_redirection(int type);
int	print_incomplete_command_error(t_input *last_token);
int	print_pipe_error(void);
int	print_unexpected_token_error(void);
void	cleanup_tokenizer_state(t_tokenizer_state *state);
t_input	*cleanup_tokenizer(t_tokenizer_state *state);
int handle_quote_in_token(t_tokenizer_state *state);
int	ft_strcmp(char *s1, char *s2);
int	process_exit_status(t_expander_context *ctx);
int	should_skip_expansion(t_expander_context *ctx);
int	initialize_expansion_buffer(t_expander_context *ctx);
int	handle_quotes_expander(t_expander_context *ctx);
int	convert_digits_to_string(int tmp, int is_neg, char *buffer, int i);
int	int_to_string(int value, char *buffer);
char	*ft_strncpy(char *dst, const char *src, size_t n);
char	*ft_strcpy(char *dst, const char *src);
void	*ft_realloc(void *ptr, size_t newsize);
int	ensure_capacity(t_expander_context *ctx, size_t additional);
int	process_digit_parameter(t_expander_context *ctx);
int	process_env_variable(t_expander_context *ctx);

void    sigint_handler(int sig);
void    sigint_handler_child(int sig);
void    setup_signals_interactive(void);
void    setup_signals_exec(void);
void    reset_signals(void);

void set_node_quoted(t_input **head, bool is_quoted);


















#endif