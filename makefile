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
INCS    = -I ./include/
SRCS    = $(addprefix $(SRC_PATH), $(SRC))
OBJ             = $(SRC:.c=.o)
OBJS    = $(addprefix $(OBJ_PATH), $(OBJ))


all: $(OBJ_PATH) $(NAME)
	@echo "\033[1;32m[✓] Compilation done.\033[0m \033[1;36mRun: ./$(NAME)\033[0m"
	@echo "\033[1;32m====================[ BUILD OK ]====================\033[0m"
	@echo "\033[1;34mYou can now run: ./$(NAME)\033[0m"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
		@$(CC) -c $< -o $@ $(INCS)
		@echo "\033[1;32mCompiling: $<\033[0m"

$(OBJ_PATH):
		mkdir $(OBJ_PATH)

$(NAME): $(OBJS) $(LIBFT)
		@$(MAKE) -s -C Libft
		@echo "\033[1;32mLinking and using the flags of : $(CFLAG)\033[0m"
		$(CC) $(CFLAG) $(OBJS) -I./Libft $(LIBFT) -o $(NAME) -lreadline



clean:
		rm -rf $(OBJ_PATH) $(NAME)
		make clean -C Libft
fclean: clean
		rm -rf $(NAME)
		make fclean -C Libft

re: fclean all

# =========================
# Inline Libft Compilation
# =========================

LIBFT_PATH = Libft/
LIBFT_SRCS = \
	ft_atoi.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
	ft_isdigit.c ft_isprint.c ft_strlen.c ft_tolower.c \
	ft_toupper.c ft_strlcat.c ft_strlcpy.c ft_strncmp.c \
	ft_strchr.c ft_strrchr.c ft_memset.c ft_bzero.c \
	ft_memcpy.c ft_memmove.c ft_memchr.c ft_memcmp.c \
	ft_strnstr.c ft_calloc.c ft_strdup.c ft_substr.c \
	ft_putchar_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_putendl_fd.c \
	ft_strjoin.c ft_strtrim.c ft_itoa.c ft_split.c \
	ft_strmapi.c ft_striteri.c \
	get_next_line.c get_next_line_utils.c

LIBFT_OBJS = $(addprefix $(OBJ_PATH)/libft_, $(LIBFT_SRCS:.c=.o))
LIBFT_SRCS_FULL = $(addprefix $(LIBFT_PATH), $(LIBFT_SRCS))

$(LIBFT): $(LIBFT_OBJS)
	@echo "\033[1;32mFinished the compiling\033[0m"
		ar rcs $@ $^

# Compile Libft with full flags
$(OBJ_PATH)/libft_%.o: $(LIBFT_PATH)%.c
	$(CC) -Wall -Wextra -Werror -g -c $< -o $@ -I $(LIBFT_PATH)
