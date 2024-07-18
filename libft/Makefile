NAME = libft.a

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC_DIR = .

OBJ_DIR = objects

SRCS := $(shell find $(SRC_DIR) -type f -name "ft_*.c")

OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@
    
$(OBJ_DIR):
	mkdir -p $@

$(NAME): $(OBJS)
	ar rcs $@ $^

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

bonus: all

so:
	$(CC) -nostartfiles -fPIC $(CFLAGS) $(SRCS) $(SRCS_B)
	gcc -nostartfiles -shared -o libft.so $(OBJS) $(OBJS_B)
