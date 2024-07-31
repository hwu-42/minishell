# Declare phony targets
.PHONY: all clean fclean re bonus

NAME = minishell

CC = cc

CFLAGS = -Wall -Wextra -Werror

LIB_PATH = libft

LIB = libft.a

LIB2 = lreadline

SRC_DIR = .

OBJ_DIR = .

SRC = $(shell find $(SRC_DIR) -maxdepth 1 -type f -name "*.c")

OBJ = $(SRC:.c=.o)
all: $(NAME)

# Build the library
$(LIB):
	$(MAKE) -C $(LIB_PATH)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ -$(LIB_PATH) -$(LIB) -$(LIB2)

$(NAME): $(OBJ) | $(LIB)
	$(CC) $(CFLAGS) $^ -o $(NAME) -L./$(LIB_PATH) -lft -$(LIB2)

clean:
	$(MAKE) -C $(LIB_PATH) fclean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

bonus: all