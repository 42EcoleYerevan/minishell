NAME = minishell
SRCDIR = ./src/
OBJDIR = ./obj/
SRCS = $(wildcard $(SRCDIR)*)
OBJS = $(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)
HEADERDIR = ./
HEADER = $(HEADERDIR)minishell.h
CC = cc
CFLAGS = -Wall -Werror -Wextra -I$(HEADERDIR)
LIBFT = ./libft
LIBFT_A = $(LIBFT)/libft.a
LIBS = -lreadline -L$(LIBFT) -lft

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

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
