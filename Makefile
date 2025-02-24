NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iincludes
RM = rm -rf

LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

SRCS = main.c \
		init.c \
		utils/readline.c \
		utils/release_memory.c 

OBJS = $(SRCS:.c=.o)

$(NAME): $(OBJS) $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
		clear

all: $(NAME)

$(LIBFT):
		@make -C $(LIBFT_DIR)
clean: 
		@$(RM) $(OBJS)
		@make -C clean $(LIBFT_DIR)
		clear

fclean: clean
		$(RM) $(NAME)
		@make -C fclean $(LIBFT_DIR)
		clear

re: fclean all

.PHONY: all clean fclean re
	