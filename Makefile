NAME = minishell
SRCDIR = ./src/
OBJDIR = ./obj/
SRCS = $(wildcard $(SRCDIR)*.c)
SRCS += $(wildcard $(SRCDIR)redirects/*.c)
SRCS += $(wildcard $(SRCDIR)builtins/*.c)
SRCS += $(wildcard $(SRCDIR)paths/*.c)
SRCS += $(wildcard $(SRCDIR)constructions/*.c)
SRCS += $(wildcard $(SRCDIR)list/*.c)
SRCS += $(wildcard $(SRCDIR)pipes/*.c)

OBJS = $(SRCS:$(SRCDIR)%.c=$(OBJDIR)%.o)
HEADERDIR = ./
HEADER = $(HEADERDIR)minishell.h
CC = cc

LIBFT = ./libft
LIBFT_A = $(LIBFT)/libft.a
RLDIR = ./readline
RL_A = $(RLDIR)/libreadline.a

CFLAGS = -Wall -Werror -Wextra -I$(RLDIR) -I$(HEADERDIR) -g -fsanitize=address
LIBS = -lreadline -L$(LIBFT) -lft -lncurses
LIBS += -L$(RLDIR) 

all: $(NAME) $(OBJDIR)

$(NAME): $(OBJS) $(HEADER) $(LIBFT_A) $(RL_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(OBJDIR)%.o: $(SRCDIR)%.c
	$(shell mkdir -p $(OBJDIR))
	$(shell mkdir -p $(OBJDIR)/redirects)
	$(shell mkdir -p $(OBJDIR)/builtins)
	$(shell mkdir -p $(OBJDIR)/paths)
	$(shell mkdir -p $(OBJDIR)/constructions)
	$(shell mkdir -p $(OBJDIR)/list)
	$(shell mkdir -p $(OBJDIR)/pipes)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT_A):
	@make -C $(LIBFT) bonus

$(RL_A):
	@cd $(RLDIR) && exec ./configure
	@make -C $(RLDIR)

clean:
	@rm -rf $(OBJDIR)
	@rm -f $(OBJS)
	@make -C $(LIBFT) clean

fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
