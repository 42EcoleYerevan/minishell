NAME = minishell
SRCDIR = ./src/
OBJDIR = ./obj/
SRCS = $(wildcard $(SRCDIR)*)
OBJS = $(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)
HEADERDIR = ./
HEADER = $(HEADERDIR)minishell.h
CC = cc

LIBFT = ./libft
LIBFT_A = $(LIBFT)/libft.a
RLDIR = ./readline
RL_A = $(RLDIR)/libreadline.a

CFLAGS = -Wall -Werror -Wextra -I$(RLDIR) -fsanitize=address -I$(HEADERDIR)
LIBS = -lreadline -L$(LIBFT) -lft -lncurses
LIBS += -L$(RLDIR) 

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(HEADER) $(LIBFT_A) $(RL_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT_A):
	@make -C $(LIBFT) bonus

$(RL_A):
	@cd $(RLDIR) && exec ./configure
	@make -C $(RLDIR)

clean:
	rm -f $(OBJS)
	@make -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
