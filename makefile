NAME = mini
CC = cc
CFLAG = -g -Wall -Werror -Wextra -lreadline 
SRC_PATH = src/
OBJ_PATH = obj/

#builtin_export.c builtin_unset.c builtin_exit.c 
SRC = main.c token_file1.c token_file2.c token_utils.c syntax_checker.c builtin_echo.c builtin_cd.c builtin_pwd.c builtin_env.c expander1.c \
        tokens_to_array.c print_arr_args.c   analyze_pipes.c analyze_cmds.c normalize_linked_list.c \
        alloc_envp.c fetch_path.c free_envp.c syntax_checker2.c token_file1_norm.c \
        big_malloc.c free_cmds_all.c expander2.c expander3.c some_ft_fun.c signal.c #cmds.c play_after_tokens.c

LIBFT = Libft/libft.a
INCS	= -I ./include/
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

all: $(OBJ_PATH) $(NAME) 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) -g -c $< -o $@ $(INCS)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(NAME): $(OBJS) $(LIBFT)
	make all -C Libft 
	$(CC)  $(OBJS) -I./Libft $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
	make -C Libft  

clean:
	rm -rf $(OBJ_PATH) $(NAME)
	make clean -C Libft
fclean: clean
	rm -rf $(NAME)
	make fclean -C Libft

re: fclean all