NAME = mini
CC = cc
CFLAG = -g -Wall -Werror -Wextra -lreadline 
SRC_PATH = src/
OBJ_PATH = obj/
SRC = main.c token_file1.c token_utils.c syntax_checker.c builtin_echo.c builtin_cd.c builtin_pwd.c  builtin_env.c expander1.c  #builtin_export.c builtin_unset.c builtin_exit.c 
LIBFT = Libft/libft.a
INCS	= -I ./include/
SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))

all: $(OBJ_PATH) $(NAME) 

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) -c $< -o $@ $(INCS)

$(OBJ_PATH):
	mkdir $(OBJ_PATH)

$(NAME): $(OBJS) $(LIBFT)
	make all -C Libft 
	$(CC) $(CFLAG) $(OBJS) -I./Libft $(LIBFT) -o $(NAME) -lreadline

$(LIBFT):
	make -C Libft  

clean:
	rm -rf $(OBJ_PATH) $(NAME)
	make clean -C Libft
fclean: clean
	rm -rf $(NAME)
	make fclean -C Libft

re: fclean all