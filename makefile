NAME = mini
CC = cc
CFLAG = -g -Wall -Werror -Wextra -lreadline
SRC_PATH = src/
OBJ_PATH = obj/

SRC = \
	alert_err_of_file.c \
	alloc_envp.c \
	analyze_cmds.c \
	analyze_pipes.c \
	apply_signals.c \
	big_malloc.c \
	builtin_cd.c \
	builtin_echo.c \
	builtin_env.c \
	builtin_pwd.c \
	change_redirections.c \
	cmds.c \
	copy_old_data.c \
	count_cmds_tokens.c \
	exec_builtin.c \
	exec_child.c \
	exec_with_child.c \
	execute_cmds.c \
	execute_here_doc.c \
	exit_err_str.c \
	expander1.c \
	expander2.c \
	expander3.c \
	fetch_path.c \
	free_2d_arr.c \
	free_big_malloc_cmds.c \
	free_both_envp_paths.c \
	free_cmds_all.c \
	free_envp.c \
	free_paths.c \
	full_close_pipes.c \
	handle_append.c \
	handle_expansion.c \
	handle_heredoc.c \
	handle_heredoc_input.c \
	handle_interrupt_of_heredoc.c \
	handle_no_pipes_cmd.c \
	handle_redir_in.c \
	handle_redir_out.c \
	handle_signals.c \
	heredoc_signal_handler.c \
	init_execution_data.c \
	init_splits.c \
	input_handler.c \
	is_built_in.c \
	just_execute.c \
	main.c \
	normalize_linked_list.c \
	parse_tokens_into_cmds.c \
	play_after_tokens.c \
	print_arr_args.c \
	process_cmd_compltly.c \
	process_heredoc.c \
	process_token_word.c \
	set_cmd_skip.c \
	set_working_cmd.c \
	signal.c \
	skip_piped_cmd.c \
	some_ft_fun.c \
	switch_pipes.c \
	syntax_checker.c \
	syntax_checker2.c \
	token_file1.c \
	token_file1_norm.c \
	token_file2.c \
	token_utils.c \
	tokens_to_array.c \
	wait_children.c \
	words_to_cmd.c \
	close_wth_free.c \
	advanced_symbols_check.c \
	# terminate_resources.c

LIBFT = Libft/libft.a
INCS = -I ./include/
SRCS = $(addprefix $(SRC_PATH), $(SRC))
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

all: $(OBJ_PATH) $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) -g -c $< -o $@ $(INCS)

$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)

$(NAME): $(OBJS) $(LIBFT)
	make -C Libft
	$(CC) $(OBJS) -I./Libft $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
	make -C Libft

clean:
	rm -rf $(OBJ_PATH)
	make clean -C Libft

fclean: clean
	rm -rf $(NAME)
	make fclean -C Libft
re: fclean all

















































# NAME = mini
# CC = cc
# CFLAG = -g -Wall -Werror -Wextra -lreadline 
# SRC_PATH = src/
# OBJ_PATH = obj/

# #builtin_export.c builtin_unset.c builtin_exit.c 
# SRC = main.c token_file1.c token_file2.c token_utils.c syntax_checker.c builtin_echo.c builtin_cd.c builtin_pwd.c builtin_env.c expander1.c \
#         tokens_to_array.c print_arr_args.c   analyze_pipes.c analyze_cmds.c normalize_linked_list.c \
#         alloc_envp.c fetch_path.c free_envp.c syntax_checker2.c token_file1_norm.c \
#         big_malloc.c free_cmds_all.c expander2.c expander3.c some_ft_fun.c signal.c play_after_tokens.c cmds.c \
# 		parse_tokens_into_cmds.c free_big_malloc_cmds.c execute_here_doc.c init_splits.c execute_cmds.c \
# 		free_2d_arr.c

# LIBFT = Libft/libft.a
# INCS	= -I ./include/
# SRCS	= $(addprefix $(SRC_PATH), $(SRC))
# OBJ		= $(SRC:.c=.o)
# OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

# all: $(OBJ_PATH) $(NAME) 

# $(OBJ_PATH)%.o: $(SRC_PATH)%.c
# 	$(CC) -g -c $< -o $@ $(INCS)

# $(OBJ_PATH):
# 	mkdir $(OBJ_PATH)

# $(NAME): $(OBJS) $(LIBFT)
# 	make all -C Libft 
# 	$(CC)  $(OBJS) -I./Libft $(LIBFT) -o $(NAME) -lreadline

# $(LIBFT):
# 	make -C Libft  

# clean:
# 	rm -rf $(OBJ_PATH) $(NAME)
# 	make clean -C Libft
# fclean: clean
# 	rm -rf $(NAME)
# 	make fclean -C Libft

# re: fclean all