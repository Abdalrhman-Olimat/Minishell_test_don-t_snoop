NAME = mini
CC = cc
CFLAG = -Wall -Werror -Wextra
SRC_PATH = src/
OBJ_PATH = obj/
SRC = test.c
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
	$(CC) $(CFLAG) $(OBJS) -I./Libft $(LIBFT) -o $(NAME)

$(LIBFT):
	make -C Libft  

clean:
	rm -rf $(OBJ_PATH) $(NAME)
	make clean -C Libft
fclean: clean
	rm -rf $(NAME)
	make fclean -C Libft

re: fclean all