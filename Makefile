NAME = a.out
SRCS = main.c
OBJS = $(SRCS:%.c=%.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT = ./libft
LIBFT_A = $(LIBFT)/libft.a
LIBS = -lreadline -L$(LIBFT) -lft
HEADER = minishell.h

all: $(NAME)

$(NAME): $(OBJS) $(HEADER) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT_A):
	@make -C $(LIBFT) bonus

clean:
	rm -f $(OBJS)
	@make -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
