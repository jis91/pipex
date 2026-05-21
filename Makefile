NAME	= pipex

CC		= cc
CFLAGS	= -Wall -Wextra -Werror

SRCS	=	main.c \
			executor.c \
			path.c \
			utils.c \

OBJS	= $(SRCS:.c=.o)

SRCS_BONUS	=	main_bonus.c \
				executor_bonus.c \
				path_bonus.c \
				utils_bonus.c \
				here_doc_bonus.c

OBJS_BONUS	= $(SRCS_BONUS:.c=.o)

LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

INCLUDES	= -I. -I$(LIBFT_DIR)


all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

bonus:

	@echo "BONUS not done yet"

.PHONY: all clean fclean re bonus